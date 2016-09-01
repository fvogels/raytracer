#define LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

void beep()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    MessageBeep(MB_ICONINFORMATION);
#else
    std::cout << '\a';
#endif
}
