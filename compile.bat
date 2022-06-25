@echo off

mkdir build
cl.exe /Od /GS- /nologo /EHsc /Zi /Fe: .\build\apitest.exe ^
    main.cpp ^
        tests\cpwtw.cpp ^
        tests\findfile.cpp ^
        tests\keylog.cpp ^
        tests\proclist.cpp ^
        tests\tokenprivs.cpp ^
        lib\log.cpp ^
        lib\timing.cpp ^
    /link ^
        Advapi32.lib ^
        User32.lib
del *.obj
del vc140.pdb
del build\apitest.ilk