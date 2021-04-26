#include "../../../../Engine/Resource/Shader/H_common.fxh"

matrix g_world;

texture g_mainTex;
texture g_fetchTex;

texture g_normalTex;


float4 g_mainTexColor;
float  g_f0;
float  g_roughness;
float g_normalPower;

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
sampler normalSampler = sampler_state
{
	texture = g_normalTex;
};




struct VS_INPUT
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;
	float2 uv : TEXCOORD0;
	float3 weight : BLENDWEIGHT0;
	float4 boneIndex : BLENDINDICES0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 uvAndDepth : TEXCOORD0; // x,y = uv  z = depth
	float3 N :NORMAL;
	float3 T :TEXCOORD1;
	float3 B :TEXCOORD2;
	float3 camDirTangent : TEXCOORD3;

};

struct PS_INPUT
{
	float4 uvAndDepth : TEXCOORD0;
	float3 N :NORMAL;
	float3 T : TEXCOORD1;
	float3 B :TEXCOORD2;

};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
	float4 normal : COLOR1;
	float4 depth_cookTorrance : COLOR2;

};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	float3 skinningPos = 0;
	float3 skinningTangent = 0;
	float3 skinningBinormal = 0;
	float3 skinningNormal = 0;


	float lerpWeight = 0.f;

	for (int i = 0; i < g_bone; ++i)
	{
		lerpWeight += _in.weight[i];
		Matrix skinMatrix = GetSkinMatrixFromTexture(fetchSampler, _in.boneIndex[i]);
		skinningPos += _in.weight[i] * mul(float4(_in.pos, 1.f), skinMatrix).xyz;
		skinningTangent += _in.weight[i] * mul(float4(_in.tangent, 0.f), skinMatrix).xyz;
		skinningBinormal += _in.weight[i] * mul(float4(_in.binormal, 0.f), skinMatrix).xyz;
		skinningNormal += _in.weight[i] * mul(float4(_in.normal, 0.f), skinMatrix).xyz;


	}
	lerpWeight = 1.f - lerpWeight;

	Matrix lastSkinMatrix = GetSkinMatrixFromTexture(fetchSampler, _in.boneIndex[g_bone]);
	skinningPos += lerpWeight * mul(float4(_in.pos, 1.f), lastSkinMatrix).xyz;
	skinningTangent += lerpWeight * mul(float4(_in.tangent, 0.f), lastSkinMatrix).xyz;
	skinningBinormal += lerpWeight * mul(float4(_in.binormal, 0.f), lastSkinMatrix).xyz;
	skinningNormal += lerpWeight * mul(float4(_in.normal, 0.f), lastSkinMatrix).xyz;



	float4 worldPos = mul(float4(skinningPos, 1), g_world);
	o.pos = mul(worldPos, g_cBuffer.viewProj);

	//float3 normal = GetWorldNormal(_in.normal, g_world).xyz;

	o.T = normalize(mul(g_world, float4(skinningTangent,1))).xyz;
	o.B = normalize(mul(g_world, float4(skinningBinormal,1))).xyz;
	o.N = normalize(mul(g_world, float4(skinningNormal,1))).xyz;

	o.uvAndDepth.xy = _in.uv;
	o.uvAndDepth.zw = o.pos.zw;
	


	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;



	float4 diffuse = tex2D(mainSampler, _in.uvAndDepth.xy);
	o.diffuse = diffuse * g_mainTexColor;
	float3 normal = tex2D(normalSampler, _in.uvAndDepth.xy);
	normal = normal * 2 - 1;
	normal = normalize(normal);
	/*float3 bumpNormal = _in.N + (normal.x * _in.T) + (normal.y * _in.B);
	bumpNormal = normalize(bumpNormal);*/

	float3x3 tbn =
	{
		_in.T,
		_in.B,
		_in.N
	};
	normal = mul(tbn, normal);// *g_normalPower + defaultNormal * (1 - g_normalPower);
	normal = normalize(normal);
	normal = normal * 0.5f + 0.5f;
	o.normal = float4(normal,1);

	o.depth_cookTorrance.xy = GetDepth(_in.uvAndDepth.zw);
	o.depth_cookTorrance.zw = float2(g_f0, g_roughness);


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
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
