# Minesweeper
Simple console version of the classic game Minesweeper.

Includes both Windows and Linux versions.
Linux version requires GNU GCC's g++ compiler (preinstalled in most distributions).
Windows version requires MinGW compiler (for providing g++ and getch functionality)

To build the binary from the source,
* Linux

run `g++ -Wall minesweeper.cpp -o output_file`
* Windows

run `g++ -Wall -static-libgcc -static-libstdc++ minesweeper.cpp -o output_file.exe`

To play the game,
run `./output_file(.exe)`
