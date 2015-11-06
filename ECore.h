#pragma once

#include "ECommon.h"
#include "EVector.h"
#include <list>

namespace E3D {
#define EPOLY_ATTR_2SIDE 0x0001
#define EPOLY_ATTR_TRANSPARENT 0x0002
#define EPOLY_ATTR_SHADE_MODE_PURE 0x0004
#define EPOLY_ATTR_SHADE_MODE_CONSTANT 0x0004
#define EPOLY_ATTR_SHADE_MODE_FLAT 0x0008
#define EPOLY_ATTR_SHADE_MODE_GROUND 0x0010
#define EPOLY_ATTR_SHADE_MODE_PHONG 0x0020
#define EPOLY_ATTR_SHADE_MODE_FASTPHONG 0x0020
#define EPOLY_ATTR_SHADE_MODE_TEXTURE 0x0040

#define EPOLY_ATTR_VERTEX_POSITION 0x1000
#define EPOLY_ATTR_VERTEX_NORMAL 0x2000
#define EPOLY_ATTR_VERTEX_UV 0x4000
#define EPOLY_STATE_ACTIVE 0x0100
#define EPOLY_STATE_CLIPPED 0x0200
#define EPOLY_STATE_BACKFACE 0x0400

#define EOBJECT_STATE_ACTIVE 0x0001
#define EOBJECT_STATE_VISIBLE 0x0002
#define EOBJECT_STATE_CULLED  0x0004

	struct EVertex4D;
	typedef std::vector<EVertex4D> EVertex4DArray;
	typedef std::vector<EVector4D> EVector4FArray;
	typedef std::vector<EPolyon4D> HPolyon4DArray;

	struct EVertex4D {
		EFloat x, y, z, w;
		EFloat u, v;

		EVertex4D();
		EVertex4D(const EVector4D &v);
		EVertex4D(EFloat xf, EFloat yf, EFloat zf);
		EVertex4D operator+(const EVector4D &right);
		EVertex4D operator-(const EVector4D &right);
		EVertex4D operator=(const EVector4D &right);
		EVertex4D operator*(const EVector4D &right);
		EVertex4D operator/(const EVector4D &right);

		EVertex4D toVector4D() const;
	};

	struct EPlane3D {
		EVector4D point;
		EVector4D normal;
		EPlane3D();
		EPlane3D(const EVector4D &normal);

	};

	struct EPolyon4D {
		EInt state;
		EInt attribute;
		EVertex4DArray *verlist;
		EInt verIndex[3];

		EPolyon4D();
	};

	struct EPolyonF4D{
		EInt state;
		EInt attribute;
		EInt color;

		EVertex4D localList[3];
		EVertex4D transformList[3];

		struct EMaterial *material;
		EPolyonF4D();
	};

	struct CompEPolyonF4D {
		EBool operator() (const EPolyonF4D &polyA, const EPolyonF4D & polyB) {
			EFloat zA = max(polyA.transformList[0].z, max(polyA.transformList[1].z, polyA.transformList[2].z));
			EFloat zB = max(polyB.transformList[0].z, max(polyB.transformList[1].z, polyB.transformList[2].z));

			if (Abs(zA - zB) < 0.005f) {
				zA = (polyA.transformList[0].z + polyA.transformList[1].z + polyA.transformList[2].z) / 3.0f;
				zB = (polyB.transformList[0].z + polyA.transformList[1].z + polyB.transformList[2].z) / 3.0f;

				if (zA <= zB)
					return false;
				else
					return true;
			}
			else if (zA < zB)
				return false;
			else
				return true;
		}
	};

	struct EObject4D {
		EString name;
		EInt state;
		EInt attribute;
		EFloat avgRadius;
		EFloat maxRadius;

		EBool needCull;
		EString materialName;
		EVector4D minBoundingBox;
		EVector4D maxBoundingBox;

		EVector4D worldPosition;
		EVector4D scale;

		EVector4D direction;

		EInt vertexNumber;
		EVector4DArray localList;
		EVector4DArray transformList;

		EInt polyonNumber;
		EPolyon4DArray polyonList;
		EObject4D *nextObject;

		EObject4D();
	};

	struct ERenderList4D {
		EInt state;
		EInt attribute;

		std::list<EPolyonF4D> polyData;
		typedef std::list<EPolyonF4D>::iterator Itr;
	};

	enum OBJ_TRANSFORM_TYPE {
		TRANSFORM_LOCAL = 0,
		TRANSFORM_TRANS = 1,
		TRANSFORM_LOCAL_TO_TRANS = 2
	};

	void Transform_Object4D(ERenderList4D* obj, const EMatrix44 &mat,
		OBJ_TRANSFORM_TYPE transformType);

	void Transform_Renderlist4D(ERenderList4D* renderList, EObject4D* obj,
		OBJ_TRANSFORM_TYPE transformType = TRANSFORM_LOCAL_TO_TRANS,
		bool transformScaleAndPosition = false);

	void Local_To_World_Object4D(EObject4D* obj, OBJ_TRANSFORM_TYPE transformType, );

	void Local_To_World_RenderList4D(ERenderList4D* renderList, const EVector4D &position,
		OBJ_TRANSFORM_TYPE transformType = TRANSFORM_LOCAL_TO_TRANS);

	bool Cull_Object4D(EObject4D *object, EFrustum *camera, CULL_TYPE);

	bool Remove_BackFace(EPolyonF4D *poly, EFrustum *camera);

	void Remove_Backface_Object4D(EObject4D *object, EFrustum *camera);

	void Remove_Backface_RenderList4D(ERenderList4D* renderList, EFrustum *camera);

	void Light_Polyon4D(EPolyonF4D* poly, EFrustum* camera);
	void Light_RenderList4D(ERenderList4D* renderList, EFrustum *camera);

	void World_To_Camera_Object4D(EObject4D* obj, EFrustum *camera);
	void World_To_Camera_RenderList4D(ERenderList4D* renderList, EFrustum* camera);

	void Sort_RenderList4D(ERenderList4D* renderList);

	void Camera_To_Perspective_Object4D(EObject4D *obj, EFrustum *camera);
	void Camera_To_Perspective_RenderList4D(ERenderList4D *renderList, EFrustum *camera);

	void Perspective_To_Screen_Object4D(EObject4D *obj, EFrustum* camera);
	void Perspective_To_Screen_RenderList4D(ERenderList4D* renderList, EFrustum* camera);

	void Clip_RenderList4D(ERenderList4D* renderList, EFrustum* camera);

	void World_To_Screen_RenderList4D(ERenderList4D* renderList, EFrustum* camera);

	void Draw_Object4D_Wire(EObject4D* obj);
	void Draw_RenderList4D_Wire(ERenderList4D* renderList);

	void Draw_Object4D_Solid(EObject4D *obj);
	void Draw_RenderList4D_Solid(ERenderList4D* renderList);

	void Draw_RenderList4D_Texture_Solid(ERenderList4D* renderList);

}