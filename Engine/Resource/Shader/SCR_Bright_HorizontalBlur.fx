#include "H_common.fxh"

matrix g_world;

texture g_mainTex;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;

	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;

};

struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
	
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 clipPos : TEXCOORD0;
	float2 uv : TEXCOORD1;
};

struct PS_INPUT
{
	float4 clipPos : TEXCOORD0;
	float2 uv :TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR;

};



VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	o.pos = float4(_in.pos, 1);

	o.uv = _in.uv;
	
	o.clipPos = o.pos;
	return o;
}

float pixelKernel[13] =
{
	-6,
	-5,
	-4,
	-3,
	-2,
	-1,
	0,
	1,
	2,
	3,
	4,
	5,
	6,
};

float blurWeights[13] =
{
	0.002216,
	0.008764,
	0.026995,
	0.064759,
	0.120985,
	0.176033,
	0.199471,
	0.176033,
	0.120985,
	0.064759,
	0.026995,
	0.008764,
	0.002216,
};

static const float g_rtPerPixelX = 0.5f / 480;
static const float g_rtPerPixelY = 0.5f / 270;


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float4 color = 0;
	for (int i = 0; i < 13; ++i)
	{
		color += tex2D(mainSampler, float2(
			_in.uv.x + (pixelKernel[i] * g_rtPerPixelX) + g_rtPerPixelX,
			_in.uv.y + g_rtPerPixelY))* blurWeights[i];
	}


	o.diffuse = color;

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

	/*	ZEnable = true;
		ZWriteEnable = true;
		CullMode = CCW;*/
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
