#pragma once

#include <cmath>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

#include "E3DHeader.h"

namespace E3D{

	typedef int EInt;
	typedef bool EBool;
	typedef char EChar;
	typedef short EShort;
	typedef float EFloat;
	typedef double EDouble;
	typedef unsigned int EUint;
	typedef unsigned char EUchar;
	typedef unsigned short EUshort;
	typedef std::string EString;
	typedef std::wstring EWString;

	const EInt SCREEN_WIDTH = 1024;
	const EInt SCREEN_HEIGHT = 800;

	const EString DEFAULT_NAME = "E3D_Default";
	const EString DefaultPath = "Media/";

	static EString GetPath(const EString& file) { return DefaultPath; }

#define PI  3.141592654f
#define PI2 (PI * 2)
#define PI_DIV_2 (PI * 0.5f)
#define PI_DIV_4 (PI * 0.25f)
#define PI_INV  0.318309886f

#define EPSILON_E6 (EFloat)(1E-6)

#define Degree_To_Radian(deg)   (deg * 0.017453f)
#define Radian_To_Degree(rad)   (rad * 57.295780f)

#define Abs(a)  ((a) > 0 ? (a) : -(a))

#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0 )
#define KEY_UP(vk_code)   ( (GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0 )

#define SafeDelete(ptr)        if(ptr)   { delete ptr; ptr = 0; }
#define SafeDeleteArray(ptr)   if(ptr)   { delete[] ptr; ptr = 0; }

#define COUT(a)    std::out<< #a << " : " << (a) << std::endl;

#define ECOLOR_16BIT(r,g,b)  (((r) & 0xff) << 16 | ((g) & 0xff) << 8 | (b) & 0xff )

	struct EColor {
		EUchar r, g, b, a;
		EColor(EInt color, EUchar alpha = 255) {
			r = (unsigned char)((color & 0xff0000) >> 16);
			g = (unsigned char)((color & 0x00ff00) >> 8);
			b = (unsigned char)(color & 0x0000ff);
			a = alpha;
		}

		EColor(EUchar ri = 0, EUchar gi = 0, EUchar bi = 0, EUchar ai = 255) : r(ri), g(gi), b(bi), a(ai) {}
	};
}