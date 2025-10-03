#include "complexTransformation.h"


glm::mat4 complexTransformation::apply(const glm::mat4& matrix) const {
    glm::mat4 result = matrix;
    for (auto it = transformations.rbegin(); it != transformations.rend(); ++it) {
        result = (*it)->apply(result);
    }
    return result;
}


void complexTransformation::Add(Transformation* t) {
    transformations.push_back(t);
}

complexTransformation::~complexTransformation() {
    for (Transformation* t : transformations) {
        delete t; 
    }
    transformations.clear();
}


/*
void complexTransformation::removeById(int removeId) {
    auto it = std::remove_if(transformations.begin(), transformations.end(),
        [removeId](Transformation* t) { return t->getId() == removeId; });
    transformations.erase(it, transformations.end());
}

*/
