struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
};

SamplerState state;
Texture2D image;

float4 main(PixelInputType input) : SV_TARGET
{
	float4 color = image.Sample(state, input.tex);
	clip(color.a - 0.05f);
	return color;
}