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
    
    
    
    Scene* scene3 = new Scene();
   
    
    app.addScene(scene3);
   
    bool z = scene3->prepareTestSceneCv04T1();
   
    bool d = app.prepareController();
    if ( z && d ) {
        
        app.run(0);
    }


    return 0;
}

