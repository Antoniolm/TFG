// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David López Machado
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "text.h"

Text::Text()
{
    //ctor
}

//**********************************************************************//

Text::Text(const string &  aMessage,const string & aTexture,vec3f aPosition,TTF_Font * aFont){
    message=aMessage;
    fileTexture=aTexture;
    position=aPosition;
    font=aFont;

    Mesh * textObject=new Mesh(string("geometries/text.obj"));
    textObject->init();

    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,fileTexture);

    Matrix4f * transText=new Matrix4f();
    transText->translation(position.x,position.y,position.z);
    Matrix4f * scaleText=new Matrix4f();
    scaleText->scale(1.0,0.3,1.0);

    textNode=new NodeSceneGraph();
    textNode->add(transText);
    textNode->add(scaleText);
    textNode->add(textObject);

    transText=new Matrix4f();
    transText->translation(position.x,position.y,position.z-0.1);
    scaleText=new Matrix4f();
    scaleText->scale(1.2,1.1,1.0);

    backNode=new NodeSceneGraph();
    backNode->add(transText);
    backNode->add(scaleText);
    backNode->add(material);
    backNode->add(textObject);

}

//**********************************************************************//

Text::~Text()
{
    glDeleteTextures(1, &textureText);
    SDL_FreeSurface(surface);
}

//**********************************************************************//

void Text::setParameters(const string &  aMessage,const string & aTexture,vec3f aPosition,TTF_Font * aFont){
    message=aMessage;
    fileTexture=aTexture;
    position=aPosition;
    font=aFont;

    Mesh * textObject=new Mesh("geometries/text.obj");
    textObject->init();

    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),32.0f,"./textures/dialog.png");

    Matrix4f * transText=new Matrix4f();
    transText->translation(position.x,position.y,position.z);
    Matrix4f * scaleText=new Matrix4f();
    scaleText->scale(1.0,0.3,1.0);

    textNode=new NodeSceneGraph();
    textNode->add(transText);
    textNode->add(scaleText);
    textNode->add(static_cast<Object3D*>(textObject));

    backNode=new NodeSceneGraph();
    backNode->add(transText);
    backNode->add(scaleText);
    backNode->add(material);
    backNode->add(textObject);
}

//**********************************************************************//

void Text::setMessage(const string & aMessage){
    message=aMessage;
}

//**********************************************************************//

void Text::init(){
    glGenTextures(1, &textureText);
    glBindTexture(GL_TEXTURE_2D, textureText);

    SDL_Color color = {0, 0, 0};
    surface = TTF_RenderText_Blended(font, message.c_str(),color);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, surface->pixels);

}

//**********************************************************************//

void Text::visualization(Context & vis){
    //Draw our texture of background
    backNode->visualization(vis);

    //Draw our text
    glBindTexture(GL_TEXTURE_2D, textureText);
    textNode->visualization(vis);

}

//**********************************************************************//

void Text::updateState(float time){

}
