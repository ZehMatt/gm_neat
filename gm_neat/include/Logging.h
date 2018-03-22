#ifndef _LOGGING_H_
#define _LOGGING_H_

#define ENABLE_LOG 1 

#if defined(ENABLE_LOG) && ENABLE_LOG 

#include <windows.h>
#include <conio.h>

#define logPrint(fmt, ...) _cprintf(fmt, __VA_ARGS__)

#else 

#define logPrint(fmt, ...)

#endif

#endif // _LOGGING_H_