#include "../../../../Engine/Resource/Shader/H_common.fxh"

matrix g_world;
texture g_mainTex;
float4 g_mainTexColor;
float g_outputRatio;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.position = mul(float4(_input.position,1), g_world);
	o.position.w = 1;
	o.uv = _input.uv;
	//o.normal = float3(0, 0, 1);
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	if (_input.uv.x < g_outputRatio)
	{
		float4 diffuse = tex2D(mainSampler, _input.uv);
		o.diffuse = diffuse * g_mainTexColor;
	}
	else
	{
		o.diffuse = float4(0.1f,0.1f,0.1f,0.5f);
	}
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
