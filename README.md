# Go Compiler

A miniature Go compiler written using lex and yacc. Project component for the
UE18CS351 Compiler Design course.


## Status

The following stages have been implemented so far:
-   Lexical Analysis
-   Syntax Analysis
-   Symbol Table Generation

The following constructs are supported by the Go compiler so far:
-   int, float32, string and bool data types
-   functions
-   if-else statements
-   for loops
-   most arithmetic and logical operations
-   block statements with scopes


## Building and Execution

### On host machines:

Dependencies:
-   flex (an implementation of lex)
-   bison (an implementation of yacc)

These can be installed via distribution specific package managers.

Once dependencies are met, the compiler can be built using make:
```
make
```

Then the compiler accepts a Go program through stdin:
```
./a.out < test.go
```

### Using docker

A docker container can be used to isolate the running environment.

While in the repository folder, the docker image for the compiler can be
built using:
```
docker build -t go-compiler .
```

Then the docker image can be run as a container, with the repository mounted
on it.
```
docker run --rm -it -v $GO_COMPILER_PATH:/go go-compiler bash
```

where $GO_COMPILER_PATH should be replaced with the full path to the
repository folder.

Running the command gives an interactive terminal, in which the previous
build and execution instructions using make can be run.
