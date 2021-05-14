#include "../../../../Engine/Resource/Shader/H_common.fxh"

matrix g_world;

texture g_mainTex;
texture g_glowTex;

float g_changeRatio;
float g_glowRatio;

float4 g_mainTexColor;


sampler mainSampler = sampler_state
{
	texture = g_mainTex;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler glowSampler = sampler_state
{
	texture = g_glowTex;

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

	float4 diffuse = tex2D(mainSampler, _input.uv);
	float4 glow = tex2D(glowSampler, _input.uv);

	diffuse = diffuse * g_changeRatio;
	glow = glow * (g_glowRatio);

	o.diffuse = diffuse + glow;

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
