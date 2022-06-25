/* CreateToolHelp32Snapshot(), GetIpNetTable(), GetNativeSystemInfo() and
 * RtlGetVersion() test implementations.
 *
 * Note: RtlGetVersion() comes from `ntdll.dll` via GetModuleHandle() and
 * GetProcAddress().
 */

#include "tests.h"

#include "../common/util.h" /* log, logf, log_error, pause */

#include <windows.h>
/* CloseHandle
 * GetModuleHandle
 * GetNativeSystemInfo
 * GetProcAddress
 */
#include <iphlpapi.h> /* GetIpNetTable */
#include <stdlib.h> /* free, malloc, sizeof */
#include <tlhelp32.h> /* CreateToolHelp32Snapshot */


typedef enum _NT_PRODUCT_TYPE {
    NtProductWinNt = 1,
    NtProductLanManNt,
    NtProductServer
} NT_PRODUCT_TYPE, *PNT_PRODUCT_TYPE;



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

void run_getnativesysteminfo_test()
{
    SYSTEM_INFO si;
    pause();
    GetNativeSystemInfo(&si);
    logf(
        "(GetNativeSystemInfo) Processor: %s",
        si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL ?
            "x86 (Intel)" : "x64 (AMD/Intel)"
    );
}

void run_rtlgetntproducttype_test()
{
    typedef NTSTATUS(NTAPI *RtlGetNtProductTypePtr)(LPDWORD);
    HMODULE ntdll = GetModuleHandle("ntdll.dll");
    if (ntdll == NULL) {
        log_error("GetModuleHandle");
        return;
    }
    RtlGetNtProductTypePtr pRtlGetNtProductType = (
        RtlGetNtProductTypePtr
    )GetProcAddress(
        ntdll, "RtlGetNtProductType"
    );
    if (pRtlGetNtProductType == NULL) {
        log_error("GetProcAddress");
        return;
    }
    DWORD dwProductType = 0;
    pause();
    pRtlGetNtProductType(&dwProductType);
    logf(
        "(RtlGetNtProductType) Product type: %s",
        dwProductType == NtProductWinNt ? "Windows NT" :
        dwProductType == NtProductLanManNt ? "Windows Server" :
        dwProductType == NtProductServer ? "Windows Server" :
        "Unknown"
    );
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