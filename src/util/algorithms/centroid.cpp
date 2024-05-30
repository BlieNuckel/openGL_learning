#include "algorithms.h"
#include <glm/glm.hpp>
#include <numeric>
#include <vector>

float average(std::vector<float> const &v) {
    if (v.empty()) {
        return 0;
    }

    float const count = static_cast<float>(v.size());
    return std::reduce(v.begin(), v.end()) / count;
};

glm::vec3 algorithms::centroid(std::vector<glm::vec3> vertices) {
    std::vector<float> x_values, y_values, z_values;

    for (auto &vertex : vertices) {
        x_values.push_back(vertex.x);
        y_values.push_back(vertex.y);
        z_values.push_back(vertex.z);
    }

    float x_avg = average(x_values);
    float y_avg = average(y_values);
    float z_avg = average(z_values);

    return glm::vec3(x_avg, y_avg, z_avg);
};