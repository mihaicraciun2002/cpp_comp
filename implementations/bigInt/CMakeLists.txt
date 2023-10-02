cmake_minimum_required(VERSION 3.0.0)
project(bigInt VERSION 0.0.1)

add_executable(bigInt bigInt.h bigInt.cpp myComplex.h bigIntMul.cpp bigIntMulFFT.cpp test.cpp)
