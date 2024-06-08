#ifndef VACA_H
#define VACA_H

#include <iostream>
#include <string>
using namespace std;

class Vaca {
public:
    int Id;
    string nombre;
    int Kg;
    string color;
    int edad;
    float peso;

    // Constructor predeterminado
    Vaca() : Id(0), Kg(0), edad(0), peso(0) {}

    // Constructor con parámetros
    Vaca(int id, const string& nombre, int Kg, const string& color, int edad, float peso)
        : Id(id), nombre(nombre), Kg(Kg), color(color), edad(edad), peso(peso) {}

    // Constructor simplificado
    Vaca(int id)
        : Id(id), nombre(""), Kg(0), color(""), edad(0), peso(0) {}

    bool operator<(const Vaca& other) const {
        return this->edad < other.edad;
    }

    bool operator==(const Vaca& other) const {
        return this->Id == other.Id;
    }

    bool operator>(const Vaca& other) const {
        return this->edad > other.edad;
    }

    friend ostream& operator<<(ostream& os, const Vaca& vaca) {
        os << "Vaca(Id: " << vaca.Id << ", Nombre: " << vaca.nombre << ", Kilos: " << vaca.Kg << ", Color: " << vaca.color << ", Edad: " << vaca.edad << ", Peso: " << vaca.peso << ")";
        return os;
    }

    friend istream& operator>>(istream& is, Vaca& vaca) {
        is >> vaca.Id;
        is.ignore();
        getline(is, vaca.nombre, '|');
        is >> vaca.Kg;
        is.ignore();
        getline(is, vaca.color, '|');
        is >> vaca.edad;
        is.ignore();
        is >> vaca.peso;
        return is;
    }
};

#endif // VACA_H
