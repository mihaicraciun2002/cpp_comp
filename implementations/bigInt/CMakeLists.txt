cmake_minimum_required(VERSION 3.0.0)
project(bigInt VERSION 0.0.1)

add_executable(bigInt bigInt.cpp bigIntMul.cpp bigIntMulFFT.cpp bigInt.h test.cpp)
