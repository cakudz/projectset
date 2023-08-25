#pragma once

#include <Windows.h>
#include "../scene/scene.h"

namespace login {

	class c_login_scene : public scene::context {

		void frame( );
		void scene_show( );
		void scene_hide( );

	};
}