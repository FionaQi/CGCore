#pragma once
#include "ECommon.h"
#include <map>
#include "EGraphics.h"

namespace E3D {

	struct EMaterial {
		EString name;
		EColor ambient; //environment
		EColor diffuse;
		EColor specular;

		EBitmap *bitmap;

		EMaterial();
		~EMaterial();
		inline bool useTexture() { return bitmap && bitmap->isValid(); }
		EColor getPixel(EFloat x, EFloat y);
	};

	typedef std::map<EString, EMaterial*>::iterator MaterialIter;
	extern std::map<EString, EMaterial*> *GMaterials;   //we can use this pointer outside the class

	extern EMaterial *GetMaterial(const EString &name);
	extern bool SetMaterial(const EString &name, EMaterial *materail);
	extern bool DestroyMaterial(const EString &name);
	extern void DestroyAllMaterial();

	extern void ParseMaterialScript(const EString &scriptName);
}