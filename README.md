# CIPSP
A simple IPS patcher written in C++, it's been tested on Linux, it should work on other platforms.
## Compiling
There aren't any special dependencies, just make sure `g++` and `make` are installed in your system, open a terminal and type:
```console
make
```
This will create various `.o` files, and one named `cipsp`, this is the executable.
## Usage
Assuming you have the executable in the same directory as the ROM and IPS files:
```console
./cipsp rom ips output
```
For example:
```console
./cipsp legalRom.gba patch.ips patchedRom.gba
```
