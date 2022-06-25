/* Test header. */

#ifndef TESTS_H
#define TESTS_H

// enum.cpp
void run_createtoolhelp32snapshot_test();
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

// processes.cpp
void run_adjusttokenprivileges_test();
void run_createprocesswithtokenw_test();

#endif /* TESTS_H */