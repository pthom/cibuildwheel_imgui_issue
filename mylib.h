#pragma once
#include <string>
#include <string.h>
#include <stdio.h>

struct Context
{
    inline Context()
    {
        printf("sizeof(std::string) = %zu\n", sizeof(std::string));
        // Warning, this will lead to a byg with the GNU/Linux std::string implementation
        // since it does *not* support to be zero-initialized!!!
        memset(this, 0, sizeof(*this));

        IniFilename = "mylib.ini";
    }
    std::string IniFilename;
};

inline Context* CreateContext()
{
    auto ctx = new Context();
    return ctx;
}
