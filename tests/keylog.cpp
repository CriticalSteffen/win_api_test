/* GetAsyncKeyState(), GetKeyboardState() and GetKeyState() test
 * implementations.
 */

#include "tests.h"

#include "../lib/libs.h" /* logf, log_delay, log_error */

#include <windows.h> /* GetAsyncKeyState, GetKeyboardState, GetKeyState */

void run_getasynckeystate_test()
{
    log_delay("GetAsyncKeyState");
    if (GetAsyncKeyState(VK_CONTROL) < 0) {
        logf("(GetAsyncKeyState) Control is pressed");
    } else {
        logf("(GetAsyncKeyState) Control is not pressed");
    }
}

void run_getkeyboardstate_test()
{
    log_delay("GetKeyboardState");
    BYTE keyboardState[256] = {0};
    if (!GetKeyboardState(keyboardState)) {
        log_error("GetKeyboardState");
        return;
    }
    if (keyboardState[VK_CONTROL]) {
        logf("(GetKeyboardState) Control is pressed");
    } else {
        logf("(GetKeyboardState) Control is not pressed");
    }
}

void run_getkeystate_test()
{
    log_delay("GetKeyState");
    if (GetKeyState(VK_CONTROL) < 0) {
        logf("(GetKeyState) Control is pressed");
    } else {
        logf("(GetKeyState) Control is not pressed");
    }
}