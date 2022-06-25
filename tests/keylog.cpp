/* GetAsyncKeyState(), GetKeyboardState() and GetKeyState() test
 * implementations.
 */

#include "tests.h"

#include "../common/util.h" /* log, lofg, log_error, pause */

#include <windows.h> /* GetAsyncKeyState, GetKeyboardState, GetKeyState */

void run_getasynckeystate_test()
{
    pause();
    if (GetAsyncKeyState(VK_CONTROL) < 0) {
        log("(GetAsyncKeyState) Control is pressed.");
    } else {
        log("(GetAsyncKeyState) Control is not pressed.");
    }
}

void run_getkeyboardstate_test()
{
    BYTE keyboardState[256] = {0};
    pause();
    if (GetKeyboardState(keyboardState) == 0) {
        log_error("GetKeyboardState");
        return;
    }
    logf(
        "(GetKeyboardState) Control is %s.",
        keyboardState[VK_CONTROL] & 0x81 ? "not pressed" : "pressed"
    );
}

void run_getkeystate_test()
{
    pause();
    if (GetKeyState(VK_CONTROL) < 0) {
        log("(GetKeyState) Control is pressed.");
    } else {
        log("(GetKeyState) Control is not pressed.");
    }
}