#include "wndproc.h"
#include "../../rendering/direct2d/direct2d.h"

namespace wndproc {

	LRESULT handler( HWND wnd, UINT msg, WPARAM w, LPARAM l ) {

		switch ( msg ) {

		// will return from this switch case in every caught case
		case WM_SIZE: {

			// renderer needs to re-size
			rendering::g_renderer.resize( );
			return 0;
		} 

		}
		return DefWindowProc( wnd, msg, w, l );

	}
}