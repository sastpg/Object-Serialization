# Object Serialization

Object Oriented Programming Project in ZJU.

## Compile and Run

Using commands in terminal to construct:

```bash
mkdir build
cd build
cmake ..
make
cd ..
```

To make things easy, I provided a shell **test.sh**. We can simply use the command `./test.sh` to construct.

After that, using commands in terminal to run:

```bash
mkdir test
rm -f test/*
cd bin
./test.out
```



## Test

All test results will be generated in directory `./bin/test_all.txt`. Some Intermediate results will be generated in directory `./test/*`.

> Note: Intermediate results of XML serialization are deleted in the process of XML deserialization. If you want to see the intermediate results, you can comment the part of XML deserialization.

Using commands `./bin/test.out` to check whether all object can be serialization / deserialization correctly.

<table><tr><td><img src=https://s2.loli.net/2022/06/08/XkVgqDzZjsfC2TO.png border=0></td><td><img src=https://s2.loli.net/2022/06/08/ziIFMBvY1RrsOWt.png border=0></td></tr></table>

## Functions

- [x] 🎉 Supported binary serialization/deserialization from a std type and user defined type
- [x] 🍀 Supported binary serialization/deserialization from smart pointers
- [x] 🏁 Supported XML serialization/deserialization from a std type and user defined type
- [x] 💃🏻 Supported XML serialization/deserialization from smart pointers

## Bugs

Due to some bugs in `tinyxml2`, so there might be some bugs in XML serialization.

## Address

Project address : [My Github](https://github.com/sastpg/Object-Serialization)

@copyright Copyright (c) 2022