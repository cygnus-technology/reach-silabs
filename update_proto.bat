echo off
rem: The intent of this batch is to regenerate the reach_proto/ansic/build directory
rem:  when modifying the proto file(s).  This isn't usually required, and 
rem:  it may take some setup to get protbufs to build from a windows batch.
rem:
rem: The build relies on cmake and protoc.
rem: cmake v3.21.1 and protoc v24.2 work.  Older versions might not work.
rem: To setup the cmake build I run cmake ../ ./ from the build directory from cygwin where the path is shortened to:
rem: export PATH='/usr/local/bin:/usr/bin:/cygdrive/c/Program Files/Git/cmd:/cygdrive/c/Program Files/CMake/bin:/cygdrive/c/Users/chuck.peplinski/AppData/Local/Programs/Python/Python310/Scripts:/cygdrive/c/Users/chuck.peplinski/AppData/Local/Programs/Python/Python310:/cygdrive/c/Users/chuck.peplinski/install2/protoc-24.2-win64/bin:/cygdrive/c/Windows/system32'
rem: In my case it is chocolaty that is messing things up.

set curdir=%cd%
set src=%cd%\reach-protobuf

cd %src%
cd proto 
echo Run 'python preprocess_options.py' to generate options file.
python preprocess_options.py

cd %src%\ansic\build

rem: With cygwin
echo Use cygin make to rebuild .pb files
make
rem:  echo With Microsoft
rem:  cmake --build .

python %src%\proto\postprocess_comments.py

echo Copy generated reach.pb.h
cp reach.pb.c %curdir%\reach-c-stack\src
cp reach.pb.h %curdir%\reach-c-stack\include
echo Copy nanopb files
xcopy /Y ..\nanopb\*.c %curdir%\reach-c-stack\third_party\nanopb
xcopy /Y ..\nanopb\*.h %curdir%\reach-c-stack\third_party\nanopb
xcopy /Y ..\nanopb\*.txt %curdir%\reach-c-stack\third_party\nanopb
xcopy /Y ..\nanopb\*.md %curdir%\reach-c-stack\third_party\nanopb

cd %curdir%
echo Done.
