#include <algorithms/algorithms.h>

bool algorithms::definitely_greater_than(float a, float b, float epsilon) {
    return std::abs(b - a) > ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * epsilon);
}