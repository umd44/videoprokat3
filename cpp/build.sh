#!/bin/bash

# Build script for C++ video rental system
# Compiles all source files and creates executable

echo "Building Videoprokat C++ application..."

# Compile command for g++
g++ -std=c++17 -o videoprokat \
    videoprokat.cpp \
    User.cpp \
    UserReal.cpp \
    Client.cpp \
    ClientReal.cpp \
    VideoCarrier.cpp \
    VideoCarrierReal.cpp \
    Catalog.cpp \
    CatalogReal.cpp \
    Rental.cpp \
    RentalReal.cpp \
    RentalManager.cpp \
    RentalManagerReal.cpp \
    FinancialCalculator.cpp \
    FinancialCalculatorReal.cpp \
    ReportGenerator.cpp \
    ReportGeneratorReal.cpp \
    -lstdc++fs

if [ $? -eq 0 ]; then
    echo "Build successful! Executable: ./videoprokat"
    echo "Run with: ./videoprokat"
else
    echo "Build failed!"
    exit 1
fi
