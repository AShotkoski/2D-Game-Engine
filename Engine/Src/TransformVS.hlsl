cbuffer cb : register(b0)
{
    matrix model;
    matrix view;
};

float4 main( float2 pos : POSITION ) : SV_POSITION
{
    matrix modelview = mul(model, view);
    float3 trans = mul(float4(pos, 0, 1), modelview);
    return float4(trans, 1);
}