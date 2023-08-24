#pragma once

#include <Windows.h>
#include <list>

namespace event {

	// event categories (event::cateory::*)
	enum category : int {
		undefined_event = -1,
		resize_event = 0,
		keybd_event = 1,
		mouse_event = 2
	};

	// in order to keep the inclusion simple, the math will be done on the outside of the type
	struct type {
	public:

		category m_category{undefined_event};

		type( category a = undefined_event ) { m_category = a; }

	};

	/* for events that need info */
	struct resize_t : public type {
	public:

		unsigned int width = 0, height = 0;

		resize_t( ) : type( resize_event ) {}
	};

	struct keybd_t : public type {
	public:

		unsigned int m_key{0};
		bool m_pressed{false};

		keybd_t( ) : type( keybd_event ) {}
	};

	struct mouse_t : public type {
	public:

		unsigned int x{0}, y{0};

		mouse_t( ) : type( mouse_event ) {}
	};

	// now comes the types of classes handling the dispatched events
	/*
	* the handler() function should be called as the register function, 
	* the progrma assumes you control the memory of the handler object
	* so the ~handler() acts as a de-register call
	* - normally register the handler on the allocation of parent() 
	*/

	class handler;

	class manager {
	private:

		std::list<handler*> m_handlers;

	public:

		void execute_event( type* );

		void register_handler( handler* );
		void deregister_handler( handler* );

	};

	extern manager g_manager;

	class handler {
	public:

		handler( );
		~handler( );

		virtual bool should_handle( type* ) = 0;
		virtual bool do_handle( type* ) { return false; }

	};


}