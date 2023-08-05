#include "errors.h"

c_errors error;

void c_errors::notify( std::string msg ) {

	/* the msg in this context is provided to the user, and also logged in the file
	   irp will get trapped waiting for user here however. */

	MessageBoxA( NULL, "set: an error has occured", msg.c_str( ), MB_OK );

	log( msg );

}

void c_errors::log( std::string msg ) {

	/* 
	 this function is for when an error is not serious
	 but it is interpreted that this error could lead to another
	 so it is useful to log some minor errors to a file that could contribute to
	 a larger error
	*/

	// make this function after made saving and loading of data handler
}