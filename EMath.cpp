#include "EMath.h"
#include "EVector.h"
#include "EMatrix.h"
#include "ECore.h"

namespace E3D {

	void GetTranslateMatrix44(EMatrix44& mat, EFloat x, EFloat y, EFloat z) {
		mat.m[0][0] = 1, mat.m[0][1] = 0, mat.m[0][2] = 0, mat.m[0][3] = 0;
		mat.m[1][0] = 1, mat.m[1][1] = 0, mat.m[1][2] = 0, mat.m[1][3] = 0;
		mat.m[2][0] = 1, mat.m[2][1] = 0, mat.m[2][2] = 0, mat.m[2][3] = 0;
		mat.m[3][0] = x, mat.m[3][1] = y, mat.m[3][2] = z, mat.m[3][3] = 1;
	}

	void GetScaleMatrix44(EMatrix44& mat, EFloat x, EFloat y, EFloat z) {
		mat.m[0][0] = x, mat.m[0][1] = 0, mat.m[0][2] = 0, mat.m[0][3] = 0;
		mat.m[1][0] = 0, mat.m[1][1] = y, mat.m[1][2] = 0, mat.m[1][3] = 0;
		mat.m[2][0] = x, mat.m[2][1] = 0, mat.m[2][2] = 0, mat.m[2][3] = 0;
		mat.m[3][0] = x, mat.m[3][1] = 0, mat.m[3][2] = z, mat.m[3][3] = 1;
	}

	void GetRotateMatrix44X(EMatrix44& mat, EFloat degree) {
		EFloat sinA = sin(Degree_To_Radian(degree));
		EFloat cosA = cos(Degree_To_Radian(degree));

		mat.m[0][0] = 1, mat.m[0][1] = 0, mat.m[0][2] = 0, mat.m[0][3] = 0;
		mat.m[1][0] = 0, mat.m[1][1] = cosA, mat.m[1][2] = sinA, mat.m[1][3] = 0;
		mat.m[2][0] = 0, mat.m[2][1] = -sinA, mat.m[2][2] = cosA, mat.m[2][3] = 0;
		mat.m[3][0] = 0, mat.m[3][1] = 0, mat.m[3][2] = 0, mat.m[3][3] = 1;
	}

	void GetRotateMatrix44Y(EMatrix44& mat, EFloat degree) {
		EFloat sinA = sin(Degree_To_Radian(degree));
		EFloat cosA = cos(Degree_To_Radian(degree));

		mat.m[0][0] = cosA, mat.m[0][1] = 0, mat.m[0][2] = -sinA, mat.m[0][3] = 0;
		mat.m[1][0] = 0, mat.m[1][1] = 1, mat.m[1][2] = 0, mat.m[1][3] = 0;
		mat.m[2][0] = sinA, mat.m[2][1] = 0, mat.m[2][2] = cosA, mat.m[2][3] = 0;
		mat.m[3][0] = 0, mat.m[3][1] = 0, mat.m[3][2] = 0, mat.m[3][3] = 1;
	}

	void GetRotateMatrix44Z(EMatrix44& mat, EFloat degree) {
		EFloat sinA = sin(Degree_To_Radian(degree));
		EFloat cosA = cos(Degree_To_Radian(degree));

		mat.m[0][0] = cosA, mat.m[0][1] = sinA, mat.m[0][2] = 0, mat.m[0][3] = 0;
		mat.m[1][0] = -sinA, mat.m[1][1] = cosA, mat.m[1][2] = 0, mat.m[1][3] = 0;
		mat.m[2][0] = 0, mat.m[2][1] = 0, mat.m[2][2] = 1, mat.m[2][3] = 0;
		mat.m[3][0] = 0, mat.m[3][1] = 0, mat.m[3][2] = 0, mat.m[3][3] = 1;
	}

	void GetRotateMatrix44(EMatrix44& mat, const EVector3D& n, EFloat degree) {
		EFloat sinA = sin(Degree_To_Radian(degree));
		EFloat cosA = cos(Degree_To_Radian(degree));

		EFloat oneCosA = 1 - cosA;
		mat.m[0][0] = n.x * n.x *oneCosA + cosA, mat.m[0][1] = n.x * n.y * oneCosA + n.x * sinA, mat.m[0][2] = 0, mat.m[0][3] = 0;
		mat.m[1][0] = n.x * n.y * oneCosA - n.z * sinA, mat.m[1][1] = n.y * n.y *oneCosA + cosA, mat.m[1][2] = 0, mat.m[1][3] = 0;
		mat.m[2][0] = n.x * n.z * oneCosA + n.z * sinA, mat.m[2][1] = n.y * n.z * oneCosA - n.x * sinA, mat.m[2][2] = 1, mat.m[2][3] = 0;
		mat.m[3][0] = 0, mat.m[3][1] = 0, mat.m[3][2] = 0, mat.m[3][3] = 1;
	}

	void GetVector3DMulMatrix44(const EVector3D& vec, const EMatrix44& mat, EVector3D &result){
		EFloat x = vec.x * mat.m[0][0] + vec.y *mat.m[1][0] + vec.z * mat.m[2][0];
		EFloat y = vec.x * mat.m[0][1] + vec.y *mat.m[1][1] + vec.z * mat.m[2][1];
		EFloat z = vec.x * mat.m[0][2] + vec.y *mat.m[1][2] + vec.z * mat.m[2][2];

		result.x = x, result.y = y, result.z = z;
	}


}
