/* CreateToolHelp32Snapshot() test implementation. */

#include "tests.h"

#include "../lib/libs.h" /* log, log_error, pause */

#include <windows.h> /* CloseHandle */
#include <tlhelp32.h> /* CreateToolHelp32Snapshot */

void run_createtoolhelp32snapshot_test()
{
    pause();
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        log_error("CreateToolhelp32Snapshot");
        return;
    }
    log("(CreateToolhelp32Snapshot) Snapshot created.");
    CloseHandle(hSnapshot);
}