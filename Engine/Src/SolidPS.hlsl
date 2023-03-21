float4 main(float2 pos : WORLDPOS) : SV_TARGET
{
    float lol = saturate((pos.y + 5) / 60.f);
	return float4(lol, 0.0f, 1.f - lol, 1.0f);
}