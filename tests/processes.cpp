/* AdjustTokenPrivileges() and CreateProcessWithTokenW() test implementations.
 */

#include "tests.h"

#include "../common/util.h" /* logf, log_error, pause */

#include <windows.h>
/* AdjustTokenPrivileges
 * CloseHandle
 * CreateProcessWithTokenW
 * GetLastError
 * LookupPrivilegeValue
 * Sleep
 */
#include <processthreadsapi.h>
/* OpenProcessToken
 * DuplicateTokenEx
 * GetCurrentProcess
 * TerminateProcess
 */

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
        logf("(AdjustTokenPrivileges) Not all privileges were assigned.");
    } else {
        logf("(AdjustTokenPrivileges) All privileges were assigned.");
    }
}

void run_createprocesswithtokenw_test()
{
    HANDLE hProcessToken, hDuplicateToken;
    STARTUPINFOW suInfo = {0};
    PROCESS_INFORMATION pInfo = {0};

    suInfo.cb = sizeof(suInfo);
    
    // Get the token of the current process.
    if (!OpenProcessToken(
        GetCurrentProcess(), TOKEN_ALL_ACCESS, &hProcessToken
    )) {
        log_error("OpenProcessToken");
        return;
    }

    // Duplicate the token.
    if (!DuplicateTokenEx(
        hProcessToken,
        TOKEN_ALL_ACCESS,
        NULL,
        SecurityImpersonation,
        TokenPrimary,
        &hDuplicateToken
    )) {
        log_error("DuplicateTokenEx");
        return;
    }

    // Create the new process.
    pause();
    if (CreateProcessWithTokenW(
        hDuplicateToken,
        LOGON_WITH_PROFILE,
        L"C:\\Windows\\System32\\notepad.exe",
        NULL,
        0,
        NULL,
        NULL,
        &suInfo,
        &pInfo
    )) {
        logf(
            "(CreateProcessWithTokenW) Process created: %d",
            pInfo.dwProcessId
        );
        // Terminate the process.
        // Sleep(100); // Un-comment this line to pause before termination.
        if (!TerminateProcess(pInfo.hProcess, 0))
        {
            log_error("TerminateProcess");
        }
        
        CloseHandle(pInfo.hProcess);
        CloseHandle(pInfo.hThread);
    } else {
        log_error("CreateProcessWithTokenW");
    }

    CloseHandle(hProcessToken);
    CloseHandle(hDuplicateToken);
}