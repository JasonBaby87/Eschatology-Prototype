#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include <stdexcept>

class NotImplementedException: public std::logic_error
{
private:
	const char* message;
public:
	NotImplementedException (char* = "Function not implemented.");
};

#endif // EXCEPTION_H_INCLUDED
