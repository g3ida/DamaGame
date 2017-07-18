#include "Utils.h"

void mySleep(int sleepMs)
{
#ifdef POSIX
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN64
    Sleep(sleepMs);
#endif
#ifdef _WIN32
    Sleep(sleepMs);
#endif
}
