#pragma once

#include<dwrite.h>
#include<d2d1.h>

class SimpleTextClass {
public:
	SimpleTextClass();
	~SimpleTextClass();

	bool CreateDeviceIndependentResources();
	bool CreateDeviceResources(HWND);
	void discardDeviceResources();

	void drawText(RECT, FLOAT, FLOAT);

private:
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	const wchar_t* m_wszText;
	UINT32 m_textLength;

	ID2D1Factory* m_pD2DFactory;
	ID2D1HwndRenderTarget *m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBrush;
};

