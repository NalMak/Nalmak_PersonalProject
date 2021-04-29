#include "H_common.fxh"



matrix g_world;


struct VS_INPUT
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
};

struct PS_INPUT
{
};

struct PS_OUTPUT
{
	float4 color : COLOR0;
};


VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	float4x4 wvp = mul(g_world, g_cBuffer.viewProj);
	o.pos = mul(float4(_in.pos,1), wvp);

	return o;
}

//PS_OUTPUT PS_Main_Default(PS_INPUT _in)
//{
//	PS_OUTPUT o = (PS_OUTPUT)0;
//
//	o.color = 1;
//
//	return o;
//}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용
	
		VertexShader = compile vs_3_0 VS_Main_Default();
		//PixelShader = compile ps_3_0 PS_Main_Default();
	}


		

	
};
