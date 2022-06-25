/* Test FindFirstFile and FindNextFile. */

#include "tests.h"

#include "../lib/libs.h" /* log, log_error */

#include <windows.h> /* FindFirstFile(W), FindNextFile(W), FindClose, Sleep */
#include <stdlib.h> /* wcstombs */
#include <stdio.h> /* sprintf */

void run_findfile_test();
void run_findfilew_test();

void run_findfile_test()
{
    WIN32_FIND_DATA fd = {0};
    Sleep(2000);
    log("(FindFirstFile) Finding first file...");
    HANDLE hFind = FindFirstFile("C:\\Windows\\System32\\*.exe", &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        log_error("FindFirstFile");
        return;
    }
    logf("(FindFirstFile) Found file: %s", fd.cFileName);
    Sleep(2000);
    log("(FindNextFile) Finding next file...");
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
    Sleep(2000);
    log("(FindFirstFileW) Finding first file...");
    HANDLE hFind = FindFirstFileW(L"C:\\Windows\\System32\\*.exe", &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        log_error("FindFirstFileW");
        return;
    }
    wcstombs(FileName, fd.cFileName, 256);
    logf("(FindFirstFileW) Found file: %s", FileName);
    Sleep(2000);
    log("(FindNextFileW) Finding next file...");
    if (!FindNextFileW(hFind, &fd)) {
        log_error("FindNextFileW");
        return;
    }
    wcstombs(FileName, fd.cFileName, 256);
    logf("(FindNextFileW) Found file: %s", FileName);
    if (!FindClose(hFind)) {
        log_error("FindClose");
        return;
    }
}