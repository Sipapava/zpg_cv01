#include "app.h"
#include "Scene.h"
#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Vertex.h"

// tvoje data
const Vertex b[] = {
    // první trojúhelník
    { { -0.5f, -0.5f, 0, 1 }, { 1, 0, 0, 1 } }, // levý dolní - červená
    { { -0.5f,  0.5f, 0, 1 }, { 1, 1, 0, 1 } }, // levý horní - žlutá
    { {  0.5f,  0.5f, 0, 1 }, { 0, 0, 1, 1 } }, // pravý horní - modrá

    // druhý trojúhelník
    { { -0.5f, -0.5f, 0, 1 }, { 1, 0, 0, 1 } }, // levý dolní - červená
    { {  0.5f,  0.5f, 0, 1 }, { 0, 0, 1, 1 } }, // pravý horní - modrá
    { {  0.5f, -0.5f, 0, 1 }, { 0, 1, 0, 1 } }  // pravý dolní - zelená
};

const Vertex c[] = {
    // přední stěna (z = 0.5)
    { {-0.5f, -0.5f,  0.5f, 1 }, { 1, 0, 0, 1 } },
    { { 0.5f, -0.5f,  0.5f, 1 }, { 0, 1, 0, 1 } },
    { { 0.5f,  0.5f,  0.5f, 1 }, { 0, 0, 1, 1 } },

    { {-0.5f, -0.5f,  0.5f, 1 }, { 1, 0, 0, 1 } },
    { { 0.5f,  0.5f,  0.5f, 1 }, { 0, 0, 1, 1 } },
    { {-0.5f,  0.5f,  0.5f, 1 }, { 1, 1, 0, 1 } },

    // zadní stěna (z = -0.5)
    { {-0.5f, -0.5f, -0.5f, 1 }, { 1, 0, 1, 1 } },
    { { 0.5f,  0.5f, -0.5f, 1 }, { 0, 1, 1, 1 } },
    { { 0.5f, -0.5f, -0.5f, 1 }, { 0, 0, 0, 1 } },

    { {-0.5f, -0.5f, -0.5f, 1 }, { 1, 0, 1, 1 } },
    { {-0.5f,  0.5f, -0.5f, 1 }, { 1, 1, 1, 1 } },
    { { 0.5f,  0.5f, -0.5f, 1 }, { 0, 1, 1, 1 } },

    // levá stěna (x = -0.5)
    { {-0.5f, -0.5f, -0.5f, 1 }, { 1, 0, 0, 1 } },
    { {-0.5f, -0.5f,  0.5f, 1 }, { 0, 1, 0, 1 } },
    { {-0.5f,  0.5f,  0.5f, 1 }, { 0, 0, 1, 1 } },

    { {-0.5f, -0.5f, -0.5f, 1 }, { 1, 0, 0, 1 } },
    { {-0.5f,  0.5f,  0.5f, 1 }, { 0, 0, 1, 1 } },
    { {-0.5f,  0.5f, -0.5f, 1 }, { 1, 1, 0, 1 } },

    // pravá stěna (x = 0.5)
    { { 0.5f, -0.5f, -0.5f, 1 }, { 1, 0, 1, 1 } },
    { { 0.5f,  0.5f,  0.5f, 1 }, { 0, 1, 1, 1 } },
    { { 0.5f, -0.5f,  0.5f, 1 }, { 0, 0, 0, 1 } },

    { { 0.5f, -0.5f, -0.5f, 1 }, { 1, 0, 1, 1 } },
    { { 0.5f,  0.5f, -0.5f, 1 }, { 0, 1, 1, 1 } },
    { { 0.5f,  0.5f,  0.5f, 1 }, { 0, 1, 0, 1 } },

    // horní stěna (y = 0.5)
    { {-0.5f,  0.5f, -0.5f, 1 }, { 1, 0, 0, 1 } },
    { {-0.5f,  0.5f,  0.5f, 1 }, { 0, 1, 0, 1 } },
    { { 0.5f,  0.5f,  0.5f, 1 }, { 0, 0, 1, 1 } },

    { {-0.5f,  0.5f, -0.5f, 1 }, { 1, 0, 0, 1 } },
    { { 0.5f,  0.5f,  0.5f, 1 }, { 0, 0, 1, 1 } },
    { { 0.5f,  0.5f, -0.5f, 1 }, { 1, 1, 0, 1 } },

    // spodní stěna (y = -0.5)
    { {-0.5f, -0.5f, -0.5f, 1 }, { 1, 0, 1, 1 } },
    { { 0.5f, -0.5f,  0.5f, 1 }, { 0, 1, 1, 1 } },
    { {-0.5f, -0.5f,  0.5f, 1 }, { 0, 0, 0, 1 } },

    { {-0.5f, -0.5f, -0.5f, 1 }, { 1, 0, 1, 1 } },
    { { 0.5f, -0.5f, -0.5f, 1 }, { 1, 1, 1, 1 } },
    { { 0.5f, -0.5f,  0.5f, 1 }, { 0, 1, 0, 1 } }
};


const char* vertex_shader2 = //program bezici pro kazdy vrchol
"#version 330\n"
"layout(location = 0) in vec4 vp;"   //vtupni atribut vrcholu, tento atribut je propojen s prvnim atributem vao
"layout(location = 1) in vec4 color;" // barva vrcholu
"out vec4 fragColor;"
"void main () {"
"    gl_Position = vp;" //prevod na homogenni souradnici
"	 fragColor = color;"
"}";

const char* fragment_shader2 = //pro kazdy fragment trojuhelniku
"#version 330\n"
"in vec4 fragColor;" //vystupni barva fragmentu
"out vec4 outColor;"
"void main () {"
"     outColor = fragColor;" //nastaveni barvy
"}";


int main(void)
{
    App app;
    if (!app.initialize()) {
        return -1;
    }

    // alokace shaderu a shader programu
    Shader* shader = new Shader(vertex_shader2, fragment_shader2);
    ShaderProgram* shaderProgram = new ShaderProgram(shader);

    // vytvoření modelu z dat
    Model* model = new Model(c, sizeof(c) / sizeof(Vertex));

    // drawable object
    DrawableObject* obj = new DrawableObject(model, shaderProgram);

    // scéna
    Scene* scene1 = new Scene(shaderProgram);
    scene1->addDrawableObject(obj);

    // přidání scény do aplikace
    app.addScene(scene1);

    // spuštění render smyčky s první scénou
    app.run(0);

    // --- uvolnění alokovaných objektů ---
    delete model;          // Model vlastní VAO a VBO, takže je uvolní
    delete shaderProgram;  // ShaderProgram vlastní OpenGL shadery
    delete shader;         // Shader jen texty, bezpečné uvolnit

    return 0;
}

