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

#include "enemy.h"
#include "../GraphicEngine/iaenemy.h"

Enemy::Enemy(){

}

//**********************************************************************//

Enemy::Enemy(float aLife,vec3f aPosition,vec3f aRadioActivity)
{
}

//**********************************************************************//

Enemy::~Enemy()
{
    delete currentText;
    for(vector<Matrix4f *>::iterator it = moveMatrix.begin() ; it != moveMatrix.end(); ++it){
        delete (*it);
    }
}

//**********************************************************************//

void Enemy::visualization(Context & cv){
    if(position.x>cv.minVisualPosition.x && position.x<cv.maxVisualPosition.x
       && position.y>cv.minVisualPosition.y && position.y<cv.maxVisualPosition.y)
            root->visualization(cv);

    if(activatedDialog){
        currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
        currentText->visualization(cv);
    }
}

//**********************************************************************//

void Enemy::updateState(float time,ControllerManager * controller,RootMap * rootMap){

}

//**********************************************************************//

void Enemy::activatedEnemy(bool value){
    enemyActivate=value;
}

//**********************************************************************//

bool Enemy::isActivate(){
    return enemyActivate;
}

//**********************************************************************//

vec3f Enemy::getRadioActivity(){
    return radioActivity;
}

//**********************************************************************//

 float Enemy::getLife(){
    return life;
 }

 //**********************************************************************//

 void Enemy::takeDamage(vec3f posAvatar,avatarDirection dirAvatar,float value,const vector<Enemy *> & enemies){
    //check Distance
    float distance=sqrt(pow(position.x-posAvatar.x,2.0)+pow(position.z-posAvatar.z,2.0));

    if(detectHit(posAvatar,dirAvatar) && dmgDelay<(currentTime-250) && distance<1.0){
        addLife(value);
        stringstream convert;
        int lastValue;

        if(activatedDialog){
            string currentValue=currentText->getMessage();
            lastValue=atoi(currentValue.c_str());
            value+=lastValue;
        }
        convert << value;

        activatedDialog=true;
        currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
        currentText->setMessage(convert.str());
        currentText->init();

        dmgDelay=currentTime;

        if(!isImpacted && canImpact(dirAvatar,enemies))
            activeImpact(dirAvatar);

        enemySound[1]->stop();
        enemySound[1]->play();

        //Check if was activated
        if(!enemyActivate)
            enemyActivate=true;
    }
 }

 //**********************************************************************//

void Enemy::takeDamage(float value){
    addLife(value);

    stringstream convert;
    int lastValue;

    if(activatedDialog){
        string currentValue=currentText->getMessage();
        lastValue=atoi(currentValue.c_str());
        value+=lastValue;
    }

    convert << value;

    activatedDialog=true;
    currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
    currentText->setMessage(convert.str());
    currentText->init();

    enemySound[1]->stop();
    enemySound[1]->play();
 }

