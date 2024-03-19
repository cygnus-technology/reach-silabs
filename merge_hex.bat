@echo off
rem PATH_SCMD=C:\SiliconLabs\SimplicityStudio\v5\developer\adapter_packs\commander
rem pwd

set BOOTLOADER=..\bootloader\bootloader-apploader.hex
set APP=reach-silabs.s37

echo "Create combined hex file reacher-tboard-v.hex"
@echo on
%PATH_SCMD%\commander.exe convert %BOOTLOADER% %APP% -o reacher-tboard-v.hex


set PATH_GCCARM=C:\SiliconLabs\SimplicityStudio\v5\developer\toolchains\gnu_arm\12.2.rel1_2023.7

echo "call create_bl_files.bat to created .gbl files for FW update."
call ..\create_bl_files.bat

rem force rebuild of dated banner
rm app\reach_app.o

echo "Created combined hex file and .gbl for OTA FW update."

