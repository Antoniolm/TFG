#include "materialcollection.h"

MaterialCollection* MaterialCollection::instance = NULL;

MaterialCollection::MaterialCollection()
{
    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeGrass.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeSand.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeBox.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/Wood.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mushrooms.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/grass.png");
    collection.push_back(material);

    material=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/water.png");
    collection.push_back(material);

    material=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/void.png");
    collection.push_back(material);

    material=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/textureCoin.png");
    collection.push_back(material);

    //Hero material
    material=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),32.0f,"./textures/leaf.jpg");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/textureLeg.png");
    collection.push_back(material);

    //Enemy material
    material=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/wood.png");
    collection.push_back(material);

    material=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/textureLeg.png");
    collection.push_back(material);

    //Create our map
    enumMap.insert(pair<string,materialElement> ("mCUBE_GRASS",mCUBE_GRASS));
    enumMap.insert(pair<string,materialElement> ("mCUBE_SAND",mCUBE_SAND));
    enumMap.insert(pair<string,materialElement> ("mCUBE_BOX",mCUBE_BOX));
    enumMap.insert(pair<string,materialElement> ("mWOOD",mWOOD));
    enumMap.insert(pair<string,materialElement> ("MUSH",MUSH));
    enumMap.insert(pair<string,materialElement> ("mGRASS",mGRASS));
    enumMap.insert(pair<string,materialElement> ("mWATER",mWATER));
    enumMap.insert(pair<string,materialElement> ("mVOID",mVOID));
    enumMap.insert(pair<string,materialElement> ("mCOIN",mCOIN));
    enumMap.insert(pair<string,materialElement> ("mARMOUR",mARMOUR));
    enumMap.insert(pair<string,materialElement> ("mHAND",mHAND));
    enumMap.insert(pair<string,materialElement> ("mDWOOD",mDWOOD));
    enumMap.insert(pair<string,materialElement> ("mDHAND",mDHAND));
}

//**********************************************************************//

MaterialCollection::~MaterialCollection()
{
    //dtor
}

//**********************************************************************//

Material* MaterialCollection::getMaterial(materialElement element){
    return collection[element];
}

//**********************************************************************//

Material* MaterialCollection::getMaterial(string element){
    return collection[(enumMap.find(element))->second];
}
