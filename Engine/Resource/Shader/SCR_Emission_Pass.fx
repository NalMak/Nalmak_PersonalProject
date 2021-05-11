#include "H_common.fxh"

texture g_final;
texture g_emission;
texture g_emissionBlurDiv4;
texture g_emissionBlurDiv2;

texture g_specular;
texture g_specularBlur;

sampler FinalSampler = sampler_state
{
	texture = g_final;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};

sampler EmissionSampler = sampler_state
{
	texture = g_emission;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};


sampler EmissionBlurSampler4 = sampler_state
{
	texture = g_emissionBlurDiv4;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};

sampler EmissionBlurSampler2 = sampler_state
{
	texture = g_emissionBlurDiv2;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};

sampler SpecularSampler = sampler_state
{
	texture = g_specular;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};

sampler SpecularBlurSampler = sampler_state
{
	texture = g_specularBlur;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
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

	float3 final = tex2D(FinalSampler, uv).xyz;
	
	float3 emission = tex2D(EmissionSampler, uv).xyz;
	if (any(emission))
	{
		float3 emissionBlur4 = tex2D(EmissionBlurSampler4, uv).xyz;
		float3 emissionBlur2 = tex2D(EmissionBlurSampler2, uv).xyz;
		
		final = final + (emission  + emissionBlur4 + emissionBlur2) * 0.5f;
	}
	else
	{
		float3 specular = tex2D(SpecularSampler, uv).xyz;
		float3 specularBlur = tex2D(SpecularBlurSampler, uv).xyz;
		final = final + (specular + specularBlur) * 0.5f;
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
