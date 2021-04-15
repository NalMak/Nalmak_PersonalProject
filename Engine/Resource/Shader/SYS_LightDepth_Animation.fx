#include "H_common.fxh"
#include "H_light.fxh"

matrix g_world;
texture g_fetchTex;
DirectionalLight g_directionalLight;

int g_bone;

sampler fetchSampler = sampler_state
{
	texture = g_fetchTex;

	minfilter = linear;
	magfilter = linear;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float3 weight : BLENDWEIGHT0;
	float4 boneIndex : BLENDINDICES0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float3 worldPos : TEXCOORD0; 
};

struct PS_INPUT
{
	float3 worldPos :TEXCOORD0;

};

struct PS_OUTPUT
{
	float4 lightDepth : COLOR0;

};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 


	float3 skinningPos = 0;
	float3 skinningNormal = 0;

	float lerpWeight = 0.f;

	for (int i = 0; i < g_bone; ++i)
	{
		lerpWeight += _in.weight[i];
		skinningPos += _in.weight[i] * mul(float4(_in.pos, 1.f), GetSkinMatrixFromTexture(fetchSampler, _in.boneIndex[i])).xyz;
	}
	lerpWeight = 1.f - lerpWeight;

	skinningPos += lerpWeight * mul(float4(_in.pos, 1.f), GetSkinMatrixFromTexture(fetchSampler, _in.boneIndex[g_bone])).xyz;

	float4 worldPos = mul(float4(skinningPos, 1), g_world);
	o.pos = mul(worldPos, g_directionalLight.viewProj);
	//o.pos = mul(worldPos, g_cBuffer.viewProj);

	o.worldPos = worldPos;
	
	
	
	return o;
}

static const float OneDividzFar = 1 / 400.f;

PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float4 color = 1;
	color.xyz = length(_in.worldPos - g_directionalLight.base.position) * OneDividzFar;
	o.lightDepth = color;
	
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
		//cullmode = none;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
