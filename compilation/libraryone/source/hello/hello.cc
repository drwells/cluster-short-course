#include <libraryone/base/config.h>


#ifdef LIBRARYONE_HAVE_ROMIO
#include <rom.io/base/romio.h>
#endif // LIBRARYONE_HAVE_ROMIO

#include <libraryone/hello/hello.h>

#include <iostream>


void write_hello()
{
  std::cout << "hello, world\n";
}
