#include "login.h"
#include "../../engine/rendering/renderer.h"
#include "../../engine/globals/globals.h"

namespace login {

	// rendering of the login screen
	void c_login_scene::frame( ) {
		auto r = renderer::get( );

		r->draw_text( std::to_wstring( global::frame_time ), 0, 0, color( 255.f, 255.f, 255.f, 255.f ), 0, r->m_fonts.m_medium.m_text_format );
	}

	// the login screen is displayed ( assume program just opened )
	void c_login_scene::scene_show( ) {

	}

	// when the user has passed the login screen? or window closed
	void c_login_scene::scene_hide( ) {

	}

}