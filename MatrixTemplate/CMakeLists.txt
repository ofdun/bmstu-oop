cmake_minimum_required(VERSION 3.30)
project(MatrixTemplate)

include_directories(inc/iterators)
include_directories(src/iterators)
include_directories(inc/matrix)
include_directories(src/matrix)
include_directories(inc/exceptions)
include_directories(inc/concepts)
include_directories(src)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

set(app-name "MatrixTemplate")

add_executable(${app-name} src/cmd/main.cpp
        src/matrix/Matrix.hpp
        src/iterators/MatrixIterator.hpp
        src/iterators/MatrixConstIterator.hpp
        src/iterators/BaseMatrixIterator.cpp
        inc/exceptions/BaseException.h
        inc/exceptions/IteratorExceptions.h
        inc/exceptions/MatrixExceptions.h
        inc/concepts/MatrixConcepts.h
        inc/iterators/MatrixReverseIterator.h
        src/iterators/MatrixReverseIterator.hpp
        src/iterators/MatrixConstReverseIterator.hpp)

target_link_libraries(${app-name} PRIVATE GTest::gtest)
