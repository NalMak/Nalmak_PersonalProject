#include "H_common.fxh"

matrix g_world;

texture g_mainTex;
texture g_fetchTex;
float4 g_mainTexColor;
float  g_f0;
float  g_roughness;

int g_bone;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;
};


sampler fetchSampler = sampler_state
{
	texture = g_fetchTex;

	minfilter = linear;
	magfilter = linear;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float3 weight : BLENDWEIGHT;
	float4 boneIndex : BLENDINDICES;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float3 normal :NORMAL;
	float4 uvAndDepth : TEXCOORD0; // x,y = uv  z = depth

};

struct PS_INPUT
{
	float3 normal :NORMAL;
	float4 uvAndDepth : TEXCOORD0;

};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
	float4 normal : COLOR1;
	float4 depth : COLOR2;
	float4 cookTorrance : COLOR3;

};

matrix GetSkinMatrixFromTexture(int _index)
{
	float4 uvCol = float4(((float)((_index % 16) * 4) + 0.5f) / 64.0f, ((float)((_index / 16)) + 0.5f) / 64.0f, 0.0f, 0.0f);

	float4x4 mat =
	{
		tex2Dlod(fetchSampler, uvCol),
		tex2Dlod(fetchSampler, uvCol + float4(1.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(fetchSampler, uvCol + float4(2.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(fetchSampler, uvCol + float4(3.0f / 64.0f, 0, 0, 0))
	};
	return mat;
}

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	float3 skinningPos = 0;
	float3 skinningNormal = 0;

	float lerpWeight = 0.f;

	for (int i = 0; i < g_bone - 1; ++i)
	{
		lerpWeight += _in.weight[i];
		
		skinningPos += _in.weight[i] * mul(float4(_in.pos,1.f), GetSkinMatrixFromTexture(_in.boneIndex[i])).xyz;
		skinningNormal += _in.weight[i] * mul(float4(_in.normal,0.f), GetSkinMatrixFromTexture(_in.boneIndex[i])).xyz;
		
	}
	
	lerpWeight = 1.f - lerpWeight;

	skinningPos += lerpWeight * mul(float4(_in.pos, 1.f), GetSkinMatrixFromTexture(_in.boneIndex[g_bone - 1])).xyz;
	skinningNormal += lerpWeight * mul(float4(_in.normal, 0.f), GetSkinMatrixFromTexture(_in.boneIndex[g_bone - 1])).xyz;

	float4 worldPos = mul(float4(skinningPos, 1), g_world);
	o.pos = mul(worldPos, g_cBuffer.viewProj);

	o.normal = GetWorldNormal(skinningNormal, g_world);

	o.uvAndDepth.xy = _in.uv;
	o.uvAndDepth.zw = o.pos.zw;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float4 diffuse = tex2D(mainSampler, _in.uvAndDepth.xy);
	o.diffuse = diffuse * g_mainTexColor;
	o.normal = GetScaleBiasNormal(_in.normal);
	
	o.depth = float4(GetDepth(_in.uvAndDepth.zw),0,1);

	o.cookTorrance.x = g_f0;
	o.cookTorrance.y = g_roughness;
	o.cookTorrance.z = 0;
	o.cookTorrance.w = 1;

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
