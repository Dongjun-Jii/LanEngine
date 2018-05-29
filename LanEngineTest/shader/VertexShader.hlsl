cbuffer WorldMatrixBuffer
{
	float4x4 worldMatrix;
};

cbuffer ViewMatrixBuffer
{
	float4x4 viewMatrix;
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
	output.pos = mul(worldMatrix, output.pos);
	output.pos = mul(viewMatrix, output.pos);
	return output;
}