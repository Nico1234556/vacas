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
    static void lecturaDatosDeArchivo(ArbolB<Vaca>& arbolBinario) {
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

            Vaca nuevaVaca(id, nombre, kg, color, edad, peso);
            arbolBinario.insertar(nuevaVaca);
        }

        archIN.close();
    }

    static void escrituraDatosEnArchivo(const ArbolB<Vaca>& arbolBinario) {
        ofstream archOUT(NOMBRE_ARCHIVO);

        if (!archOUT.is_open()) {
            cout << "Error: No se pudo abrir el archivo !!!" << endl;
            exit(1);
        }

        // Escribimos el encabezado
        archOUT << "Id|Nombre|Kg|Color|Edad|Peso" << endl;

        guardarEnArchivoRecursivo(arbolBinario.raiz, archOUT);

        archOUT.close();
        cout << "Datos escritos en el archivo " << NOMBRE_ARCHIVO << " exitosamente." << endl;
    }

private:
    static void guardarEnArchivoRecursivo(Nodo<Vaca>* nodo, ofstream& archOUT) {
        if (nodo == nullptr) return;
        archOUT << nodo->elemento << endl;
        guardarEnArchivoRecursivo(nodo->izq, archOUT);
        guardarEnArchivoRecursivo(nodo->der, archOUT);
    }
};

#endif // ARCHIVOS_H
