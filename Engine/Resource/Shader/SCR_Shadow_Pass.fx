#include "H_common.fxh"
#include "H_light.fxh"

DirectionalLight g_directionalLight;

texture g_depth;
texture g_lightDepth;


sampler DepthSampler = sampler_state
{
	texture = g_depth;
};
sampler LightDepthSampler = sampler_state
{
	texture = g_lightDepth;
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
	float2 uv :TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	o.position = float4(_input.position, 1);
	o.uv = _input.uv;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 uv = float2(_input.uv) + float2(perPixelX, perPixelY);


	float2 depth = tex2D(DepthSampler, uv).xy;
	float4 worldPos = GetWorldPosFromDepth(depth, uv);
	float4 lightPos = mul(worldPos, g_directionalLight.viewProj);

	float2 shadowUV;

	shadowUV.x = saturate((lightPos.x / lightPos.w) * 0.5f + 0.5f);
	shadowUV.y = saturate(-(lightPos.y / lightPos.w) * 0.5f + 0.5f);

	

	float4 lightDepth = tex2D(LightDepthSampler, shadowUV);
	float lightDistance = lightDepth.x * zFar;
	float objDistance = length(worldPos - g_directionalLight.base.position);

	float adjust = 0;// shadowDistance / 10;

	float4 color = 1.f;
	if (lightDistance > objDistance * 0.99f)
	{
		color.xyz = 1;
	}
	else
		color = 0;
	//color.xyz = lightDepth;
	/*if (length(worldPos - float4(g_cBuffer.worldCamPos, 1)) > zFar)
	{
		color.w = 0;
	}*/
	//color = lightDepth;
	//color = lightDepth;
	//color = lightDepth;
	//color = saturate(color + length(worldPos - float4(g_cBuffer.worldCamPos,1)) / zFar);
	//o.color = objDistance / zFar;
	color.w = 1;
	//o.color.xyz = lightDepth + depth;
	o.color = color;
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
