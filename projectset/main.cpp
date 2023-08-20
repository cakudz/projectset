#include <Windows.h>

#include "engine/windows/windows.h"
#include "engine/errors/errors.h"
#include "engine/rendering/direct2d/direct2d.h"

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

	// now let our renderer set up
	if ( !rendering::g_renderer.allocate_const_resources( ) || !rendering::g_renderer.allocate_resources( ) ) {
		error.notify( "failed to initialise renderer" );
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
		rendering::g_renderer.run_frame( );

	}

	// release system memory
	rendering::g_renderer.release_resources( );
	rendering::g_renderer.release_const_resources( );

	return 0;

}