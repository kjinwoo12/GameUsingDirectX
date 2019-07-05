#include "SimpleTextClass.h"



SimpleTextClass::SimpleTextClass() {
}
 

SimpleTextClass::~SimpleTextClass() {
	
}


bool SimpleTextClass::CreateDeviceIndependentResources() {
	HRESULT result;

	result = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&m_pD2DFactory
	);

	if (!SUCCEEDED(result)) {
		return false;
	}

	result = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
	);

	if (!SUCCEEDED(result)) {
		return false;
	}

	m_wszText = L"Hello world using  DirectWrite!";
	m_textLength = (UINT32)wcslen(m_wszText);

	result = m_pDWriteFactory->CreateTextFormat(
		L"Gabriola",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		72.9F,
		L"en-us",
		&m_pTextFormat
	);
	if (!SUCCEEDED(result)) {
		return false;
	}

	result = m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	if (!SUCCEEDED(result)) {
		return false;
	}

	result = m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	if (!SUCCEEDED(result)) {
		return false;
	}

	return true;
}

bool SimpleTextClass::CreateDeviceResources(HWND hwnd) {
	RECT rect;
	GetClientRect(hwnd, &rect);

	D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);
	if (!m_pRenderTarget) {
		HRESULT result = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				hwnd,
				size
			),
			&m_pRenderTarget
		);

		if (!SUCCEEDED(result)) {
			return false;
		}
		result = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_pBrush
		);
		return true;
	}
	return false;
}

void SimpleTextClass::discardDeviceResources() {
	m_pRenderTarget->Release();
	m_pBrush->Release();
}

void SimpleTextClass::drawText(RECT rect, FLOAT dpiScaleX, FLOAT dpiScaleY) {
	D2D1_RECT_F layoutRect = D2D1::RectF(
		static_cast<FLOAT>(rect.left) / dpiScaleX,
		static_cast<FLOAT>(rect.top) / dpiScaleY,
		static_cast<FLOAT>(rect.right - rect.left) / dpiScaleX,
		static_cast<FLOAT>(rect.bottom - rect.top) / dpiScaleY
		);

	m_pRenderTarget->DrawText(
		m_wszText,
		m_textLength,
		m_pTextFormat,
		layoutRect,
		m_pBrush
	);


}