#include "wndproc.h"

namespace wndproc {

	LRESULT handler( HWND wnd, UINT msg, WPARAM w, LPARAM l ) {

		return DefWindowProc( wnd, msg, w, l );

	}
}