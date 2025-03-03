cbuffer Transform : register(b0)
{
    matrix WorldViewProjectionMatrix;
}

struct VS_INPUT
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : TEXCOORD1;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.pos = mul(float4(input.pos, 1.0), WorldViewProjectionMatrix);
    output.uv = input.uv;
    output.normal = normalize(input.normal);
    return output;
}
