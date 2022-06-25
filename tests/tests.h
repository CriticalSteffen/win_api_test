/* Test header. */

#ifndef TESTS_H
#define TESTS_H

// cpwtw.cpp
void run_cpwtw_test();

// enum.cpp
void run_getipnettable_test();
void run_getnativesysteminfo_test();
void run_rtlgetversion_test();

// findfile.cpp
void run_findfile_test();
void run_findfilew_test();

// keylog.cpp
void run_getasynckeystate_test();
void run_getkeyboardstate_test();
void run_getkeystate_test();

// proclist.cpp
void run_createtoolhelp32snapshot_test();

// tokenprivs.cpp
void run_adjusttokenprivileges_test();

#endif /* TESTS_H */