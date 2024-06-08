#pragma once
#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <fstream>
#include <string>
#include <sstream>
#include "Arbolbinario.hpp"
#include "Vaca.h"

using namespace std;

#define NOMBRE_ARCHIVO "vacas.csv"

class Archivos {
public:
    static void lecturaDatosDeArchivo(ArbolB<Vaca>& arbolBinario, vector<Vaca*>& vacas) {
        ifstream archIN(NOMBRE_ARCHIVO);

        if (!archIN.is_open()) {
            cout << "Error: No se pudo abrir el archivo !!!" << endl;
            exit(1);
        }

        string linea;
        char delimitador = '|';

        // Encabezado: Leemos la primera línea para descartarla, pues es el encabezado
        getline(archIN, linea);

        // Contenido: Leemos todas las líneas
        while (getline(archIN, linea)) {
            stringstream stream(linea);

            int id, kg, edad;
            float peso;
            string nombre, color;

            stream >> id;
            stream.ignore();
            getline(stream, nombre, delimitador);
            stream >> kg;
            stream.ignore();
            getline(stream, color, delimitador);
            stream >> edad;
            stream.ignore();
            stream >> peso;

            Vaca* nuevaVaca = new Vaca(id, nombre, kg, color, edad, peso);
            arbolBinario.insertar(*nuevaVaca);
            vacas.push_back(nuevaVaca);
        }

        archIN.close();
    }

    static void escrituraDatosEnArchivo(const vector<Vaca*>& vacas) {
        ofstream archOUT(NOMBRE_ARCHIVO);

        if (!archOUT.is_open()) {
            cout << "Error: No se pudo abrir el archivo !!!" << endl;
            exit(1);
        }

        // Escribimos el encabezado
        archOUT << "Id|Nombre|Kg|Color|Edad|Peso" << endl;

        for (const auto& vaca : vacas) {
            archOUT << vaca->Id << "|" << vaca->nombre << "|" << vaca->Kg << "|" << vaca->color << "|" << vaca->edad << "|" << vaca->peso << endl;
        }

        archOUT.close();
        cout << "Datos escritos en el archivo " << NOMBRE_ARCHIVO << " exitosamente." << endl;
    }
};

#endif // ARCHIVOS_H
