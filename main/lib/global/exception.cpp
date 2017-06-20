#ifndef EXCEPTION_CPP_INCLUDED
#define EXCEPTION_CPP_INCLUDED

NotImplementedException::NotImplementedException (char* message):
    logic_error(message){}

#endif // EXCEPTION_CPP_INCLUDED
