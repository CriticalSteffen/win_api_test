/* Timing library implementation. */

#include "libs.h"

#include <windows.h> /* Sleep */

const int DELAY_MS = 2000;

void pause()
{
    Sleep(DELAY_MS);
}