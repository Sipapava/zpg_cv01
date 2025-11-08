#include "drawableSky.h"

drawableSky::drawableSky(Model* model,ShaderProgram* shader)
    : DrawableObject(model, shader) // volání konstruktoru DrawableObject
{
    // pøípadnì další inicializace specifická pro skybox/skydome
}

void drawableSky::draw() {
    if (!shaderProgram || !model) return;

    // Nastavení hloubkového testu
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    

    shaderProgram->setShaderProgram();
    shaderProgram->ProjectionApply();

    // Bind textur (cubemap nebo panorama)
    for (auto t : textures) {
        if (!t) continue;
        t->ActiveTexture();
        t->BindTexture();
        shaderProgram->setUniformInt(t->GetSlot(), t->GetType().c_str());
    }

    // Vykreslení modelu
    model->Draw();

    shaderProgram->resetShaderProgram();

    // Vrátíme pùvodní culling a depth funkci
    
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}
