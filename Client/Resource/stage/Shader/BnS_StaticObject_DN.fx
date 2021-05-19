#include "../../../../Engine/Resource/Shader/H_common.fxh"

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

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
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
	float4 depth_cookTorrance : COLOR2;
	float4 specular : COLOR3;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	
	float4 worldPos = mul(float4(_in.pos, 1), g_world);
	o.pos = mul(worldPos, g_cBuffer.viewProj);

	o.T = LocalToWorldDirection(_in.tangent, g_world);
	o.B = LocalToWorldDirection(_in.binormal, g_world);
	o.N = LocalToWorldDirection(_in.normal, g_world);



	o.uvAndDepth.xy = _in.uv;
	o.uvAndDepth.zw = o.pos.zw;
	
	

	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;




	float4 diffuse = tex2D(mainSampler, _in.uvAndDepth.xy);
	o.diffuse = diffuse * g_mainTexColor;
	float3 normal = tex2D(normalSampler, _in.uvAndDepth.xy).xyz;
	normal = normal * 2 - 1;
	normal = normalize(normal);
	

	float3x3 tbn =
	{
		_in.T,
		_in.B,
		_in.N
	};
	normal = mul(normal , tbn) * g_normalPower + normal * (1 - g_normalPower);
	normal = normal * 0.5f + 0.5f;
	o.normal = float4(normal,1);


	o.depth_cookTorrance.xy = GetDepth(_in.uvAndDepth.zw);
	o.depth_cookTorrance.zw = float2(g_f0, g_roughness);
	
	o.specular = float4(0, 0, 0, 1);

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
		//CullMode = none;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
