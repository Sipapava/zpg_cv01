#include "elementarTransformation.h"


Translation::Translation(const glm::vec3 offset) : Transformation(), offset(offset) {}

glm::mat4 Translation::apply(const glm::mat4& matrix) {  
    return glm::translate(matrix, offset);
}

Rotation::Rotation(float angle, const glm::vec3& axis) : Transformation(), angle(angle), axis(axis) {}

glm::mat4 Rotation::apply(const glm::mat4& matrix)  {
    return glm::rotate(matrix, angle, axis);
}

Scale::Scale(const glm::vec3& factors) : Transformation(), factors(factors) {}

glm::mat4 Scale::apply(const glm::mat4& matrix) {
    return glm::scale(matrix, factors);
}

glm::mat4 RotationDynamic::apply(const glm::mat4& matrix) {
    angle += addAngle; // 
    return glm::rotate(matrix, angle, axis);
}


RotationDynamic::RotationDynamic(float initialAngle, const glm::vec3& axis, float addAngle)
    : Rotation(initialAngle, axis), addAngle(addAngle) {}




glm::vec3 RandomTranslation::randomDirection() {
   
    float x = (rand() % 200 - 100) / 100.0f;
    float y = (rand() % 200 - 100) / 100.0f;
    float z = (rand() % 200 - 100) / 100.0f;
    glm::vec3 v(x, y, z);
    if (v == glm::vec3(0)) v = glm::vec3(1, 0, 0); 
    return glm::normalize(v);
}


RandomTranslation::RandomTranslation(float speed, int maxSteps)
    : speed(speed), maxSteps(maxSteps), stepsRemaining(0), added(0.0f, 0.0f, 0.0f) {
   
    direction = randomDirection();
    stepsRemaining = maxSteps;
   
}

glm::mat4 RandomTranslation::apply(const glm::mat4& matrix) {
    if (stepsRemaining <= 0) {
        direction = randomDirection();
        stepsRemaining = maxSteps;
        
        
    }
    added += direction * speed;
    glm::mat4 result = glm::translate(matrix, added);
    stepsRemaining--;
    return result;
}




CostumTransformation::CostumTransformation(const glm::mat4x4& matrix) : Transformation(), matrix(matrix) {}

glm::mat4 CostumTransformation::apply(const glm::mat4& matrix) {
    return matrix * this->matrix;
};


glm::vec3 RandomLine::randomPoint() {
    float x = -5.0f + (rand() / (float)RAND_MAX) * 10.0f;
    float y = 0.1f;
    float z = -5.0f + (rand() / (float)RAND_MAX) * 10.0f;
    return glm::vec3(x, y, z);
}

glm::vec3 RandomLine::randomDir() {
    float x = -1.0f + (rand() / (float)RAND_MAX) * 2.0f;
    float y = 0.0f;
    float z = -1.0f + (rand() / (float)RAND_MAX) * 2.0f;
    glm::vec3 d(x, y, z);
    return glm::normalize(d);
}

RandomLine::RandomLine(float speed)
    : speed(speed), t(0.0f)
{
    A = randomPoint();
    u = randomDir();
}

glm::mat4 RandomLine::apply(const glm::mat4& matrix) {
    if (t >= 1.0f) {
        A = A + u;        
        u = randomDir(); 
        t = 0.0f;
    }

    glm::vec3 pos = A + u * t;
    t += speed;

    return glm::translate(matrix, pos);
}




Bezier::Bezier(const glm::vec3 controlPoints[4], float speed)
    : speed(speed), t(0.0f)
{
    A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0.0),
        glm::vec4(-3.0, 3.0, 0.0, 0.0),
        glm::vec4(1.0, 0.0, 0.0, 0.0));

    B = glm::mat4x3(controlPoints[0],
        controlPoints[1],
        controlPoints[2],
        controlPoints[3]);
    finished = false;
   
}


glm::mat4 Bezier::apply(const glm::mat4& matrix)
{
    finished = false;
    if (t >= 1.0f) {
        t = 0.0f;
        finished = true;
    
    };

    glm::vec4 P = glm::vec4(t * t * t, t * t, t, 1.0f);
    glm::vec3 pos = glm::vec3(P * A * glm::transpose(B));

    glm::vec3 P0 = B[0];
    glm::vec3 P1 = B[1];
    glm::vec3 P2 = B[2];
    glm::vec3 P3 = B[3];

    float u = 1.0f - t;


    glm::vec3 dPos = 3.0f * u * u * (P1 - P0) + 6.0f * u * t * (P2 - P1) + 3.0f * t * t * (P3 - P2);
    dPos = glm::normalize(dPos);

  
    float alpha = glm::degrees(asin(dPos.y));
    float phi = glm::degrees(atan2(dPos.z, dPos.x));

  

    t += speed;

    glm::mat4 result = matrix;
    result = glm::translate(result, pos);
    result = glm::rotate(result, glm::radians(alpha), glm::vec3(1, 0, 0)); // pitch
    result = glm::rotate(result, glm::radians(phi), glm::vec3(0, 1, 0)); // yaw
    
   printf("t = %.3f, dPos = (%.3f, %.3f, %.3f), alpha = %.3f, phi = %.3f\n",
       t, dPos.x, dPos.y, dPos.z, alpha, phi);



    return result;
}



BezierCustom::BezierCustom(const std::vector<glm::vec3>& points, float speed) {
    this->points = points;

    std::vector<glm::vec3> pts = this->points;

    // force of the same derivation, for continues movement
    for (size_t i = 3; i + 1 < pts.size(); i += 3) {

        glm::vec3 P3_prev = pts[i];     
        glm::vec3 P2_prev = pts[i - 1]; 

        glm::vec3 differenc = P3_prev - P2_prev;

        //P4, segment n+1 P3 a P4
        pts[i + 1] = P3_prev + differenc;
    }
    

    size_t i = 0;
    for (; i + 3 < pts.size(); i += 3) {

        glm::vec3 cp[4] = {
            pts[i],
            pts[i + 1],
            pts[i + 2],
            pts[i + 3]
        };

        

        segments.emplace_back(cp, speed);
    }

    
    if (i < pts.size()) {

        glm::vec3 cp[4];
        int idx = 0;

        for (; i < pts.size() && idx < 4; i++, idx++) {
            cp[idx] = pts[i];
        }

        glm::vec3 last = cp[idx - 1];
        while (idx < 4) {
           
            glm::vec3 tangent = last - pts[pts.size() - 2];
            cp[idx] = last + tangent;
            idx++;
        }

        segments.emplace_back(cp, speed);
    }
}


glm::mat4 BezierCustom::apply(const glm::mat4& matrix) {
        if (segments.empty()) return matrix;

        glm::mat4 m = segments[currentSegment].apply(matrix);

        if (segmentFinished(segments[currentSegment])) {
            segments[currentSegment].resetFinished();
            if (currentSegment + 1 < (int)segments.size()) {
                currentSegment++;
            }
            else {
                currentSegment = 0;
            }
        }

        return m;
    }


bool BezierCustom::segmentFinished(const Bezier& b) {
        return b.getT() >= 1.0f;
    }


