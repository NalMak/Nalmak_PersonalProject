#include "H_common.fxh"
#include "H_light.fxh"

texture g_skyBox;
DirectionalLight g_directionalLight;

samplerCUBE skyBoxSampler = sampler_state
{
	texture = <g_skyBox>;
	/*magfilter = LINEAR;
	minfilter = LINEAR;
	mipfilter = LINEAR;*/
	AddressU = Mirror;
	AddressV = Mirror;

};

struct VS_INPUT
{
	float3 position : POSITION;
	float3 uvw : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float3 uvw : TEXCOORD0;
};

struct PS_INPUT
{
	float3 uvw : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	matrix matWorld = 0;
	matWorld._11 = 1;
	matWorld._22 = 1;
	matWorld._33 = 1;
	matWorld._44 = 1;

	matWorld._41 = g_cBuffer.worldCamPos.x;
	matWorld._42 = g_cBuffer.worldCamPos.y;
	matWorld._43 = g_cBuffer.worldCamPos.z;

	matrix wvp = mul(matWorld, g_cBuffer.viewProj);
	o.position = mul(float4(_input.position ,1), wvp).xyww;
	o.uvw = _input.uvw;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	//float diffuseFactor = max(dot(float3(0, 1, 0), -g_directionalLight.direction),0) + 0.2f;
	o.diffuse = texCUBE(skyBoxSampler, _input.uvw);// *diffuseFactor;
	//o.diffuse = float4(0.8f, 0.9f, 0.95f,1.f);
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		//ZEnable = false;
		//ZWriteEnable = false;
		alphaBlendEnable = false;
		alphaTestEnable = false;
		CullMode = CW;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
