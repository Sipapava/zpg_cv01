#include "drawableSky.h"

drawableSky::drawableSky(Model* model,ShaderProgram* shader)
    : DrawableObject(model, shader) 
{
  
}

void drawableSky::draw() {
    if (!shaderProgram || !model) return;

    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glStencilMask(0x00); // musim zakazat zapis, zustava tam nastevni z posledniho objektu minule smycky a tak se prepisuji
    shaderProgram->setShaderProgram();
    shaderProgram->ProjectionApply();

  
    for (auto t : textures) {
        if (!t) continue;
        t->ActiveTexture();
        t->BindTexture();
        shaderProgram->setUniformInt(t->GetSlot(), t->GetType().c_str());
    }

    
    model->Draw();

    shaderProgram->resetShaderProgram();

   
    
    glClear(GL_DEPTH_BUFFER_BIT);
}
