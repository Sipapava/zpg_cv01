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

    app.createScene("normal");
    app.createScene("normal");
    app.createScene("normal");
    app.createScene("normal");
    app.createScene("game");
   
   
    Scene* homogenus = app.getScene(0);
    Scene* space = app.getScene(1);
    Scene* cars = app.getScene(2);
    Scene* forest = app.getScene(3);
    Scene* catchGame = app.getScene(4);

    app.prepareModelsFromManager();

    bool h = homogenus->prepareHomogenusChange();
    bool s = space->prepareSolarSystem();
    bool cs = cars->prepareFlyingCars();
    bool fo = forest->prepareForest();
    bool cg = catchGame->prepareCatchGame();

    bool control = app.prepareController();
    app.dummyStencilRead();

    if ( h && s && cs && fo && cg && control) {
        app.run(0);
    }

    return 0;
}

