#include "Utils.hlsl"

#define LIGHT_TYPE_DIRECTIONAL 0
#define LIGHT_TYPE_SPOT 1
#define LIGHT_TYPE_POINT 2
#define MAX_LIGHTS 10

struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
    float3 WorldPos : POSITION;
};

cbuffer WorldBuffer : register(b0)
{
    float4x4 gWorld;
};

cbuffer ViewProjBuffer : register(b1)
{
    float4x4 gProj;
    float4x4 gView;
};

cbuffer cbPerMaterial : register(b2)
{
    float4 cbPerMaterial_ambientLightColor;
    float4 cbPerMaterial_ambient;
    float4 cbPerMaterial_diffuse;
    float4 cbPerMaterial_specular;
    float cbPerMaterial_shininess;
    float cbPerMaterial_padding3[3];
};

struct Light
{
    float3 color;
    int type;
    
    float3 direction;
    float intensity;
    
    float3 position;
    float spotAngle;
    
    float padding[4];
};

cbuffer cbPerLights : register(b3)
{
    Light lights[MAX_LIGHTS];
};

float PerlinNoise(float3 position)
{
    return frac(sin(dot(position.xyz, float3(12.9898, 78.233, 45.164))) * 43758.5453);
}

PSInput VS(VSInput vin)
{
    PSInput vout;

    float height = PerlinNoise(vin.position);
    height = max(0.2, height);
    
    float3 color = vin.color.rgb;
    color = color * height;
    
    float heightPos = height / 32;
    
    vin.position += normalize(vin.position) * heightPos;
    
    vout.position = mul(mul(mul(float4(vin.position, 1.0f), gWorld), gView), gProj);
    
    vout.normal = normalize(mul(vin.normal, (float3x3) gWorld));

    vout.color = float4(color, vin.color.a);
    
    vout.WorldPos = vout.position.xyz;

    return vout;
}

float4 PS(PSInput input) : SV_TARGET
{
    float3 cameraPosition = -mul(gView, gView[3].xyz); // Camera position in world space

    float3 viewDirection = normalize(cameraPosition - input.WorldPos); // View direction

    float4 finalColor = ComputeAmbient(cbPerMaterial_ambientLightColor, cbPerMaterial_ambient, input.color);

    float3 diffuseColor = float3(0.0f, 0.0f, 0.0f);
    float3 specularColor = float3(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < MAX_LIGHTS; ++i)
    {
        Light currentLight = lights[i];

        if (currentLight.type == LIGHT_TYPE_DIRECTIONAL)
        {
            // Directional light calculations
            float3 lightColorDirectional = currentLight.color * currentLight.intensity;
            float3 lightDirectionDirectional = -normalize(currentLight.direction); // Invert direction for directional light

            float diffuseIntensity = dot(input.normal, lightDirectionDirectional);
            diffuseIntensity = saturate(diffuseIntensity);

            diffuseColor += ComputeDiffuse(lightDirectionDirectional, input.normal, lightColorDirectional, cbPerMaterial_diffuse) * diffuseIntensity;
            specularColor += ComputePhongSpecular(lightDirectionDirectional, input.normal, viewDirection, lightColorDirectional, cbPerMaterial_specular, cbPerMaterial_shininess);
        }
        else if (currentLight.type == LIGHT_TYPE_SPOT)
        {
            // Spot light calculations
            float3 lightColorSpot = currentLight.color * currentLight.intensity;
            float3 lightPositionSpot = -currentLight.position;
            float3 lightDirectionSpot = -normalize(currentLight.direction);
            float spotlightAngle = radians(currentLight.spotAngle);

            float spotIntensity = ComputeSpotIntensity(lightPositionSpot, lightDirectionSpot, input.WorldPos, spotlightAngle);

            diffuseColor += ComputeDiffuse(lightDirectionSpot, input.normal, lightColorSpot, cbPerMaterial_diffuse) * spotIntensity;
            specularColor += ComputePhongSpecular(lightDirectionSpot, input.normal, viewDirection, lightColorSpot, cbPerMaterial_specular, cbPerMaterial_shininess) * spotIntensity;
        }
        else if (currentLight.type == LIGHT_TYPE_POINT)
        {
            // Point light calculations
            float3 lightColorPoint = currentLight.color;
            float3 lightPositionPoint = currentLight.position;

            float pointLightIntensity = ComputePointLightIntensity(lightPositionPoint, input.normal, currentLight.intensity);

            float3 lightDirectionPoint = normalize(lightPositionPoint - input.normal);

            diffuseColor += ComputeDiffuse(lightDirectionPoint, input.normal, lightColorPoint, cbPerMaterial_diffuse) * pointLightIntensity;
            specularColor += ComputePhongSpecular(lightDirectionPoint, input.normal, viewDirection, lightColorPoint, cbPerMaterial_specular, cbPerMaterial_shininess) * pointLightIntensity;
        }
    }

    finalColor.rgb += diffuseColor * input.color.rgb;
    finalColor.rgb += specularColor * input.color.rgb;
    finalColor.a = input.color.a;
    
    return finalColor;
}