#pragma once

#pragma comment(lib, "d2d1")

#include <d2d1.h>
#include <Windows.h>

namespace rendering {

	class c_rendering {
	private:

		ID2D1Factory* m_factory;
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

		void resize( );

		// called after dispatching messages - every frame
		void run_frame( void );

	};
	
	extern c_rendering g_renderer;
}