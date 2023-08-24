#include "wndproc.h"
#include "../../rendering/direct2d/direct2d.h"
#include "../eventsystem/eventsystem.h"
#include <windowsx.h>

namespace wndproc {

	LRESULT handler( HWND wnd, UINT msg, WPARAM w, LPARAM l ) {

		switch ( msg ) {

		// will return from this switch case in every caught case
		case WM_SIZE: {

			// renderer needs to re-size
			event::resize_t resize_event {};
			resize_event.width = LOWORD( l );
			resize_event.height = HIWORD( l );

			event::g_manager.execute_event( &resize_event );

			return 0;
		} 

		case WM_KEYDOWN: {

			event::keybd_t keybd_event {};
			keybd_event.m_pressed = true;
			keybd_event.m_key = static_cast<unsigned int>(w);

			event::g_manager.execute_event( &keybd_event );

			return 0;
		}

		case WM_KEYUP: {

			event::keybd_t keybd_event {};
			keybd_event.m_pressed = false;
			keybd_event.m_key = static_cast<unsigned int>(w);

			event::g_manager.execute_event( &keybd_event );

			return 0;
		}

		case WM_MOUSEMOVE: {

			event::mouse_t mouse_event {};
			mouse_event.x = GET_X_LPARAM( l );
			mouse_event.y = GET_Y_LPARAM( l );

			event::g_manager.execute_event( &mouse_event );

			return 0;
		}

		}
		return DefWindowProc( wnd, msg, w, l );

	}
}