#include "H_common.fxh"

matrix g_world;

texture g_mainTex;
texture g_normalTex;

float4 g_mainTexColor;
float  g_f0;
float  g_roughness;
float g_normalPower;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;
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
	float4 depth : COLOR2;
	float4 cookTorrance : COLOR3;

};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	matrix wvp = mul(g_world, g_cBuffer.viewProj);
	o.pos = mul(float4(_in.pos,1), wvp);

	//float3 normal = GetWorldNormal(_in.normal, g_world).xyz;

	o.T = normalize(mul(g_world, float4(_in.tangent,1))).xyz;
	o.B = normalize(mul(g_world, float4(_in.binormal,1))).xyz;
	o.N = normalize(mul(g_world, float4(_in.normal,1))).xyz;

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

	//float3x3 tbn =
	//{
	//	_in.T,
	//	_in.B,
	//	_in.N
	//};
	//float3 defaultNormal = normalize(_in.N);
	//normal = mul(tbn, normal);// *g_normalPower + defaultNormal * (1 - g_normalPower);
	normal = normal * 0.5f + 0.5f;
	o.normal = float4(normal,1);


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
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
