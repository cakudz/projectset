#pragma once

#include <Windows.h>
#include <list>
#include <memory>

#include "../../engine/events/eventsystem/eventsystem.h"

namespace scene {

	/* this will be the header for the scene / gui context / screen / wwhatever u want to call it */
	class context {
	public:

		// for the scene to render
		virtual void frame( ) = 0;

		// any memory management for the scene
		virtual void scene_show( ) = 0;
		virtual void scene_hide( ) = 0;

	};

	class manager : event::handler {
	private:

		context* m_current_context{nullptr};

	public:

		void change_context( context* );

		bool should_handle( event::type* );
		
	};

	extern std::unique_ptr<manager> g_manager;
}