#include "H_common.fxh"




struct VS_INPUT
{
	float3 position : POSITION;
	float3 color :COLOR;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float3 color :COLOR;
};

struct PS_INPUT
{
	float3 color :COLOR;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	
	o.position = mul(float4(_input.position,1),g_cBuffer.viewProj);

	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	
	o.diffuse = float4(0,1,0,1);

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		
		CullMode = NONE;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
