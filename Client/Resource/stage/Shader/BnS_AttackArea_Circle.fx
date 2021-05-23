#include "../../../../Engine/Resource/Shader/H_common.fxh"

matrix g_world;


texture g_mainTex;
texture g_outLineTex;


float4 g_mainColor;
float g_lifeTimeRatio;


sampler mainSampler = sampler_state
{
	texture = g_mainTex;
};
sampler outlineSampler = sampler_state
{
	texture = g_outLineTex;
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

	matrix wvp = mul(g_world, g_cBuffer.viewProj);
	
	o.position = mul(float4(_input.position,1), wvp);
	o.uv = _input.uv;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float4 final = tex2D(outlineSampler, _input.uv);
	
	float2 uv = _input.uv - float2(0.5f, 0.5f);
	if (g_lifeTimeRatio * g_lifeTimeRatio > pow(uv.x,2) + pow(uv.y,2))
	{
		float4 innerTex = tex2D(mainSampler, _input.uv);
		final += innerTex;
	}
	o.diffuse = final * g_mainColor;

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		//ZEnable = true;
		//ZWriteEnable = true;
		
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
