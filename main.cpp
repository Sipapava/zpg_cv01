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

    
    //Scene* scene1 = new Scene();
    //Scene* scene2 = new Scene();
    Scene* scene3 = new Scene();
   
    //app.addScene(scene1);
    //app.addScene(scene2);
    app.addScene(scene3);
   // bool t = scene1->prepareTestSceneCv03T1();
   // bool p = scene2->prepareTestSceneCv03T2();
    bool z = scene3->prepareTestSceneCv03T3();
    if ( z) {
        app.run(0);
    }


    return 0;
}

