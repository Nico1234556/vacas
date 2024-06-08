#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vaca.h"
#include "Arbolbinario.hpp"
#include "Sorting.hpp"
#include "Archivos.hpp"
#include <vector>
#include "HashEntidad.hpp"
#include "HashTabla.hpp"

using namespace std;

void mostrarmenu() {
    std::cout << "\n========================================\n";
    std::cout << "===            Menu vacas             ===\n";
    std::cout << "========================================\n\n";
    std::cout << "1. Insertar 300 vacas a hashtable\n";
    std::cout << "2. Insertar 300 vacas a arbol binario\n";
    std::cout << "3. Buscar por ID\n";
    std::cout << "4. Ordenar por edad\n";
    std::cout << "5. Eliminar vaca por ID\n";
    std::cout << "6. Verificar si el nodo mayor es múltiplo de 3\n";
    std::cout << "7. Guardar datos en archivo\n";
    std::cout << "8. Leer datos de archivo\n";
    std::cout << "9. Salir\n";
    std::cout << "========================================\n";
    std::cout << "Seleccione una opcion: ";
}

string generarNombreAleatorio() {
    const vector<string> nombres = { "Vaca1", "Vaca2", "Vaca3", "Vaca4", "Vaca5", "Vaca6", "Vaca7", "Vaca8", "Vaca9", "Vaca10" };
    return nombres[rand() % nombres.size()];
}

string generarColorAleatoria() {
    const vector<string> colores = { "Blanca", "Negra", "Manchada", "Marrón", "Marrón claro" };
    return colores[rand() % colores.size()];
}

Vaca generarVacaAleatorio() {
    static int id = 1;
    string nombre = generarNombreAleatorio();
    int Kg = rand() % 100;
    string color = generarColorAleatoria();
    int edad = rand() % 20;
    float peso = rand() % 100 + (rand() % 100) / 100.0;
    return Vaca(id++, nombre, Kg, color, edad, peso);
}

void generarDatosVaca(vector<Vaca*>& vacas, int n) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        vacas.push_back(new Vaca(generarVacaAleatorio()));
    }
}

bool compararPorEdad(const Vaca* a, const Vaca* b) {
    return a->edad < b->edad;
}

bool compararPorNombre(const Vaca* a, const Vaca* b) {
    return a->nombre < b->nombre;
}

void busquedaBinaria(const std::vector<Vaca*>& vacas, int edad) {
    auto it = std::lower_bound(vacas.begin(), vacas.end(), edad, [](const Vaca* vaca, int value) {
        return vaca->edad < value;
        });

    if (it != vacas.end() && (*it)->edad == edad) {
        std::cout << "Vacas encontradas en los índices: ";
        while (it != vacas.end() && (*it)->edad == edad) {
            std::cout << std::distance(vacas.begin(), it) << " ";
            ++it;
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No se encontraron vacas con la edad " << edad << std::endl;
    }
}

void ordenarPorEdadYNombre(std::vector<Vaca*>& vacas) {
    std::sort(vacas.begin(), vacas.end(), [](const Vaca* a, const Vaca* b) {
        if (a->edad == b->edad) {
            return a->nombre < b->nombre;
        }
        return a->edad < b->edad;
        });
}

int main() {
    HashTabla hashTable(300);
    ArbolB<Vaca> arbolBinario;
    vector<Vaca*> vacas;
    Sorting<Vaca*> sorter;
    int opcion;

    // Generar datos de vacas
    generarDatosVaca(vacas, 300);

    do {
        mostrarmenu();
        cin >> opcion;
        switch (opcion) {
        case 1:
            system("cls");
            /* (1 punto) Inserción de vacas en HashTable */
            for (const auto& vaca : vacas) {
                hashTable.insertar(to_string(vaca->Id), *vaca);
            }
            cout << "Se han insertado 300 vacas en la tabla hash." << endl;
            break;
        case 2:
            system("cls");
            /* (4 puntos) Inserción de vacas en Árbol Binario */
            for (const auto& vaca : vacas) {
                arbolBinario.insertar(*vaca);
            }
            cout << "Se han insertado 300 vacas en el árbol binario." << endl;
            break;
        case 3: {
            system("cls");
            /* (3 puntos) Búsqueda de vacas por ID */
            int idBuscado;
            cout << "Ingrese el ID de la vaca que desea buscar: ";
            cin >> idBuscado;

            const Vaca* vacaHash = hashTable.buscar(to_string(idBuscado));
            const Vaca* vacaArbol = arbolBinario.buscar(Vaca(idBuscado));

            if (vacaHash != nullptr) {
                cout << "Vaca encontrada en la tabla hash: " << *vacaHash << endl;
            }
            else {
                cout << "Vaca no encontrada en la tabla hash." << endl;
            }

            if (vacaArbol != nullptr) {
                cout << "Vaca encontrada en el árbol binario: " << *vacaArbol << endl;
            }
            else {
                cout << "Vaca no encontrada en el árbol binario." << endl;
            }
            break;
        }
        case 4:
            system("cls");
            /* (3 puntos) Ordenación de vacas por edad y nombre */
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
                sorter.quicksort(vacas, compararPorEdad);
                for (const auto& vaca : vacas) {
                    cout << *vaca << endl;
                }
                break;
            case 2:
                cout << "Ordenando con MergeSort..." << endl;
                sorter.mergesort(vacas, compararPorEdad);
                for (const auto& vaca : vacas) {
                    cout << *vaca << endl;
                }
                break;
            case 3:
                cout << "Ordenando con HeapSort..." << endl;
                sorter.heapsort(vacas, compararPorEdad);
                for (const auto& vaca : vacas) {
                    cout << *vaca << endl;
                }
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
            }
            break;
        case 5: {
            system("cls");
            /* (2 puntos) Eliminación de vacas por ID */
            int idAEliminar;
            cout << "Ingrese el ID de la vaca que desea eliminar: ";
            cin >> idAEliminar;

            bool eliminadoArbol = arbolBinario.eliminar(Vaca(idAEliminar));
            const Vaca* vacaHash = hashTable.buscar(to_string(idAEliminar));
            if (vacaHash != nullptr) {
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
            /* (2 puntos) Verificar si el nodo mayor es múltiplo de 3 */
            arbolBinario.verificarMayorMultiploDe3();
            break;
        case 7:
            system("cls");
            /* Guardar datos en archivo */
            Archivos::escrituraDatosEnArchivo(vacas);
            break;
        case 8:
            system("cls");
            /* Leer datos de archivo */
            Archivos::lecturaDatosDeArchivo(arbolBinario, vacas);
            break;
        case 9:
            system("cls");
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opción no válida.\n";
            break;
        }
    } while (opcion != 9);

    return 0;
}
