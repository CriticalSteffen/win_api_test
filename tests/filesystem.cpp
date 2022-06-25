/* FindFirstFile() and FindNextFile() test implementations. */

#include "tests.h"

#include "../common/util.h" /* logf, log_error, pause */

#include <windows.h> /* FindFirstFile(W), FindNextFile(W), FindClose */

void run_findfile_test()
{
    WIN32_FIND_DATA fd = {0};
    pause();
    HANDLE hFind = FindFirstFile("C:\\Windows\\System32\\*.exe", &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        log_error("FindFirstFile");
        return;
    }
    logf("(FindFirstFile) Found file: %s", fd.cFileName);
    pause();
    if (!FindNextFile(hFind, &fd)) {
        log_error("FindNextFile");
        return;
    }
    logf("(FindNextFile) Found file: %s", fd.cFileName);
    if (!FindClose(hFind)) {
        log_error("FindClose");
        return;
    }
}

void run_findfilew_test()
{
    WIN32_FIND_DATAW fd = {0};
    char FileName[256] = {0};
    pause();
    HANDLE hFind = FindFirstFileW(L"C:\\Windows\\System32\\*.exe", &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        log_error("FindFirstFileW");
        return;
    }
    logf("(FindFirstFileW) Found file: %S", fd.cFileName);
    pause();
    if (!FindNextFileW(hFind, &fd)) {
        log_error("FindNextFileW");
        return;
    }
    logf("(FindNextFileW) Found file: %S", fd.cFileName);
    if (!FindClose(hFind)) {
        log_error("FindClose");
        return;
    }
}