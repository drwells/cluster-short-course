#include <libraryone/helloint/hello.h>

#include <iostream>

namespace librarytwo
{
    void write_integer(const int i)
    {
        write_hello(i + 1);
    }
}
