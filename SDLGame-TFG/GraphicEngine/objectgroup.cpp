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


#include "objectgroup.h"

ObjectGroup::ObjectGroup(MaterialIndex materialIndex){
    MaterialCollection *materialCollect=MaterialCollection::getInstance();
    root=new NodeSceneGraph();
    root->add(materialCollect->getMaterial(materialIndex));

}

//**********************************************************************//

ObjectGroup::~ObjectGroup()
{
    //dtor
}

//**********************************************************************//

void ObjectGroup::addObject(vec3f position,MeshIndex meshIndex){
    vector<vec3f> currentVertex;
    vector<GLushort> currentTriangles;
    vector<vec3f> currentNormals;
    vector<vec2f> currentTextureCord;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    Mesh * mesh=meshCollect->getMesh(meshIndex);

    currentVertex=mesh->getVertex();
    currentTriangles=mesh->getTriangles();
    currentNormals=mesh->getNormals();
    currentTextureCord=mesh->getTextCoord();

    int shift=triangles.size();
    for(int i=0;i<currentTriangles.size();i++){
        vertex.push_back(vec3f(currentVertex[i].x+position.x,currentVertex[i].y+position.y,currentVertex[i].z+position.z));
        normals.push_back(currentNormals[i]);
        textureCord.push_back(currentTextureCord[i]);
        triangles.push_back(currentTriangles[i]+shift);
    }
}

//**********************************************************************//

void ObjectGroup::init(){
    Mesh * mesh=new Mesh("geometries/sphere.obj");
    mesh->init(vertex,triangles,normals,textureCord);
    root->add(mesh);
}

//**********************************************************************//

void ObjectGroup::visualization(Context & vis){
    //Draw our object
    root->visualization(vis);
}

//**********************************************************************//

void ObjectGroup::updateState(float time,Controller * controller,RootMap * rootMap){
}

