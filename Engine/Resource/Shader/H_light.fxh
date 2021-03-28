struct BaseLight
{
	float3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct PointLight
{
	BaseLight base;

	float3 position;
	float radius;
};

struct DirectionalLight
{
	BaseLight base;

	float3 direction;
};

float4 CalcLightInternal(BaseLight _light, float3 _camPos, float3 _direction, float3 _worldPos, float3 _normal)
{
	float4 ambientColor = float4(_light.color * _light.ambientIntensity, 1.0);
	float diffuseFactor = dot(_normal, -_direction);

	float4 diffuseColor = 0;

	if (diffuseFactor > 0.0)
	{
		diffuseColor = float4(_light.color * _light.diffuseIntensity * diffuseFactor, 1.0);
		//float3 vertexToEye = normalize(_camPos - _worldPos);
	}

	//return ambientColor + diffuseColor;
	return diffuseColor * diffuseFactor + ambientColor;
}

float4 CalcPointLight(PointLight _pointLight,float3 _camPos, float3 _worldPos, float3 _normal)
{
	float3 lightDirection = _worldPos - _pointLight.position;
	float distance = length(lightDirection);

	lightDirection = normalize(lightDirection);

	float4 color = CalcLightInternal(_pointLight.base, _camPos, lightDirection, _worldPos, _normal);
	float attention = pow((_pointLight.radius - distance) / _pointLight.radius, 2);
	color = color * attention;
	color.w = 1;

	return  color;//*(distance - _pointLight.radius) /*/ _pointLight.radius;
}

float G1V(float _dotNV, float _k)
{
	return 1.0f / (_dotNV * (1.0f - _k) + _k);
}

float LightingGGX_Ref(float3 _N, float _V, float3 _L, float _F0, float _Roughness)
{
	float alpha = _Roughness * _Roughness;

	float3 H = normalize(_V + _L);

	float dotNL = saturate(dot(_N, _L));
	float dotNV = saturate(dot(_N, _V));
	float dotNH = saturate(dot(_N, H));
	float dotLH = saturate(dot(_L, H));

	float F; // Fresnel
	float D; // GGX ref
	float V; // smith's schlick

	float alphaSqr = alpha * alpha;
	const float PI = 3.141592f;
	float denom = dotNH * dotNH * (alphaSqr - 1.0) + 1.0f;
	D = alphaSqr / (PI * denom * denom);

	float dotLH5 = pow(1.0f - dotLH, 5);
	F = _F0 + (1.0 - _F0) * dotLH5;


	float k = alpha / 2.0f;
	V = G1V(dotNL, k) * G1V(dotNV, k);

	float specular = dotNL * D * F * V;

	return specular;
}