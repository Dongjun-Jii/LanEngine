cbuffer WorldMatrixBuffer
{
	float4x4 worldMatrix;
};

struct VertexInputType
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	output.tex = input.tex;
	output.pos = input.pos;
	output.pos = mul(output.pos, worldMatrix);
	return output;
}