#include "Scene.h"
#include <algorithm> 
#include "circleBuild.h"

int Scene::nextId = 0;
Scene::Scene() {
    id = nextId++;
}

Scene::~Scene() {
    
    for (auto obj : drawableObjects) {
        delete obj;
    }
    drawableObjects.clear();

    
    for (auto sp : shaderPrograms) {
        delete sp;
    }
    shaderPrograms.clear();
}

void Scene::addShaderProgram(ShaderProgram* sp) {
    shaderPrograms.push_back(sp);
}



DrawableObject* Scene::CreateDrawableObject(Model* m, ShaderProgram* sp) {
    return new DrawableObject(m, sp);
}

Model* Scene::CreateModel(const Vertex* vertices, size_t count,bool color,std::string type) {
    return new Model(vertices, count,color,type);
}

void Scene::addDrawableObject(DrawableObject* obj) {
    drawableObjects.push_back(obj);
}

void Scene::draw() {
    // iterace pres shadery?
    for (auto obj : drawableObjects) {
        obj->draw();
    }
}

bool Scene::prepareTestSceneCv02() {
    

    std::vector<Vertex> circle = buildCircle(0.5f, 60);

    const Vertex linie[] = {
        
        { { -0.9f, -0.5f, 0, 1 }, { 1, 0, 0, 1 } }, // - èervená
        { { -0.9f,  -0.3f, 0, 1 }, { 1, 1, 0, 1 } }, // - žlutá
        { {  -0.5f,  -0.3f, 0, 1 }, { 0, 0, 1, 1 } }, //  - modrá

    };

    const Vertex a[] = {
        
        { { -1.0f,  0.6f, 0, 1 } }, 
        { { -1.0f,  1.0f, 0, 1 } }, 
        { { -0.6f,  1.0f, 0, 1 } }, 
    };

    const Vertex c[] = {
        
        { { 0.7f,  0.7f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.7f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },

        { { 0.7f,  0.7f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.7f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },

        
        { { 0.7f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f, -0.1f, 1 }, { 1, 0, 1, 1 } },

        { { 0.7f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.7f,  0.9f, -0.1f, 1 }, { 1, 0, 1, 1 } },

        
        { { 0.7f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.7f,  0.7f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.7f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },

        { { 0.7f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.7f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.7f,  0.9f, -0.1f, 1 }, { 1, 0, 1, 1 } },

        
        { { 0.9f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.7f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },

        { { 0.9f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f, -0.1f, 1 }, { 1, 0, 1, 1 } },

        
        { { 0.7f,  0.9f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.7f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },

        { { 0.7f,  0.9f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.9f, -0.1f, 1 }, { 1, 0, 1, 1 } },

        
        { { 0.7f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.7f,  0.7f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.7f,  0.1f, 1 }, { 1, 0, 1, 1 } },

        { { 0.7f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.7f,  0.1f, 1 }, { 1, 0, 1, 1 } },
        { { 0.9f,  0.7f, -0.1f, 1 }, { 1, 0, 1, 1 } }
    };



    const char* vertex_shader = //program bezici pro kazdy vrchol
        "#version 330\n"
        "layout(location=0) in vec3 vp;" //vtupni atribut vrcholu, tento atribut je propojen s prvnim atributem vao
        "void main () {"
        "     gl_Position = vec4 (vp, 1.0);" //prevod na homogenni souradnici
        "}";

    const char* fragment_shader = //pro kazdy fragment trojuhelniku
        "#version 330\n"
        "out vec4 fragColor;" //vystupni barva fragmentu
        "void main () {"
        "     fragColor = vec4 (0.5, 0.0, 0.5, 1.0);" //nastaveni barvy
        "}";

    const char* vertex_shader_color = //program bezici pro kazdy vrchol
        "#version 330\n"
        "layout(location = 0) in vec4 vp;"   //vtupni atribut vrcholu, tento atribut je propojen s prvnim atributem vao
        "layout(location = 1) in vec4 color;" // barva vrcholu
        "out vec4 fragColor;"
        "void main () {"
        "    gl_Position = vp;" //prevod na homogenni souradnici
        "	 fragColor = color;"
        "}";

    const char* fragment_shader_color = //pro kazdy fragment trojuhelniku
        "#version 330\n"
        "in vec4 fragColor;" //vystupni barva fragmentu
        "out vec4 outColor;"
        "void main () {"
        "     outColor = fragColor;" //nastaveni barvy
        "}";

        
    Shader* shader = new Shader(vertex_shader_color, fragment_shader_color);
    ShaderProgram* shaderProgram = new ShaderProgram(shader);

    Shader* shader1 = new Shader(vertex_shader, fragment_shader);
    ShaderProgram* shaderProgram1 = new ShaderProgram(shader1);

    // vytvoøení modelu z dat
    Model* model_krychle = new Model(c, sizeof(c) / sizeof(Vertex), true,"triangles");
    Model* model_trojuhe = new Model(a, sizeof(a) / sizeof(Vertex), false,"triangles");
    Model* model_kruh = new Model(circle.data(), circle.size(), true, "triangles");
    Model* model_linie = new Model(linie, sizeof(linie) / sizeof(Vertex), true, "lines");
    

    // drawable object
    DrawableObject* obj_krychle = new DrawableObject(model_krychle, shaderProgram);

    DrawableObject* obj_trojuhe = new DrawableObject(model_trojuhe, shaderProgram1);
    DrawableObject* obj_kruh = new DrawableObject(model_kruh, shaderProgram);
    DrawableObject* obj_linie = new DrawableObject(model_linie, shaderProgram);


    this->addShaderProgram(shaderProgram);
    this->addShaderProgram(shaderProgram1);
    this->addDrawableObject(obj_krychle);
    this->addDrawableObject(obj_trojuhe);
    this->addDrawableObject(obj_kruh);
    this->addDrawableObject(obj_linie);

    return true;

}



