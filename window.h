#pragma once

#include <cstdlib>
#include <queue>

template<class T>
class Window {
public:
    Window(std::size_t size) : size (size), sumX (0) {
        for (std::size_t i = 0; i < size; i++)
            queue.push(0);
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
