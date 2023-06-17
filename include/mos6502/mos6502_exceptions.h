#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>

namespace mos6502
{

static char ram_access_fail[32] = "\nFAILED: Illegal access to RAM\n";
static char stk_empty[30] = "\nFAILED: Stack already empty\n";
static char stk_full[29] = "\nFAILED: Stack already full\n";

class RAMException : public std::exception
{
private:
    char* message;

public:
    explicit RAMException(char*);
    ~RAMException();
    virtual const char* what() const noexcept;
};
};

#endif   // EXCEPTIONS_H_