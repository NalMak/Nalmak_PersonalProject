#include "H_common.fxh"

matrix g_world;

float4 g_mainTexColor;
float g_thick;

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; //

	


	float4 worldPos = mul(float4(_input.position,1), g_world);
	float3 worldNormal = mul(float4(_input.normal,0), g_world).xyz;
	worldPos.xyz = worldPos.xyz + normalize(worldNormal) * g_thick;

	o.position = mul(worldPos, g_cBuffer.viewProj);
	o.uv = _input.uv;
	
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 diffuse = g_mainTexColor;
	o.diffuse = diffuse;

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z �������� Ȱ��

		//ZEnable = true;
		//ZWriteEnable = true;
		
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
