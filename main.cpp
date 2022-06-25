/* SysMon API Test Driver
 * ======================
 * Execute a series of Windows API calls for observation with SysMon.
 * 
 * The resulting binary must be run with administrator privileges.
 */

#include "lib/libs.h" /* log_split, close_log */
#include "tests/tests.h"
/* run_cpwtw_test
 * run_findfile_test
 * run_findfilew_test
 */

#include <windows.h> /* Sleep */
#include <stdlib.h> /* atexit, exit */

void clean_exit();

int main(int argc, char *argv[])
{
    atexit(clean_exit);

    log_split("API TEST START");

    run_cpwtw_test();
    run_findfile_test();
    run_findfilew_test();

    log_split("API TEST COMPLETE");
    Sleep(5000);
    return 0;
}

void clean_exit()
{
    close_log();
    exit(0);
}

