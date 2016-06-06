#include <iostream>

#include "filepolicy.hpp"

void FilePolicy::write( const std::string& message )
{
	//std::cerr << message << std::endl;
	mStream << message;
	mStream.flush();
}
