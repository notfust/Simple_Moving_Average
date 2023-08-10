#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include "window.h"

static constexpr std::size_t ARR_SIZE = 1'000'000;

using namespace std::chrono;
using std::vector;

int main() {
    std::random_device rd;
    std::uniform_real_distribution<float> dist(-10, 10);
    steady_clock::time_point start;
    steady_clock::time_point end;

    std::ofstream tableTimes("timetests.csv", std::ofstream::out | std::ofstream::trunc);
    std::ofstream tableValues("value.csv", std::ofstream::out | std::ofstream::trunc);

    tableTimes << "type_and_window" << ',' << "count_sec" << std:: endl;
    tableValues << "type_and_window" << ',';
    for (std::size_t i = 0; i < 1000; i++) 
        tableValues << i + 1 << ',';
    tableValues << std::endl;

    vector<float> floatInputVector(ARR_SIZE);

    tableValues << "float_init" << ',';
    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        floatInputVector[i] = dist(rd);
        if (i < 1000) 
            tableValues << floatInputVector[i] << ',';
    }
    tableValues << std::endl;

    for (std::size_t i = 4; i <= 128; i *= 2) {
        Window<float> window(i);
        vector<float> floatOutputVector(ARR_SIZE);

        start = steady_clock::now();
        for (std::size_t j = 0; j < ARR_SIZE; j++) 
            floatOutputVector[j] = window.next(floatInputVector[j]);
        end = steady_clock::now();

        tableTimes << "float_" << i << ','
                   << ARR_SIZE / duration<double>(end - start).count()
                   << std::endl;

        tableValues << "float_" << i << ',';
        for (std::size_t j = 0; j < 1000; j++) 
            tableValues << floatOutputVector[j] << ',';
        tableValues << std::endl;
    }

    vector<double> doubleInputVector(ARR_SIZE);

    tableValues << "double_init" << ',';
    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        doubleInputVector[i] = dist(rd);
        if (i < 1000) 
            tableValues << doubleInputVector[i] << ',';
    }

    tableValues << std::endl;
    for (std::size_t i = 4; i <= 128; i *= 2) {
        Window<double> window(i);
        vector<double> doubleOutputVector(ARR_SIZE);

        start = steady_clock::now();
        for (std::size_t j = 0; j < ARR_SIZE; j++) 
            doubleOutputVector[j] = window.next(floatInputVector[j]);
        end = steady_clock::now();

        tableTimes << "double_" << i << ','
                   << ARR_SIZE / duration<double>(end - start).count()
                   << std::endl;

        tableValues << "double_" << i << ',';
        for (std::size_t j = 0; j < 1000; j++) 
            tableValues << doubleOutputVector[j] << ',';
        tableValues << std::endl;
    }

    return 0;
}
