# SQLite Setup Guide for A3
## For WSL2 Environment

Clone the SQLite repository:
```bash
git clone https://github.com/sqlite/sqlite.git
```

Navigate to the SQLite directory:
```bash
cd sqlite
```

Configure the build for the system:
```bash
./configure
```

Compile SQLite3:
```bash
make
```

### Note: make might not exist on the system
Install tclsh 8.4
```bash
sudo apt install tcl
```

Run
```bash
tclsh
```

Test
```bash
puts "Hello, World!"
```

Then
```bash
exit
```

(Optional) Install SQLite3 system-wide:
```bash
sudo make install
```

To use SQLite3 in this C++ program, link against the SQLite3 library. From /mnt/c/Users/samue/git/A3/src directory, compile the C++ program with SQLite3 like this:
```bash
g++ -o test test.cpp -lsqlite3
```




