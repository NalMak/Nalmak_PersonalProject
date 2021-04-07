#include "H_common.fxh"
#include "H_light.fxh"

DirectionalLight g_directionalLight;

texture g_diffuse;
texture g_normal;
texture g_depth;
texture g_cookTorrance;

sampler DiffuseSampler = sampler_state
{
	texture = g_diffuse;
};

sampler NormalSampler = sampler_state
{
	texture = g_normal;
};

sampler DepthSampler = sampler_state
{
	texture = g_depth;
};

sampler CookTorranceSampler = sampler_state
{
	texture = g_cookTorrance;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv :TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 emission : COLOR0;
	float4 light : COLOR1;
	float4 lightDepth : COLOR2;

};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.pos = float4(_in.pos, 1);
	o.uv = _in.uv;


	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 uvRT = _in.uv + float2(perPixelX, perPixelY);

	float4 diffuse = tex2D(DiffuseSampler, uvRT);
	float3 normal = tex2D(NormalSampler, uvRT).xyz;

	float2 depth = tex2D(DepthSampler, uvRT).xy;
	float4 worldPos = GetWorldPosFromDepth(depth, uvRT);

	float2 cookTorrance = tex2D(CookTorranceSampler, uvRT).xy;
	float f0 = cookTorrance.x;
	float roughness = cookTorrance.y;

	normal = normal * 2 - 1;
	normal = normalize(normal);
	float4 light = CalcLightInternal(g_directionalLight.base, g_cBuffer.worldCamLook, g_directionalLight.direction, worldPos.xyz, normal);


	float specular;
	if (normal.x == -1 && normal.y == -1 && normal.z == -1)
	{
		specular = 0;
	}
	else
	{
		float3 _N = normal;
		float3 _V = normalize(g_cBuffer.worldCamPos - worldPos.xyz);
		float3 _L = -g_directionalLight.direction;
		float _F0 = cookTorrance.x;
		float _Roughness = cookTorrance.y;

		specular = LightingGGX_Ref(_N, _V, _L, _F0, _Roughness);

	}
	

	
	///////////////////////////
	o.emission = light * specular;
	o.light = light;
	//o.lightDepth = 
	return o;
}

// implicit truncation of vector type


technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z °ª¿¡´ëÇÑ È°¿ë

		ZEnable = false;
		AlphaBlendEnable = true;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
