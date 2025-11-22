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
    
   
  
    
   // Scene* scene2 = new Scene();
   
    
    
   app.createScene();
    app.createScene();
    //app.addScene(scene2);
   
    Scene* scene3 = app.getScene(0);
    Scene* scene4 = app.getScene(1);

    scene3->createModelsForScenes(); //udelat z toho statickou
   bool z = scene3->prepareTestSceneCv05T3();
    bool a = scene4->prepareTestSceneCv05T4();
    //bool b = scene2->prepareTestSceneCv05T2();
 
   
    bool d = app.prepareController();
    if ( z && a) {
        GLuint dummy; //na toto metodu
        glReadPixels(0, 0, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &dummy);

        app.run(0);
    }


    return 0;
}

