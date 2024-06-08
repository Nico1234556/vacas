#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vaca.h"
#include "Arbolbinario.hpp"
#include "Sorting.hpp"
#include <vector>
#include "HashEntidad.hpp"
#include "HashTabla.hpp"

using namespace std;

void mostrarmenu() {
    std::cout << "\n========================================\n";
    std::cout << "===            Menu productos          ===\n";
    std::cout << "========================================\n\n";
    std::cout << "1. Insertar 300 vacas a hashtable\n";
    std::cout << "2. Insertar 300 vacas a arbol binario\n";
    std::cout << "3. Buscar por ID\n";
    std::cout << "4. Ordenar por precio\n";
    std::cout << "5. Eliminar producto por ID\n";
    std::cout << "6. Verificar si el nodo mayor es múltiplo de 5\n";
    std::cout << "7. Salir\n";
    std::cout << "========================================\n";
    std::cout << "Seleccione una opcion: ";
}

string generarNombreAleatorio() {
    const vector<string> nombres = { "Leche", "Pan", "Queso", "Jamon", "Cereal", "Mantequilla", "Arroz", "Azucar", "Sal", "Aceite" };
    return nombres[rand() % nombres.size()];
}

string generarColorAleatoria() {
    const vector<string> categorias = { "blanca", "negra", "blanca con manchas negras", "marron", "marron claro" };
    return categorias[rand() % categorias.size()];
}

Vaca generarVacaAleatorio() {
    static int id = 1;
    string nombre = generarNombreAleatorio();
    int Kg = (rand() % 1000) / 10;
    string color = generarColorAleatoria();
    int edad = rand() % 100;
    int peso = rand() % 100;
    return Vaca(id++, nombre, Kg, color, edad, peso);
}

void generarDatosVaca(vector<Vaca*>& productos, int n) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        productos.push_back(new Vaca(generarVacaAleatorio()));
    }
}

bool compararPorEdad(const Vaca* a, const Vaca* b) {
    return a->edad < b->edad;
}

int main() {
    HashTabla hashTable(300);
    ArbolB<Vaca> arbolBinario;
    vector<Vaca*> Vacas;
    Sorting<Vaca*> sorter;
    int opcion;

    // Generar datos de productos
    generarDatosVaca(Vacas, 300);

    do {
        mostrarmenu();
        cin >> opcion;
        switch (opcion) {
        case 1:
            system("cls");
            /* Inserción de productos en HashTable */
            for (const auto& Vaca : Vacas) {
                hashTable.insertar(to_string(Vaca->Id), *Vaca);
            }
            cout << "Se han insertado 300 productos en la tabla hash." << endl;
            break;
        case 2:
            system("cls");
            /* Inserción de productos en Árbol Binario */
            for (const auto& Vaca : Vacas) {
                arbolBinario.insertar(*Vaca);
            }
            cout << "Se han insertado 300 productos en el árbol binario." << endl;
            break;
        case 3: {
            system("cls");
            /* Búsqueda de productos por ID */
            int idBuscado;
            cout << "Ingrese el ID del producto que desea buscar: ";
            cin >> idBuscado;

            const Vaca* VacaHash = hashTable.buscar(to_string(idBuscado));
            const Vaca* VacaArbol = arbolBinario.buscar(Vaca(idBuscado, "", 0, "", 0, ""));

            if (VacaHash != nullptr) {
                cout << "Vaca encontrada en la tabla hash: " << *VacaHash << endl;
            }
            else {
                cout << "Vaca no encontrada en la tabla hash." << endl;
            }

            if (VacaArbol != nullptr) {
                cout << "Vaca encontrada en el árbol binario: " << *VacaArbol << endl;
            }
            else {
                cout << "Vaca no encontrada en el árbol binario." << endl;
            }
            break;
        }
        case 4:
            system("cls");
            /* Ordenación de productos */
            int metodoOrdenamiento;
            cout << "Seleccione el método de ordenamiento:\n";
            cout << "1. QuickSort\n";
            cout << "2. MergeSort\n";
            cout << "3. HeapSort\n";
            cout << "Seleccione una opción: ";
            cin >> metodoOrdenamiento;

            switch (metodoOrdenamiento) {
            case 1:
                cout << "Ordenando con QuickSort..." << endl;
                sorter.quicksort(Vacas, compararPorEdad);
                for (const auto& Vaca : Vacas) {
                    cout << *Vaca << endl;
                }
                break;
            case 2:
                cout << "Ordenando con MergeSort..." << endl;
                sorter.mergesort(Vacas, compararPorEdad);
                for (const auto& Vaca : Vacas) {
                    cout << *Vaca << endl;
                }
                break;
            case 3:
                cout << "Ordenando con HeapSort..." << endl;
                sorter.heapsort(Vacas, compararPorEdad);
                for (const auto& Vaca : Vacas) {
                    cout << *Vaca << endl;
                }
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
            }
            break;
        case 5: {
            system("cls");
            /* Eliminación de productos por ID */
            int idAEliminar;
            cout << "Ingrese el ID de la Vaca que desea eliminar: ";
            cin >> idAEliminar;

            bool eliminadoArbol = arbolBinario.eliminar(Vaca(idAEliminar, "", 0, "", 0, ""));
            const Vaca* VacaHash = hashTable.buscar(to_string(idAEliminar));
            if (VacaHash != nullptr) {
                hashTable.eliminar(to_string(idAEliminar));
                cout << "Vaca eliminada de la tabla hash." << endl;
            }
            else {
                cout << "Vaca no encontrada en la tabla hash." << endl;
            }

            if (eliminadoArbol) {
                cout << "Vaca eliminada del árbol binario." << endl;
            }
            else {
                cout << "Vaca no encontrada en el árbol binario." << endl;
            }
            break;
        }
        case 6:
            system("cls");
            /* Verificar si el nodo mayor es múltiplo de 5 */
            arbolBinario.verificarMayorMultiploDe5();
            break;
        case 7:
            system("cls");
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opción no válida.\n";
            break;
        }
    } while (opcion != 7);

    return 0;
}
