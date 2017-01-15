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

#ifndef COLLECTION_H
#define COLLECTION_H

#include <map>
#include <vector>
#include <string>

using namespace std;

template <class T,class T2>
class Collection
{
    public:
        /** Default constructor */
        Collection();
        /** Default destructor */
        virtual ~Collection();

        void addElement(T * element);
        void addIndex(string index,T2 value);

        T * getElement(T2 value);
        T * getElement(string index);
    protected:

    private:
        vector<T *> collection;
        map<string,T2> enumMap;

};

#endif // COLLECTION_H
