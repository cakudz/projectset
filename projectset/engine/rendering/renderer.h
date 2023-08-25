#pragma once

#include <dwrite.h>
#include <string>

#include "../color/color.h"

class renderer {
public:
	static renderer* get( ) {
		static renderer* instance = new renderer( );

		return instance;
	}

	// same with fonts !!! bery cool
	struct {

		struct {

			IDWriteTextFormat* m_text_format;

		} m_medium;

	} m_fonts;

	void draw_text( std::wstring, int, int, color, DWORD, IDWriteTextFormat* );
};