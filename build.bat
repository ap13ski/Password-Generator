rem MinGW-W64 v.8.1.0
windres resources.rc -o resources.o
g++ -static main.cpp clipboard.cpp password.cpp resources.o -lgdi32 -luser32 -lkernel32 -lcomctl32 -lgcc -lstdc++ -mwindows

pause