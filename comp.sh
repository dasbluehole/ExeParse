#! /bin/bash
#gcc=~/djgpp/bin/i586-pc-msdosdjgpp-gcc
gcc=/usr/bin/gcc
$gcc -g -c exedump.c -o exedump.o
$gcc -g -c ne_exe.c  -o ne_exe.o
$gcc -g -c dos_exe.c -o dos_exe.o
$gcc -g -c lx_exe.c  -o lx_exe.o
$gcc -g -c pe_exe.c  -o pe_exe.o
$gcc -g -c coff.c    -o coff.o
$gcc dos_exe.o ne_exe.o lx_exe.o pe_exe.o coff.o exedump.o -o exedump.exe
#gcc dos_exe.o lx_exe.o exedump.o -o exedump.exe
rm -rf *.o

