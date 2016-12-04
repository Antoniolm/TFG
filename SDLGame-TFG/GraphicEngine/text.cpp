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

Text::Text(const string & aFile,int aHeight,int aWidth,vec3f aPosition,TTF_Font * aFont){
    fileTexture=aFile;
    height=aHeight;
    width=aWidth;
    position=aPosition;
    font=aFont;
}

//**********************************************************************//

Text::~Text()
{
    //dtor
}

//**********************************************************************//

void Text::setParameters(const string & aFile,int aHeight,int aWidth,vec3f aPosition,TTF_Font * aFont){
    fileTexture=aFile;
    height=aHeight;
    width=aWidth;
    position=aPosition;
    font=aFont;
}

//**********************************************************************//

void Text::init(){

}

//**********************************************************************//

void Text::visualization(Context & vis){

}

//**********************************************************************//

void Text::updateState(float time){

}

//**********************************************************************//

void Text::activeText(Shader * currentShader){

}
