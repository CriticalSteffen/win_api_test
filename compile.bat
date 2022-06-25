@echo off

mkdir build
cl.exe /Od /GS- /nologo /EHsc /Zi /Fe: .\build\apitest.exe ^
    main.cpp ^
        tests\enum.cpp ^
        tests\filesystem.cpp ^
        tests\keylog.cpp ^
        tests\processes.cpp ^
        common\util.cpp ^
    /link ^
        Advapi32.lib ^
        Iphlpapi.lib ^
        User32.lib
del *.obj
del vc140.pdb
del build\apitest.ilk