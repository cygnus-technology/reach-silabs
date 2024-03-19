rem copy thisinto the build directory and run it there.

rem set PATH_GCCARM=C:\SiliconLabs\SimplicityStudio\v5\developer\toolchains\gnu_arm\10.3_2021.10
set SIZER=C:\SiliconLabs\SimplicityStudio\v5\developer\toolchains\gnu_arm\10.3_2021.10\bin\arm-none-eabi-size.exe 
set NM=C:\SiliconLabs\SimplicityStudio\v5\developer\toolchains\gnu_arm\10.3_2021.10\bin\arm-none-eabi-nm.exe 

Rem %SIZER% reach-silabs.out > reach-silabs-size.txt
%NM% -S reach-silabs.out > reach-silabs-nm.txt



