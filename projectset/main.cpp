#include <Windows.h>

#include "engine/windows/windows.h"
#include "engine/errors/errors.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int cmd_show) {

	// windows entry point

	// needs to be set before calling create canvas
	windows.g_instance = instance;

	// this would be strange, never the less!
	if ( !windows.create_fullscreen_canvas( ) )
	{
		error.notify( "failed to create window" );
		return -1;
	}


	MSG msg{};
	BOOL avail{FALSE};

	for ( ;; avail = PeekMessageA( &msg, windows.g_data.canvas_window, 0, 0, PM_REMOVE ) ) {

		if ( avail ) {
			TranslateMessage( &msg );
			DispatchMessageA( &msg );
		}


		/* now it is frame time */
	}

	return 0;

}