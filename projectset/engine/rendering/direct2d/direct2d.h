#pragma once

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#include <d2d1.h>
#include <dwrite.h>
#include <Windows.h>
#include <string>

#include "../../color/color.h"
#include "../../events/eventsystem/eventsystem.h"

namespace rendering {

	enum e_text_flags : DWORD {
		no_text_flags = 0x0
	};

	class c_rendering : event::handler {
	private:

		ID2D1Factory* m_factory;

		IDWriteFactory* m_direct_write_factory;

		ID2D1HwndRenderTarget* m_render_target;

		/*
		* for memory management brushes stored in a cute struct ;-;
		* 0x0 m_brushes
		* {
		* [] sizeof(void*) -> brush
		* }
		* sizeof(m_brushes)
		*/
		struct {
			ID2D1SolidColorBrush* m_solid_brush;
		} m_brushes;

		
	public:

		bool allocate_resources( );
		bool allocate_const_resources( );

		void release_resources( );
		void release_const_resources( );

		bool should_handle( event::type* );

		// called after dispatching messages - every frame
		void run_frame( void );

		void draw_text( std::wstring , int, int, color, DWORD, IDWriteTextFormat* );

	};
	
	extern c_rendering g_renderer;
}