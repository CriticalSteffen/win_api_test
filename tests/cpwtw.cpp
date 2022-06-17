/* CreateProcessWithTokenW() test implementation. */

#include "tests.h"
#include "../lib/libs.h"

#include <windows.h>
#include <processthreadsapi.h>
#include <stdio.h>

void run_cpwtw_test()
{
    /* Launch `calc.exe` via `CreateProcessWithTokenW()`. */

    HANDLE hProcessToken, hDuplicateToken;
    STARTUPINFOW suInfo;
    PROCESS_INFORMATION pInfo;

    ZeroMemory(&suInfo, sizeof(suInfo));
    ZeroMemory(&pInfo, sizeof(pInfo));
    suInfo.cb = sizeof(suInfo);
    
    if (
        // Get a token for the current process.
        OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hProcessToken)
    ) {
        // Duplicate the token.
        DuplicateTokenEx(hProcessToken, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &hDuplicateToken);

        // Sleep to break up the log.
        Sleep(5000);

        // Create the new process.
        CreateProcessWithTokenW(hDuplicateToken, LOGON_WITH_PROFILE, L"C:\\Windows\\System32\\calc.exe", NULL, 0, NULL, NULL, &suInfo, &pInfo);

        // Ensure success.
        if (GetLastError() == ERROR_SUCCESS) {
            char message[256] = {0};
            sprintf(message, "(CreateProcessWithTokenW) Process created: %d", pInfo.dwProcessId);
            log(message);
            // Close process and thread handles.
            CloseHandle(pInfo.hProcess);
            CloseHandle(pInfo.hThread);
        } else {
            char error_msg[1024] = {0};
            sprintf(error_msg, "(CreateProcessWithTokenW) Failed to create process. Error: %d", GetLastError());
            log(error_msg);
        }
    } else {
        log("(CreateProcessWithTokenW) Failed to get process token.");
    }

    CloseHandle(hProcessToken);
    CloseHandle(hDuplicateToken);
}