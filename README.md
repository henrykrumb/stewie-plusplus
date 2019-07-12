# stewie++

## License
This project is licensed under the GPLv3 license.

## Installation ##
### Prerequisites ###

### Linux ###
```bash
mkdir build
cd build
cmake ..
./examples forms
```

### Windows ###


## Philosophy ##

### Simplicity ###
Allow short cuts for common use cases but keep not-so-common use cases
feasible.

### Portability ###
stewie++ should be portable in a way that it could run on a Windows terminal
using pcurses; that is a major restriction. Unicode characters should be
prevented, also only 8 colors can be displayed.

### Code ###

1. Prevent control statements (if, while,...) without brackets.

```C++
// good
if (/* ... */) {
	one_line_statement();
}

// bad
if (/* ... */)
	one_line_statement();
```

2. Use smart pointers wherever possible. C style pointers should only be
used in scenarios where smart pointers cannot be used without major effort,
e.g. when you need to store the "this" pointer of some class.
If you should happen to use C style pointers, make sure you have full control
of when it is created, shared and finally destroyed.
