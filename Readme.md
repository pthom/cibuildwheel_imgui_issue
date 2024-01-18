I observed that when building a wheel from C++ sources on ubuntu 22.04, `cibuildwheel` will use the "GNU/Linux" ABI,  when `pip install` will use SYSV (the older ABI).

`sizeof(std::string)` yields different results in those two context.

Is that something of importance?


### A wheel built with pip install:

- uses the SYSV ABI (older set of conventions for system calls, object files, and libraries)
- sizeof(string)=8
- is linked against libstdc++.so.6

```bash
> file _mylib.cpython-310-x86_64-linux-gnu.so
 ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked
```

### A wheel built with cibuildwheel
- uses the GNU/Linux ABI (newer conventions for system calls, with modifications made by the GNU project)
- sizeof(string)=32
- is linked against libstdc++.so.6

```bash
> file _mylib.cpython-310-x86_64-linux-gnu.so
 ELF 64-bit LSB shared object, x86-64, version 1 (GNU/Linux), dynamically linked
```

