struct VSOUT
{
    float3 Color : COLOR;
    float4 Pos : SV_Position;
};

float4 main(VSOUT psin) : SV_TARGET
{
	return float4(psin.Color, 1.0f);
}