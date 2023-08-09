#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <queue>

#define ARR_SIZE 1'000'000

using namespace std::chrono;
using std::vector;

template<class T>
class Window {
public:
    Window(std::size_t size) : size (size), sumX (0) {
        for (std::size_t i = 0; i < size; i++) queue.push(0);
    }

    T next(T value) {
        sumX -= queue.front();
        queue.pop();

        sumX += value;
        queue.push(value);

        return sumX / size;
    }

private:
    std::size_t size;
    std::queue<T> queue;
    T sumX;
};

int main() {
    std::random_device rd;
    std::uniform_real_distribution<float> dist(-10, 10);
    steady_clock::time_point start;
    steady_clock::time_point end;

    std::ofstream tableTimes("timetests.csv", std::ofstream::out | std::ofstream::trunc);
    std::ofstream tableValues("value.csv", std::ofstream::out | std::ofstream::trunc);

    tableTimes << "Type w/ window" << ',' << "count/sec" << std:: endl;
    tableValues << "Type w/ window" << ',';
    for (std::size_t i = 0; i < 1000; i++) tableValues << i + 1 << ',';
    tableValues << std::endl;

    vector<float> floatInputVector(ARR_SIZE);

    tableValues << "Float (init)" << ',';
    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        floatInputVector[i] = dist(rd);
        if (i < 1000) tableValues << floatInputVector[i] << ',';
    }
    tableValues << std::endl;

    for (std::size_t i = 4; i <= 128; i *= 2) {
        Window<float> window(i);
        vector<float> floatOutputVector(ARR_SIZE);

        start = steady_clock::now();
        for (std::size_t j = 0; j < ARR_SIZE; j++) floatOutputVector[j] = window.next(floatInputVector[j]);
        end = steady_clock::now();

        tableTimes << "Float (" << i << ")" << ','
                   << ARR_SIZE / duration<double>(end - start).count()
                   << std::endl;

        tableValues << "Float (" << i << ")" << ',';
        for (std::size_t j = 0; j < 1000; j++) tableValues << floatOutputVector[j] << ',';
        tableValues << std::endl;
    }

    vector<double> doubleInputVector(ARR_SIZE);

    tableValues << "Double (init)" << ',';
    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        doubleInputVector[i] = dist(rd);
        if (i < 1000) tableValues << doubleInputVector[i] << ',';
    }

    tableValues << std::endl;
    for (std::size_t i = 4; i <= 128; i *= 2) {
        Window<double> window(i);
        vector<double> doubleOutputVector(ARR_SIZE);

        start = steady_clock::now();
        for (std::size_t j = 0; j < ARR_SIZE; j++) doubleOutputVector[j] = window.next(floatInputVector[j]);
        end = steady_clock::now();

        tableTimes << "Double (" << i << ")" << ','
                   << ARR_SIZE / duration<double>(end - start).count()
                   << std::endl;

        tableValues << "Double (" << i << ")" << ',';
        for (std::size_t j = 0; j < 1000; j++) tableValues << doubleOutputVector[j] << ',';
        tableValues << std::endl;
    }

    return 0;
}
