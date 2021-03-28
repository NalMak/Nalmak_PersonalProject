#include "H_common.fxh"

texture g_final;
texture g_brightBlur;

sampler FinalSampler = sampler_state
{
	texture = g_final;
};

sampler BrightBlurSampler = sampler_state
{
	texture = g_brightBlur;
};

//sampler EmissionBlurSampler = sampler_state
//{
//	texture = g_emissionBlur;
//};

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
	float2 uv :TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	o.position = float4(_input.position, 1);
	o.uv = _input.uv;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 uv = float2(_input.uv) + float2(perPixelX, perPixelY);

	float3 final = tex2D(FinalSampler, uv).xyz;
	float3 bright = tex2D(BrightBlurSampler, uv).xyz;

	o.color = float4(final + bright * 0.1f, 1);

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용


		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
