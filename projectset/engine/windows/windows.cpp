#include "windows.h"

#include "../events/wndproc/wndproc.h"

c_windows windows;

bool c_windows::create_fullscreen_canvas( ) {

	WNDCLASS wc{};

	wc.lpfnWndProc = wndproc::handler;
	wc.hInstance = this->g_instance;
	wc.lpszClassName = this->g_data.class_name;

	RegisterClass( &wc );

	HWND wnd = CreateWindowEx( 0, this->g_data.class_name,
		this->g_data.window_name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, this->g_instance, nullptr );

	if ( wnd == NULL || wnd == INVALID_HANDLE_VALUE )
		return false;

	this->g_data.canvas_window = wnd;

	ShowWindow( this->g_data.canvas_window, SHOW_FULLSCREEN );

	return true;

}