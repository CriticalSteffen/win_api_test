/* GetIpNetTable() test implementation. */

#include "tests.h"

#include "../lib/libs.h" /* logf, log_error, pause */

#include <windows.h> /* General data structures. */
#include <iphlpapi.h> /* GetIpNetTable */
#include <stdlib.h> /* free, malloc */

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