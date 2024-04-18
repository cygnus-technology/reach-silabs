@echo off
rem PATH_SCMD=C:\SiliconLabs\SimplicityStudio\v5\developer\adapter_packs\commander
rem pwd

set BOOTLOADER=..\bootloader\bootloader-apploader.hex
set APP=reach-silabs.s37

echo Create combined hex file reach-silabs-combined.hex
@echo on
%PATH_SCMD%\commander.exe convert %BOOTLOADER% %APP% -o reach-silabs-combined_v.hex


set PATH_GCCARM=C:\SiliconLabs\SimplicityStudio\v5\developer\toolchains\gnu_arm\12.2.rel1_2023.7

echo call create_bl_files.bat to created .gbl files for FW update.
call ..\create_bl_files.bat
mv 

rem force rebuild of dated banner
rm src/cli.o

echo Created combined hex file and .gbl for OTA FW update.

