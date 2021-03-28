#include "H_common.fxh"

texture g_mainTex;


sampler mainSampler = sampler_state
{
	texture = g_mainTex;

};

struct VS_INPUT
{
	float3 position : POSITION;
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
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.position = float4(_input.position, 1);
	o.uv = _input.uv;
	//o.normal = float3(0, 0, 1);
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float2 uv = float2(_input.uv) + float2(perPixelX, perPixelY);
		
	float4 diffuse = tex2D(mainSampler, uv);
	o.diffuse = diffuse;

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		//ZEnable = true;
		//ZWriteEnable = true;
		//CullMode = NONE;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
