Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);
cbuffer cbMosaic : register(b0)
{
    float2 g_playerScreenPos;
    float g_radius;
    float2 g_screenSize;
};
struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
};
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};
VS_OUT VS(VS_IN vin)
{
    VS_OUT vout;
    vout.pos = float4(vin.pos, 1.0f);
    vout.uv = vin.uv;
    return vout;
}
float4 PS(VS_OUT pin) : SV_Target
{
    float dist = distance(pin.uv, g_playerScreenPos);

    float2 uv = pin.uv;
    if (dist > g_radius)
    {
        float2 pixelSize = 8.0 / g_screenSize;
        uv = floor(uv / pixelSize) * pixelSize;
    }

    return g_texture.Sample(g_sampler, uv);
}
