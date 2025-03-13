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

PSInput VS(VSInput input)
{
    PSInput output;
    output.position = mul(mul(mul(float4(input.position, 1.0f), World), View), Proj);
    output.color = input.color;
    return output;
}

float4 PS(PSInput input) : SV_TARGET
{
    return input.color;
}