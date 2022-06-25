/* SysMon API Test Driver
 * ======================
 * Execute a series of Windows API calls for observation with SysMon.
 * 
 * The resulting binary must be run with administrator privileges.
 */

#include <stdlib.h>
#include <windows.h>

#include "tests/tests.h"
#include "lib/libs.h"

void clean_exit();

int main(int argc, char *argv[])
{
    atexit(clean_exit);

    log("SysMon API Test");

    run_cpwtw_test();
    run_findfile_test();
    run_findfilew_test();

    log("SysMon API Test Complete");
    Sleep(5000);
    return 0;
}

void clean_exit()
{
    close_log();
    exit(0);
}

