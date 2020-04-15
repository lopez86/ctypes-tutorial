# ctypes-tutorial
## Tutorial on Running C &amp; C++ Code in Python

### Intro

This project provides a tutorial on how to use the python `ctypes` package to use C-compatible binaries in your python code.

The simple example here is a system to run basic banking transactions like account creation, checking balances, withdrawing money, and depositing money.
The code is written in C++ with a provided C API that is then used in some Python code. It uses some complex (but still simple) types
to show how you can get your python code to talk to things like C++ objects.

### Why?

If you're like me and come from a background of doing scientific computing mostly in C++, you may have run into cases where you
have some C++ code that you'd like to run in a python program. Maybe it's some high-performance mathematical operations. 
Maybe it's a 3rd party C or C++ API to run a piece of equipment that you bought. There are a number of things you can do from here.

In some cases, you can just rewrite the code in python and run it. That's going to be the simplest way to do it but in cases like
I just mentioned above that may not be feasible. In that case, you can also rewrite it in Cython to still get the performance of C.
However, Cython is also a pain to deal with and is sort of like its own language, so there's a lot of mental overhead in terms of 
just having to learn Cython and also having to learn the more complicated build system.

The other thing that you can do is to use a python package to just call your code directly as if it were python. 
The ctypes package is an official python package that does exactly this. It's not the only package though. I haven't looked too
much into other packages but there are others with slightly different features that might be more appropriate depending on your use case.
For example, the particle physics analysis package ROOT comes with its own method of automatically generating python bindings for
much of your code.

### Requirements
 1) python3
 1) make
 1) gcc and g++

### Using the code
I have not set this up as a python package, so once you download, you need to make everything yourself with:
```bash
make
```

Currently, there are two examples, which do more or less the same thing. `make` will build an example in C, which you can run with:
```bash
LD_LIBRARY_PATH:$PWD/banking:$LD_LIBRARY_PATH ./bank_example.exe
```
and a python example, which you can run with
```bash
python bank_example.py
```

### Future improvements

A few future improvements I hope to make are:
 1) Add a simple flask server so that users can add arbitrary data
 1) Maybe make a Rust implementation too since that is going to be more complicated than C++
