#include "../../../../Engine/Resource/Shader/H_common.fxh"

matrix g_world;

float4 g_color;
float g_emissionPower;

texture g_fetchTex;

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
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
	float3 weight : BLENDWEIGHT0;
	float4 boneIndex : BLENDINDICES0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 uvAndDepth : TEXCOORD0; // x,y = uv  z = depth
	float3 normal :NORMAL;
};

struct PS_INPUT
{
	float4 uvAndDepth : TEXCOORD0;
	float3 normal :NORMAL;
};

struct PS_OUTPUT
{
	float4 emission : COLOR0;
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
		Matrix skinMatrix = GetSkinMatrixFromTexture(fetchSampler, _in.boneIndex[i]);
		skinningPos += _in.weight[i] * mul(float4(_in.pos, 1.f), skinMatrix).xyz;
		skinningNormal += _in.weight[i] * mul(float4(_in.normal, 0.f), skinMatrix).xyz;
	}
	lerpWeight = 1.f - lerpWeight;

	Matrix lastSkinMatrix = GetSkinMatrixFromTexture(fetchSampler, _in.boneIndex[g_bone]);
	skinningPos += lerpWeight * mul(float4(_in.pos, 1.f), lastSkinMatrix).xyz;
	skinningNormal += lerpWeight * mul(float4(_in.normal, 0.f), lastSkinMatrix).xyz;

	float4 worldPos = mul(float4(skinningPos, 1), g_world);
	o.pos = mul(worldPos, g_cBuffer.viewProj);

	o.normal = LocalToWorldDirection(skinningNormal, g_world);  

	o.uvAndDepth.xy = _in.uv;
	o.uvAndDepth.zw = o.pos.zw;

	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	
	float angle = 1 - abs(dot(g_cBuffer.worldCamLook, _in.normal));
	float rimPower = pow(angle, 2);
	float3 final = g_color.xyz * rimPower * g_emissionPower;
	o.emission = float4(final,1);

	//o.emission = (float4(specular, 1) * mask.g + (o.diffuse * mask.r) + (o.diffuse * mask.b * 3.f)) * g_specularPower;

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
