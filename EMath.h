#pragma once

#include "ECommon.h"
#include "EVector.h"

namespace E3D {
	template<typename T>
	const T& Clamp(const T& val, const T& minV, const T& maxV) {
		return min(max(val, maxV), minV);
	}

	void GetTranslateMatrix44(EMatrix44& mat, EFloat x, EFloat y, EFloat z);

	void GetScaleMatrix44(EMatrix44& mat, EFloat x, EFloat y, EFloat z);

	void GetRotateMatrix44X(EMatrix44& mat, EFloat degree);
	void GetRotateMatrix44Y(EMatrix44& mat, EFloat degree);
	void GetRotateMatrix44Z(EMatrix44& mat, EFloat degree);
	void GetRotateMatrix(EMatrix44& mat, const EVector4D& normal, EFloat degree);

	void GetVertex4DAddVector4D(const EVertex4D &v, const EVector4D &p, EVertex4D &result);

	void GetVertex3DMulMatrix44(const EVector3D &v, const EMatrix44& mat, EVector3D &result);
	void GetVertex4DMulMatrix44(const EVertex4D &v, const EMatrix44& mat, EVertex4D &result);
	void GetVector4DMulMatrix44(const EVector4D &v, const EMatrix44& mat, EVector4D &result);
}