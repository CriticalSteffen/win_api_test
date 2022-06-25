/* GetIpNetTable() test implementation. */

#include "tests.h"

#include "../lib/libs.h" /* logf, log_error, pause */

#include <windows.h> /* General data structures. */
#include <iphlpapi.h> /* GetIpNetTable */
#include <stdlib.h> /* free, malloc, sizeof */

void run_getipnettable_test()
{
    PMIB_IPNETTABLE pIpNetTable = NULL;
    DWORD dwSize = 0;
    pause();
    DWORD dwRetVal = GetIpNetTable(pIpNetTable, &dwSize, TRUE);
    if (dwRetVal == ERROR_INSUFFICIENT_BUFFER) {
        pIpNetTable = (PMIB_IPNETTABLE)malloc(dwSize);
        if (pIpNetTable == NULL) {
            log_error("malloc");
            return;
        }
        dwRetVal = GetIpNetTable(pIpNetTable, &dwSize, TRUE);
        if (dwRetVal == NO_ERROR) {
            logf(
                "(GetIpNetTable) %d entries found.",
                pIpNetTable->dwNumEntries
            );
        } else {
            log_error("GetIpNetTable");
        }
        free(pIpNetTable);
    } else {
        log_error("GetIpNetTable");
    }
}

void run_rtlgetversion_test()
{
    typedef NTSTATUS(NTAPI *RtlGetVersionPtr)(LPOSVERSIONINFOEX);
    OSVERSIONINFOEX result = {
        sizeof(OSVERSIONINFOEX), 0, 0, 0, 0, {'\0'}, 0, 0, 0, 0, 0
    };
    HMODULE ntdll = GetModuleHandle("ntdll.dll");
    if (ntdll == NULL) {
        log_error("GetModuleHandle");
        return;
    }
    RtlGetVersionPtr pRtlGetVersion = (RtlGetVersionPtr)GetProcAddress(
        ntdll, "RtlGetVersion"
    );
    if (pRtlGetVersion == NULL) {
        log_error("GetProcAddress");
        return;
    }
    pause();
    if (pRtlGetVersion(&result) != 0) {
        log_error("RtlGetVersion");
    } else {
        logf(
            "(RtlGetVersion) Version: %d.%d.%d.%d",
            result.dwMajorVersion,
            result.dwMinorVersion,
            result.dwBuildNumber,
            result.dwPlatformId
        );
    }
}