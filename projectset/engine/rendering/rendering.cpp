#include "renderer.h"
#include "direct2d/direct2d.h"

void renderer::draw_text( std::wstring string, int x, int y, color col, DWORD tf, IDWriteTextFormat* font ) {
	rendering::g_renderer.draw_text( string, x, y, col, tf, font );
}