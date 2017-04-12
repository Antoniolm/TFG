// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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

#include "weapon.h"

Weapon::Weapon(vec3f aPos,WeaponType atype,float aDamage,MeshIndex mesh,MaterialIndex material)
{
    damage=aDamage;
    type=atype;
    position=vec4f(aPos.x,aPos.y,aPos.z,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    Matrix4f * transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(materialCollect->getMaterial(material));
    root->add(meshCollect->getMesh(mesh));

    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Weapon::~Weapon()
{
    delete root;
}
//**********************************************************************//

void Weapon::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Weapon::updateState(GameState & gameState){

}

//**********************************************************************//

void Weapon::setDamage(float value){
    damage=value;
}

//**********************************************************************//

float Weapon::getDamage(){
    return damage;
}

//**********************************************************************//

WeaponType Weapon::getType(){
    return type;
}

//**********************************************************************//

void Weapon::setWeapon(const Weapon & weapon){
    damage=weapon.damage;
    type=weapon.type;
    root=weapon.root;
}

