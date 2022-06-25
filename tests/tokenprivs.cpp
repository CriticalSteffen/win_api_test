/* AdjustTokenPrivileges() test implementation. */

#include "tests.h"

#include "../lib/libs.h" /* logf, log_error, pause */

#include <windows.h>
/* AdjustTokenPrivileges
 * LookupPrivilegeValue
 * GetLastError
 */
#include <processthreadsapi.h> /* OpenProcessToken, GetCurrentProcess */

void run_adjusttokenprivileges_test()
{
    HANDLE token = NULL;
    if (!OpenProcessToken(
        GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES,
        &token
    )) {
        log_error("OpenProcessToken");
        return;
    }
    TOKEN_PRIVILEGES privileges = {0};
    privileges.PrivilegeCount = 1;
    if (!LookupPrivilegeValue(
        NULL,
        SE_DEBUG_NAME,
        &privileges.Privileges[0].Luid
    )) {
        log_error("LookupPrivilegeValue");
        return;
    }
    
    pause();
    privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if (!AdjustTokenPrivileges(token, FALSE, &privileges, 0, NULL, NULL)) {
        log_error("AdjustTokenPrivileges");
        return;
    }
    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        logf("(AdjustTokenPrivileges) Not all privileges were assigned");
    } else {
        logf("(AdjustTokenPrivileges) All privileges were assigned");
    }
}