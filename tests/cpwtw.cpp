/* CreateProcessWithTokenW() test implementation. */

#include "tests.h"
#include "../lib/libs.h"

#include <windows.h>
#include <processthreadsapi.h>
#include <stdio.h>

void log_error(const char *func_name);
void run_cpwtw_test();

void run_cpwtw_test()
{
    HANDLE hProcessToken, hDuplicateToken;
    STARTUPINFOW suInfo;
    PROCESS_INFORMATION pInfo;

    log("(run_cpwtw_test) Preparing test...");

    ZeroMemory(&suInfo, sizeof(suInfo));
    ZeroMemory(&pInfo, sizeof(pInfo));

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
    Sleep(2000);

    // Create the new process.
    log("(CreateProcessWithTokenW) Creating new `calc.exe` process...");
    if (CreateProcessWithTokenW(hDuplicateToken, LOGON_WITH_PROFILE, L"C:\\Windows\\System32\\calc.exe", NULL, 0, NULL, NULL, &suInfo, &pInfo))
    {

        char message[256] = {0};
        sprintf(message, "(CreateProcessWithTokenW) Process created: %d", pInfo.dwProcessId);
        log(message);

        // Sleep to break up the log.
        Sleep(2000);

        log("(TerminateThread) Terminating thread...");
        if (TerminateThread(pInfo.hThread, 0))
        {
            log("(TerminateThread) Thread terminated.");
        } else {
            log_error("TerminateThread");
        }

        log("(TerminateProcess) Killing process...");
        if (TerminateProcess(pInfo.hProcess, 0))
        {
            log("(TerminateProcess) Process killed.");
        } else {
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

void log_error(const char *func_name)
{
    char error_msg[256] = {0};
    sprintf(error_msg, "(%s) Failed with error code: %d.", func_name, GetLastError());
    log(error_msg);
}