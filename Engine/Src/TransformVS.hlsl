cbuffer cb : register(b0)
{
    matrix model;
    matrix viewproj;
};

struct VSout
{
    float2 worldpos : WORLDPOS;
    float4 pos : SV_Position;
};

VSout main( float2 pos : POSITION )
{
    VSout vsout;
    matrix modelviewproj = mul(model, viewproj);
    float3 trans = mul(float4(pos, 0, 1), modelviewproj).xyz;
    vsout.pos = float4(trans, 1);
    vsout.worldpos = mul(float4(pos, 0, 1), model);
    return vsout;
}