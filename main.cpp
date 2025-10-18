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
    Scene* scene3 = new Scene();
    Scene* scene4 = new Scene();
    Scene* scene2 = new Scene();
   
    
    app.addScene(scene1);
    app.addScene(scene3);
    app.addScene(scene4);
    app.addScene(scene2);
   
    bool z = scene3->prepareTestSceneCv05T3();
    bool a = scene4->prepareTestSceneCv05T4();
    bool b = scene2->prepareTestSceneCv05T2();
   bool p = scene1->prepareTestSceneCv05T1();
   
    bool d = app.prepareController();
    if ( z && d && a && p ) {
        
        app.run(0);
    }


    return 0;
}

