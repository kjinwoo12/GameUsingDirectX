#pragma once

#include<DWrite.h>

class TextClass {
public:
	TextClass();
	~TextClass();

private:
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

	const wchar_t* m_text;
	UINT32 m_textLength;
};

