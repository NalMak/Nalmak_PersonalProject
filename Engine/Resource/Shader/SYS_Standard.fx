#include "H_common.fxh"

matrix g_world;

texture g_mainTex;
float4 g_mainTexColor;
float  g_f0;
float  g_roughness;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
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
	float4 depth_cookTorrance : COLOR2;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	matrix wvp = mul(g_world, g_cBuffer.viewProj);
	o.pos = mul(float4(_in.pos,1), wvp);

	o.normal = GetWorldNormal(_in.normal, g_world);

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
	
	o.depth_cookTorrance.xy = GetDepth(_in.uvAndDepth.zw);

	o.depth_cookTorrance.z = g_f0;
	o.depth_cookTorrance.w = g_roughness;


	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z �������� Ȱ��

	/*	ZEnable = true;
		ZWriteEnable = true;
		CullMode = CCW;*/
		//cullmode = none;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
