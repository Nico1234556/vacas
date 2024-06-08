#pragma once
#ifndef __HASHENTIDAD_HPP__
#define __HASHENTIDAD_HPP__
using namespace std;

#include "Vaca.h"
#include <string>

class HashEntidad {
private:
    string key;
    Vaca value;

public:
    HashEntidad(const string& key, const Vaca& value) : key(key), value(value) {}

    const string& getKey() const { return key; }
    const Vaca& getValue() const { return value; }
};

#endif // !__HASHENTIDAD_HPP__

