#pragma once
#include "ECommon.h"
#include "EVector.h"

namespace E3D {
	enum LIGHT_TYPE {
		LIGHT_AMBIENT = 0,
		LIGHT_DIRECTION = 1,
		LIGHT_POINT = 2
	};

	struct ELight {
		EInt id;
		EBool lighton;
		LIGHT_TYPE lightType;
		EFloat power;
		EFloat shadowFactor;

		EColor ambient;
		EColor diffuse;
		EColor specular;

		EVector4D position;
		EVector4D direction;

		EVector4D transPosition;
		EVector4D transDirection;

		EFloat kc, kl, kq;

		EFloat spot_inner;
		EFloat spot_outer;

		EFloat pt;

		ELight(EInt lightId, LIGHT_TYPE type);
	};

#define MAX_LIGHTS 8

	extern std::vector<ELight*> *GLights;

	typedef std::vector<ELight*>::iterator LightItr;

	extern EInt CreateLight(LIGHT_TYPE lightType);
	extern ELight* GetLight(EInt lightId);
	extern EInt GetLightSize();

	extern void DestroyAllLights();
}