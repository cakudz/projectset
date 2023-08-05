#pragma once

#include <Windows.h>

class c_windows {
public:
	// instance recieved through WinMain
	HINSTANCE g_instance;

	/* below is the windows information related to the applications window */
	struct {

		// set this at compile time, refer to it later
		LPCWSTR class_name = L"set23";
		LPCWSTR window_name = L"project set";

		HWND canvas_window{ NULL };

	} g_data;

	// function to create a fullscreen 'canvas' more than a window 
	// because we arent using default windows conventions ( cracking becomes harder ! )
	bool create_fullscreen_canvas( );

};

extern c_windows windows;