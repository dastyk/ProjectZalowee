cbuffer TCBuffer
{
	float4x4 mTranslation;
	float4 mColor;
};

struct VS_IN
{
	float2 Pos : POSITION;
};
struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

VS_OUT VSMain( VS_IN input)
{
	VS_OUT output;

	output.Pos = mul(float4(input.Pos, 0.0f, 1.0f), mTranslation);
	output.Color = mColor;
	return output;
}