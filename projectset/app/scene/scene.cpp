#include "scene.h"

namespace scene {

	std::unique_ptr<manager> g_manager;

	// make sure any context change occurs outside of any rendering code 
	// that would reference current context otherwise we might have a few bugs
	void manager::change_context( context* ctx ) {

		if ( this->m_current_context != nullptr )
			this->m_current_context->scene_hide( );

		this->m_current_context = ctx;

		ctx->scene_show( );
	}


	bool manager::should_handle( event::type* event ) {
		if ( event->m_category != event::render_event )
			return false;

		/* we are rendering now hallileuyah or something */
		this->m_current_context->frame( );

		return false;
	}



}