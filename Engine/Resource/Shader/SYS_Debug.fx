#include "H_common.fxh"

matrix g_world;

float4 g_mainTexColor;


struct VS_INPUT
{
	float3 position : POSITION;
	
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	
};

struct PS_INPUT
{
	
};

struct PS_OUTPUT
{
	float4 diffuse0 : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 珥덇린???꾩닔!

	float4x4 wvp = mul(g_world, g_cBuffer.viewProj);
	o.position = mul(float4(_input.position,1), wvp);
	
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	
	o.diffuse0 = g_mainTexColor;

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

	
		CullMode = NONE;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
