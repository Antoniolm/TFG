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

#include "collection.h"

template <typename T,typename T2>
Collection<T,T2>::Collection()
{
    //ctor
}

//**********************************************************************//

template <typename T,typename T2>
Collection<T,T2>::~Collection()
{
    //dtor
}

//**********************************************************************//

template <typename T,typename T2>
void Collection<T,T2>::addElement(T * element){
    collection.push_back(element);
}

//**********************************************************************//

template <typename T,typename T2>
void Collection<T,T2>::addIndex(string index,T2 value){
    enumMap.insert(pair<string,T2> (index,value));
}

//**********************************************************************//

template <typename T,typename T2>
T * Collection<T,T2>::getElement(T2 value){
    return collection[value];
}

//**********************************************************************//

template <typename T,typename T2>
T * Collection<T,T2>::getElement(string index){
    return collection[(enumMap.find(index))->second];
}
