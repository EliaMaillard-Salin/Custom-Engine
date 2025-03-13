#include "Utils.hlsl"

#define LIGHT_TYPE_DIRECTIONAL 0
#define LIGHT_TYPE_SPOT 1
#define LIGHT_TYPE_POINT 2
#define MAX_LIGHTS 10

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
};

cbuffer cbPerCamera : register(b1)
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

struct VertexIn
{
    float3 PosL : POSITION;
    float4 Color : COLOR;
    float3 Normal : NORMAL;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float4 Color : COLOR;
    float3 NormalW : NORMAL;
    float3 WorldPos : POSITION;
};

// Vertex shader
VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    
    // Transform position to world space
    float4 posW = mul(float4(vin.PosL, 1.0f), gWorld);

    // Transform position to homogeneous clip space using gWorld, gView, and gProj matrices.
    vout.PosH = mul(mul(posW, gView), gProj);

    // Transform normal to world space
    vout.NormalW = normalize(mul(vin.Normal, (float3x3) gWorld));

    // Pass vertex color to the pixel shader.
    vout.Color = vin.Color;

    // Pass world position to the pixel shader
    vout.WorldPos = posW.xyz;

    return vout;
}

// Pixel shader
float4 PS(VertexOut pin) : SV_Target
{    
    float3 cameraPosition = -mul(gView, gView[3].xyz); // Camera position in world space

    float3 viewDirection = normalize(cameraPosition - pin.WorldPos); // View direction

    float4 finalColor = ComputeAmbient(cbPerMaterial_ambientLightColor, cbPerMaterial_ambient, pin.Color);

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

            float diffuseIntensity = dot(pin.NormalW, lightDirectionDirectional);
            diffuseIntensity = saturate(diffuseIntensity);

            diffuseColor += ComputeDiffuse(lightDirectionDirectional, pin.NormalW, lightColorDirectional, cbPerMaterial_diffuse) * diffuseIntensity;
            specularColor += ComputePhongSpecular(lightDirectionDirectional, pin.NormalW, viewDirection, lightColorDirectional, cbPerMaterial_specular, cbPerMaterial_shininess);
        }
        else if (currentLight.type == LIGHT_TYPE_SPOT)
        {
            // Spot light calculations
            float3 lightColorSpot = currentLight.color * currentLight.intensity;
            float3 lightPositionSpot = -currentLight.position;
            float3 lightDirectionSpot = -normalize(currentLight.direction);
            float spotlightAngle = radians(currentLight.spotAngle);

            float spotIntensity = ComputeSpotIntensity(lightPositionSpot, lightDirectionSpot, pin.WorldPos, spotlightAngle);

            diffuseColor += ComputeDiffuse(lightDirectionSpot, pin.NormalW, lightColorSpot, cbPerMaterial_diffuse) * spotIntensity;
            specularColor += ComputePhongSpecular(lightDirectionSpot, pin.NormalW, viewDirection, lightColorSpot, cbPerMaterial_specular, cbPerMaterial_shininess) * spotIntensity;
        }
        else if (currentLight.type == LIGHT_TYPE_POINT)
        {
            // Point light calculations
            float3 lightColorPoint = currentLight.color;
            float3 lightPositionPoint = currentLight.position;

            float pointLightIntensity = ComputePointLightIntensity(lightPositionPoint, pin.WorldPos, currentLight.intensity);

            float3 lightDirectionPoint = normalize(lightPositionPoint - pin.WorldPos);

            diffuseColor += ComputeDiffuse(lightDirectionPoint, pin.NormalW, lightColorPoint, cbPerMaterial_diffuse) * pointLightIntensity;
            specularColor += ComputePhongSpecular(lightDirectionPoint, pin.NormalW, viewDirection, lightColorPoint, cbPerMaterial_specular, cbPerMaterial_shininess) * pointLightIntensity;
        }
    }

    finalColor.rgb += diffuseColor * pin.Color.rgb;
    finalColor.rgb += specularColor * pin.Color.rgb;
    finalColor.a = pin.Color.a;
    
    return finalColor;
}