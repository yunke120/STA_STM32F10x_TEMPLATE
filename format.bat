@echo off
setlocal EnableDelayedExpansion


@echo off
setlocal EnableDelayedExpansion

REM 承定要查找的文件夹
set "dir1=USER"
set "dir2=HARDWARE"

REM 承定文件后缀名
set "ext1=.c"
set "ext2=.h"

for /R "%dir1%" %%i in ("*%ext1%", "*%ext2%") do (
    echo Formatting file: "%%i"
    clang-format.exe -i "%%i"
)

for /R "%dir2%" %%i in ("*%ext1%", "*%ext2%") do (
    echo Formatting file: "%%i"
    clang-format.exe -i "%%i"
)

REM pause