#include "H_common.fxh"


texture g_diffuse;
texture g_normal;
texture g_light;
texture g_shadow;

sampler DiffuseSampler = sampler_state
{
	texture = g_diffuse;
};
sampler NormalSampler = sampler_state
{
	texture = g_normal;
};
sampler LightSampler = sampler_state
{
	texture = g_light;
};
sampler ShadowSampler = sampler_state
{
	texture = g_shadow;
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

	float3 diffuse = tex2D(DiffuseSampler, uv).xyz;
	float3 normal = tex2D(NormalSampler, uv).xyz;


	float3 final;
	if (any(normal))
	{
		float3 light = tex2D(LightSampler, uv).xyz;
		float3 shadow = tex2D(ShadowSampler, uv).xyz;
		shadow = saturate(shadow + 0.2f);
		//shadow = light + shadow;
		final =  diffuse * shadow * light;
	}
	else
	{
		final = diffuse;
	}
	
	o.color = float4(final, 1);

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
