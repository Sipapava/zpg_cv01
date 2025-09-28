#include "app.h"
#include "Scene.h"
#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Vertex.h"







int main(void)
{
    App app;
    if (!app.initialize()) {
        return -1;
    }

    
    Scene* scene1 = new Scene();
   
    app.addScene(scene1);
    bool t = scene1->prepareTestSceneCv02();
    if (t) {
        app.run(0);
    }


    return 0;
}

