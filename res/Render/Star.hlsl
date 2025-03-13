// Simple vertex shader
struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

cbuffer WorldBuffer : register(b0)
{
    float4x4 World;
};

cbuffer ViewProjBuffer : register(b1)
{
    float4x4 Proj;
    float4x4 View;
};

float PerlinNoise(float3 position)
{
    return frac(sin(dot(position.xyz, float3(12.9898, 78.233, 45.164))) * 43758.5453);
}

PSInput VS(VSInput input)
{
    PSInput output;
    output.position = mul(mul(mul(float4(input.position, 1.0f), World), View), Proj);
    output.color = input.color;
    return output;
}

float4 PS(PSInput input) : SV_TARGET
{
    float amount = 0.5;
    float n = smoothstep(0.99, 1., PerlinNoise(input.position.xyz / 3000));
    float3 g = lerp(float3(0.0, 0.0, 0.0), float3(0.0,0.0,0.0), input.position.z / 10);
    float3 col = lerp(g, input.color.rgb, n);
    float4 color = float4(col, 1.0);
    return color;
}
