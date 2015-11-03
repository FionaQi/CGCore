#include "EGraphics.h"
#include "EUtil.h"

namespace E3D{
	EBitmap::EBitmap(const EString &filename) :name(filename), pixels(NULL),
		pitch(0), width(0), height(0), valid(false) 
	{
		hBitmap = (HBITMAP)::LoadImage(GHInstance, GetPath(filename).c_str(), IMAGE_BITMAP, 0, 0, fuload);
		if (hBitmap != nullptr) {
			bitmapHDC = ::CreateCompatibleDC(NULL);
			::SelectObject(bitmapHDC, (HGDIOBJ)hBitmap);
			::GetObject(hBitmap, sizeof(BITMAP), &bitmap);

			width = bitmap.bmWidth;
			height = bitmap.bmHeight;
			pitch = bitmap.bmHeight;
			valid = true;

			pixels = new EColor(width * height);
			for (EInt i = 0; i < getHeight(); i++) {
				for (EInt j = 0; j < getWidth(); j++) {
					COLORREF color = ::GetPixel(bitmapHDC, i, j);
					pixels[j * width + i] = EColor(GetRValue(color), GetBValue(color));
				}
			}
		}
	}

	EBitmap::~EBitmap() {
		DeleteObject(hBitmap);
		DeleteDC(bitmapHDC);
		SafeDeleteArray(pixels);
	}

	EColor EBitmap::getPixel(EInt x, EInt y) {
		return pixels[y * pitch + x];
	}

	HINSTANCE GHInstance;
	HBITMAP		EGraphics::GBufferHandle;
	HDC			EGraphics::GBufferedHDC;
	HBRUSH		EGraphics::GBgBrush;
	HPEN		EGraphics::GPen;
	HINSTANCE	EGraphics::GInstance;
	RECT		EGraphics::GBufferSize;
	DIBSECTION	EGraphics::GDiBSection;
	BYTE		*EGraphics::GDatas;
	EInt		EGraphics::GPitch;

	EFloat		*EGraphics::GZBuffer;

	bool EGraphics::initGraphics(HINSTANCE hinstance) {
		GBufferedHDC = ::CreateCompatibleDC(NULL);

		BITMAPINFO info = (0);
		info.bmiHeader.biSize = sizeof(info.bmiHeader);
		info.bmiHeader.biWidth = SCREEN_WIDTH;
		info.bmiHeader.biHeight = SCREEN_HEIGHT;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biSizeImage = SCREEN_WIDTH * SCREEN_HEIGHT * 32 / 8;

		void* pBits = NULL;
		GBufferHandle = ::CreateDIBSection(GBufferedHDC, &info, DIB_RGB_COLORS, &pBits, NULL, 0);
		::SelectObject(GBufferedHDC, GBufferHandle);

		::GetObject(GBufferHandle, sizeof(DIBSECTION), &GDiBSection);
		GDatas = (BYTE*)GDiBSection
	}
}