@echo off

mkdir build
cl.exe /Od /GS- /nologo /EHsc /Zi /Fe: .\build\apitest.exe ^
    main.cpp ^
    tests\cpwtw.cpp ^
    lib\log.cpp ^
    /link Advapi32.lib
del *.obj
del vc140.pdb
del build\apitest.ilk