#include "H_common.fxh"


texture g_mainTex;

float g_RTperPixelX;
float g_RTperPixelY;


sampler mainSampler = sampler_state
{
	texture = g_mainTex;

	
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
	
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv :TEXCOORD0;
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




PS_OUTPUT PS_Vertical(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float4 color = 0;
	for (int i = 0; i < 13; ++i)
	{
		//color += tex2D(mainSampler, float2(
		//	_in.uv.x + g_RTperPixelX,
		//	_in.uv.y + (pixelKernel[i] * g_RTperPixelY) + g_RTperPixelY))
		//	* blurWeights[i];
		color += tex2D(mainSampler, float2(
			_in.uv.x + g_RTperPixelX,
			_in.uv.y + (pixelKernel[i] * g_RTperPixelY) + g_RTperPixelY))
			* blurWeights[i];

	}

	o.diffuse = color;

	return o;
}



PS_OUTPUT PS_Horizontal(PS_INPUT  _in)
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float4 color = 0;
	for (int i = 0; i < 13; ++i)
	{
		color += tex2D(mainSampler, float2(
			_in.uv.x + (pixelKernel[i] * g_RTperPixelX) + g_RTperPixelX,
			_in.uv.y + g_RTperPixelY))
			* blurWeights[i];
	}


	o.diffuse = color;

	return o;

}
technique DefaultTechnique
{
	Pass VerticalPass
	{
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Vertical();
	}

	Pass HorizontalPass
	{
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Horizontal();
	}

	
};
