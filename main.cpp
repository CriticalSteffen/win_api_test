/* SysMon API Test Driver
 * ======================
 * Execute a series of commonly-abused Windows API calls for observation with
 * SysMon.
 * 
 * The resulting binary must be run with administrator privileges.
 */

#include "common/util.h" /* close_log, log_split, pause */
#include "tests/tests.h"
/* run_createtoolhelp32snapshot_test
 * run_getipnettable_test
 * run_getnativesysteminfo_test
 * run_getusername_test
 * run_rtlgetntproducttype_test
 * run_rtlgetversion_test
 * run_findfile_test
 * run_findfilew_test
 * run_getasynckeystate_test
 * run_getkeyboardstate_test
 * run_getkeystate_test
 * run_adjusttokenprivileges_test
 * run_createprocesswithtokenw_test
 */

#include <stdlib.h> /* atexit, exit */

void clean_exit();

int main(int argc, char *argv[])
{
    atexit(clean_exit);

    log_split("API TEST START");

    log_split("tests/enum.cpp");
    run_createtoolhelp32snapshot_test();
    run_getipnettable_test();
    run_getnativesysteminfo_test();
    run_getusername_test();
    run_rtlgetntproducttype_test();
    run_rtlgetversion_test();

    log_split("tests/filesystem.cpp");
    run_findfile_test();
    run_findfilew_test();

    log_split("tests/keylog.cpp");
    run_getasynckeystate_test();
    run_getkeyboardstate_test();
    run_getkeystate_test();

    log_split("tests/processes.cpp");
    run_adjusttokenprivileges_test();
    run_createprocesswithtokenw_test();

    log_split("API TEST COMPLETE");
    pause();
    return 0;
}

void clean_exit()
{
    close_log();
    exit(0);
}

