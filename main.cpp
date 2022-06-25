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
 * run_getasynckeystate_test
 * run_getkeyboardstate_test
 * run_getkeystate_test
 */

#include <windows.h> /* Sleep */
#include <stdlib.h> /* atexit, exit */

void clean_exit();

int main(int argc, char *argv[])
{
    atexit(clean_exit);

    log_split("API TEST START");

    // tests/cpwtw.cpp
    run_cpwtw_test();
    // tests/findfile.cpp
    run_findfile_test();
    run_findfilew_test();
    // tests/keylog.cpp
    run_getasynckeystate_test();
    run_getkeyboardstate_test();
    run_getkeystate_test();

    log_split("API TEST COMPLETE");
    Sleep(1000);
    return 0;
}

void clean_exit()
{
    close_log();
    exit(0);
}

