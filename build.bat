rem call vcvars64
pushd build
call clang -Wall -Wextra -lgdi32 -luser32 ..\main.c -o imgcat.exe
call imgcat.exe 1.png
popd