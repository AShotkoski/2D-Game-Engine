struct VSOUT
{
    float3 Color : COLOR;
    float4 Pos : SV_Position;
};

VSOUT main( float2 pos : POSITION, float3 c : COLOR )
{
    VSOUT vout;
    vout.Color = c;
    vout.Pos = float4(pos, 0, 1);
    return vout;
}