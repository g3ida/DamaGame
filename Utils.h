#pragma once


#ifdef POSIX
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef _WIN64
#include <windows.h>
#endif


void mySleep(int sleepMs);
