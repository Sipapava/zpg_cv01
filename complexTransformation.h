#pragma once
#include "transformation.h"
#include <vector>

class complexTransformation : public Transformation {
private:
    std::vector<Transformation*> transformations;
public:
    ~complexTransformation();
    void Add(Transformation * t) override;
    //delete with id
    glm::mat4 apply(const glm::mat4& matrix) override;
};