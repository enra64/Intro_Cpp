#pragma once

#include "policy.hpp"
#include <fstream>

// TODO: Write a FilePolicy which inherits from Policy!
// The Policy must have a constructor which takes a file name where the log
// should be written.
// A good choice for file output would be ofstream. Have a look at the flush()
// command and use it.
// Check for errors.
class FilePolicy: public Policy
{
public:
    FilePolicy(std::string file){
        mStream = std::ofstream("log.txt");
    }
    
	virtual void write( const std::string& message ) override;
private:
    std::ofstream mStream;
};
