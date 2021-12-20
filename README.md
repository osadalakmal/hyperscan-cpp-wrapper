# hyperscan-cpp-wrapper

![Build Status](https://github.com/osadalakmal/hyperscan-cpp-wrapper/actions/workflows/cmake.yml/badge.svg)

A c++ wrapper for intel hyperscan regex library

## Goals

The main goals are to provide better resource management and familiar C++ interface to the functionality

## Building

Use cmake to build. After cloning change to the source directory and run

```
mkdir -p build && cd build && cmake ../ && make -j
```

## Running Test(s)

From repo root run

```
./build/hs-cpp.t.tsk
```
