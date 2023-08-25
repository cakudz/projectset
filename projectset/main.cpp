#include <Windows.h>
#include <chrono>
#include <memory>

#include "engine/windows/windows.h"
#include "engine/errors/errors.h"
#include "engine/rendering/direct2d/direct2d.h"
#include "engine/globals/globals.h"
#include "engine/events/eventsystem/eventsystem.h"
#include "app/scene/scene.h"
#include "app/login/login.h"

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

	LARGE_INTEGER frequency;// ticks per second

	// get ticks per second
	QueryPerformanceFrequency( &frequency );

	// start timer
	LARGE_INTEGER begin;
	QueryPerformanceCounter( &begin );
	scene::g_manager = std::make_unique<scene::manager>( );
	/* scene manager setting up and setting scene */
	std::unique_ptr<login::c_login_scene> login_ctx = std::make_unique<login::c_login_scene>( );
	scene::g_manager.get()->change_context( login_ctx.get() );

	for ( ;; avail = PeekMessageA( &msg, windows.g_data.canvas_window, 0, 0, PM_REMOVE ) ) {

		if ( avail ) {
			TranslateMessage( &msg );
			DispatchMessageA( &msg );
		}

		LARGE_INTEGER end;
		QueryPerformanceCounter( &end );

		// compute and print the elapsed time in millisec
		global::frame_time += (end.QuadPart - begin.QuadPart) * 1.f / frequency.QuadPart;

		QueryPerformanceCounter( &begin );

		/* send out a update event / anim / physics sim */
		auto event  = event::update_t();
		event::g_manager.execute_event( &event );

		/* now it is frame time */
		rendering::g_renderer.run_frame( );

	}

	// release system memory
	rendering::g_renderer.release_resources( );
	rendering::g_renderer.release_const_resources( );

	return 0;

}