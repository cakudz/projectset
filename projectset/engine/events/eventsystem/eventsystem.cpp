#include "eventsystem.h"

namespace event {

	manager g_manager;

	void manager::execute_event( type* event ) {

		for ( auto v : this->m_handlers ) {
			if ( v->should_handle( event ) )
				if ( v->do_handle( event ) )
					return;
		}
	}

	void manager::register_handler( handler* handler ) {
		this->m_handlers.push_back( handler );
	}

	void manager::deregister_handler( handler* handler ) {
		this->m_handlers.remove( handler );
	}

	handler::handler( ) {
		g_manager.register_handler( this );
	}

	handler::~handler( ) {
		g_manager.deregister_handler( this );
	}
}