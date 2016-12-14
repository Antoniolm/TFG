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

#include "objectscene.h"

ObjectScene::ObjectScene()
{
    //ctor
}

//**********************************************************************//

ObjectScene::ObjectScene(Object3D * aObject){
    object=aObject;
}

//**********************************************************************//

ObjectScene::~ObjectScene()
{
    delete object;
}

//**********************************************************************//

void ObjectScene::visualization(Context & vis){
    object->visualization(vis);

    if(vis.visualization_mode==1){
        matrix=Matrix4f(vis.currentTransf);
        position=matrix.product(vec4f());
        generateBoundingbox();
    }

}

//**********************************************************************//

void ObjectScene::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap ){
    object->updateState(time,currentKeyStates,rootMap);
}

//**********************************************************************//

vec3f ObjectScene::getPosition(){
    return vec3f(position.x,position.y,position.z);
}

//**********************************************************************//

BoundingBox ObjectScene::getBoundingBox(){
    return boundingBox;
}

//**********************************************************************//

float ObjectScene::getDamage(){
    return 0.0;
}

//**********************************************************************//

void ObjectScene::generateBoundingbox(){
    boundingBox=object->getBoundingBox();
    GLfloat * mat=matrix.getMatrix();

    //Eliminate the translation
    mat[12]=0;mat[13]=0;mat[14]=0;
    Matrix4f matrixBounding;
    matrixBounding.setMatrix(mat);

    //generate vertex
    vector<vec4f> vertex;

    vertex.push_back(vec4f(boundingBox.minValue.x,boundingBox.maxValue.y,boundingBox.maxValue.z,1.0));   vertex.push_back(vec4f(boundingBox.minValue.x,boundingBox.minValue.y,boundingBox.maxValue.z,1.0));
    vertex.push_back(vec4f(boundingBox.maxValue.x,boundingBox.maxValue.y,boundingBox.maxValue.z,1.0));   vertex.push_back(vec4f(boundingBox.maxValue.x,boundingBox.minValue.y,boundingBox.maxValue.z,1.0));
    vertex.push_back(vec4f(boundingBox.minValue.x,boundingBox.maxValue.y,boundingBox.minValue.z,1.0));   vertex.push_back(vec4f(boundingBox.minValue.x,boundingBox.minValue.y,boundingBox.minValue.z,1.0));
    vertex.push_back(vec4f(boundingBox.maxValue.x,boundingBox.maxValue.y,boundingBox.minValue.z,1.0));   vertex.push_back(vec4f(boundingBox.maxValue.x,boundingBox.minValue.y,boundingBox.minValue.z,1.0));

    for(int i=0;i<vertex.size();i++)
        vertex[i]=matrixBounding.product(vertex[i]);

    //Generate the new boundingBox
    float maxX,maxY,maxZ,minX,minY,minZ;
    maxX=vertex[0].x;  maxY=vertex[0].y;  maxZ=vertex[0].z;
    minX=vertex[0].x;  minY=vertex[0].y;  minZ=vertex[0].z;

    int tam=vertex.size();

    for(int i=1;i<tam;i++){
        if(vertex[i].x >maxX) maxX=vertex[i].x;
        if(vertex[i].y >maxY) maxY=vertex[i].y;
        if(vertex[i].z >maxZ) maxZ=vertex[i].z;

        if(vertex[i].x < minX) minX=vertex[i].x;
        if(vertex[i].y < minY) minY=vertex[i].y;
        if(vertex[i].z < minZ) minZ=vertex[i].z;
	}

	boundingBox.maxValue=vec3f(maxX,maxY,maxZ);
	boundingBox.minValue=vec3f(minX,minY,minZ);
}

