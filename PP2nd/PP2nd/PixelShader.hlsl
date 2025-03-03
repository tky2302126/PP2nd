Texture2D BaseColorMap : register(t0);
Texture2D NormalMap : register(t1);
Texture2D AOMap : register(t2);
Texture2D RoughnessMap : register(t3);
SamplerState Sampler : register(s0);

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : TEXCOORD1;
};

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    float4 baseColor = BaseColorMap.Sample(Sampler, input.uv);
    float3 normalMap = NormalMap.Sample(Sampler, input.uv).xyz * 2.0 - 1.0;
    float ao = AOMap.Sample(Sampler, input.uv).r;
    float roughness = RoughnessMap.Sample(Sampler, input.uv).r;

    float3 lightDir = normalize(float3(0.3, 1.0, 0.5)); // ŽÎ‚ß‚©‚ç‚ÌŒõ
    float lightIntensity = max(dot(normalMap, lightDir), 0.0);

    float3 color = baseColor.rgb * lightIntensity * ao * (1.0 - roughness);
    
    return float4(color, baseColor.a);
}
