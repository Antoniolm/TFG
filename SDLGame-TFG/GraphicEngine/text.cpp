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

Text::Text(const string &  aMessage,const string & aFile,int aHeight,int aWidth,vec3f aPosition,TTF_Font * aFont){
    message=aMessage;
    fileTexture=aFile;
    height=aHeight;
    width=aWidth;
    position=aPosition;
    font=aFont;

    Mesh * textObject=new Mesh(string("geometries/text.obj"));
    textObject->init();

    Matrix4f * matrix=new Matrix4f();
    matrix->translation(position.x,position.y,position.z);

    textNode=new NodeSceneGraph();
    textNode->add(matrix);
    textNode->add(static_cast<Object3D*>(textObject));
}

//**********************************************************************//

Text::~Text()
{
    //TTF_CloseFont(font);
    //SDL_DestroyTexture(text);
    //SDL_FreeSurface(surface);
}

//**********************************************************************//

void Text::setParameters(const string &  aMessage,const string & aFile,int aHeight,int aWidth,vec3f aPosition,TTF_Font * aFont){
    message=aMessage;
    fileTexture=aFile;
    height=aHeight;
    width=aWidth;
    position=aPosition;
    font=aFont;

    Mesh * textObject=new Mesh("geometries/text.obj");
    textObject->init();

    Matrix4f * matrix=new Matrix4f();
    matrix->translation(position.x,position.y,position.z);

    textNode=new NodeSceneGraph();
    textNode->add(matrix);
    textNode->add(static_cast<Object3D*>(textObject));
}

//**********************************************************************//

void Text::setMessage(const string & aMessage){
    message=aMessage;
}

//**********************************************************************//

void Text::init(){
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  SDL_Color color = {0, 0, 0};
  surface = TTF_RenderText_Blended(font, message.c_str(),color);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                GL_UNSIGNED_BYTE, surface->pixels);

}

//**********************************************************************//

void Text::visualization(Context & vis){
    //Draw our text
    glBindTexture(GL_TEXTURE_2D, texture);
    textNode->visualization(vis);
}

//**********************************************************************//

void Text::updateState(float time){

}
