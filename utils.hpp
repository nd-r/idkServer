#ifndef IDK_UTILS_HPP
#define IDK_UTILS_HPP

#define UNUSED(expr) do { (void)(expr); } while (false)

#include <fcntl.h>

int setNonblocking(int fd);

#endif //IDK_UTILS_HPP
