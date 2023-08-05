#pragma once

#include <Windows.h>
#include <string>

class c_errors {
public:

	// notify the user
	void notify( std::string message );

	// less serious - log error in file
	void log( std::string );
};

extern c_errors error;