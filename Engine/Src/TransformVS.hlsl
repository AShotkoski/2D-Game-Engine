cbuffer cb : register(b0)
{
    matrix model;
    matrix viewproj;
};

float4 main( float2 pos : POSITION ) : SV_POSITION
{
    matrix modelviewproj = mul(model, viewproj);
    float3 trans = mul(float4(pos, 0, 1), modelviewproj);
    return float4(trans, 1);
}