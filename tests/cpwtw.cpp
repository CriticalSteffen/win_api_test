/* CreateProcessWithTokenW() test implementation. */

#include "tests.h"
#include "../lib/libs.h"

#include <windows.h>
#include <processthreadsapi.h>
#include <stdio.h>

void run_cpwtw_test();

void run_cpwtw_test()
{
    HANDLE hProcessToken, hDuplicateToken;
    STARTUPINFOW suInfo = {0};
    PROCESS_INFORMATION pInfo = {0};

    log("(run_cpwtw_test) Preparing test...");

    suInfo.cb = sizeof(suInfo);
    
    // Get the token of the current process.
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hProcessToken)) {
        log_error("OpenProcessToken");
        return;
    }

    // Duplicate the token.
    if (!DuplicateTokenEx(hProcessToken, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &hDuplicateToken))
    {
        log_error("DuplicateTokenEx");
        return;
    }

    // Sleep to break up the log.
    Sleep(5000);

    // Create the new process.
    log("(CreateProcessWithTokenW) Creating new `notepad.exe` process...");
    if (CreateProcessWithTokenW(hDuplicateToken, LOGON_WITH_PROFILE, L"C:\\Windows\\System32\\notepad.exe", NULL, 0, NULL, NULL, &suInfo, &pInfo))
    {

        char message[256] = {0};
        sprintf(message, "(CreateProcessWithTokenW) Process created: %d", pInfo.dwProcessId);
        log(message);

        Sleep(100);
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