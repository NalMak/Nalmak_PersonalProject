#include "H_common.fxh"

matrix g_world;

texture g_mainTex;
texture g_depthTex;
float4 g_mainTexColor;


sampler mainSampler = sampler_state
{
	texture = g_mainTex;
};

sampler depthSampler = sampler_state
{
	texture = g_depthTex;
};
struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 uvAndDepth : TEXCOORD0; // x,y = uv  z = depth
	float4 projPos : TEXCOORD1;
};

struct PS_INPUT
{
	float3 normal :NORMAL;
	float4 uvAndDepth : TEXCOORD0;
	float4 projPos : TEXCOORD1;

};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	matrix wvp = mul(g_world, g_cBuffer.viewProj);
	o.pos = mul(float4(_in.pos,1), wvp);
	o.projPos = o.pos;
	//o.normal = _in.normal;
	o.uvAndDepth.xy = _in.uv;
	o.uvAndDepth.zw = o.pos.zw;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float4 diffuse = tex2D(mainSampler, _in.uvAndDepth.xy);
	o.diffuse = diffuse * g_mainTexColor;
	
	float2 depthUV;

	depthUV.x = (_in.projPos.x / _in.projPos.w) * 0.5f + 0.5f;
	depthUV.y = (_in.projPos.y / _in.projPos.w) * -0.5f + 0.5f;

	float viewZ = tex2D(depthSampler, depthUV).y * zFar;

	o.diffuse.a = o.diffuse.a * max((viewZ - _in.projPos.w) * 0.05f, 0.f);

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
