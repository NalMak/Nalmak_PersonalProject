#include "../../../../Engine/Resource/Shader/H_common.fxh"

matrix g_world;

texture g_mainTex;
float4 g_mainTexColor;
float g_emissionPower;
float g_lifeTimeRatio;

float g_uvAnimX;
float g_uvAnimY;
int g_uvRepeatX;
int g_uvRepeatY;

float g_hardness;

float g_thick;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;
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


	o.position = mul(float4(_input.position, 1), wvp);
	o.uv = _input.uv * float2(g_uvRepeatX, g_uvRepeatY);


	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input)
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 boundary = _input.uv - float2(0.5f, 0.5f);

	float hard = g_hardness * 2;
	float alphaX = saturate(g_hardness - abs(boundary.x) * hard);
	float alphaY = saturate(g_hardness - abs(boundary.y) * hard);

	float4 diffuse = tex2D(mainSampler, _input.uv.xy + float2(g_uvAnimX * g_lifeTimeRatio, g_uvAnimY* g_lifeTimeRatio));
	o.diffuse = diffuse * g_mainTexColor * g_emissionPower * alphaX * alphaY;

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		//ZEnable = true;
		//ZWriteEnable = true;
		CullMode = NONE;
	VertexShader = compile vs_3_0 VS_Main_Default();
	PixelShader = compile ps_3_0 PS_Main_Default();

	}





};