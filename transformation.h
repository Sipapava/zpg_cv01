#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <stdexcept>


//matice transformaci
class Transformation {
protected:
    int id;
    static int counter_id;
public:
    Transformation() : id(counter_id++) {}
    virtual ~Transformation() = default;
    virtual void Add(Transformation* t) {
        throw std::runtime_error("Cannot add to a leaf Transformation");
    };
    virtual glm::mat4 apply(const glm::mat4& matrix) = 0;

    int getId() const { return id; }
};

