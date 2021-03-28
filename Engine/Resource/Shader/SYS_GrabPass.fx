#include "H_common.fxh"
#include "H_light.fxh"


matrix g_world;


texture g_diffuse;



sampler DiffuseSampler = sampler_state
{
	texture = g_diffuse;
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
	float4 clipPos : TEXCOORD0;
};

struct PS_INPUT
{
	float4 clipPos : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	float4x4 wvp = mul(g_world, g_cBuffer.viewProj);
	o.pos = mul(float4(_in.pos,1), wvp);

	o.clipPos = o.pos;


	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 uv = ComputeScreenUV(_in.clipPos);
	float2 uvRT = uv +float2(0.5f / WINCX, 0.5f / WINCY);

	float3 diffuse = tex2D(DiffuseSampler, uvRT).xyz;
	
	o.diffuse = float4(diffuse, 1);

	//o.diffuse = worldPos;
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
