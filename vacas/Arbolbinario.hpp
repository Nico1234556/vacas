#ifndef __ARBOLB_HPP__
#define __ARBOLB_HPP__

#include <iostream>
#include <vector>
#include <algorithm>
#include "Vaca.h"

template <class T>
class Nodo {
public:
    T elemento;
    Nodo* izq;
    Nodo* der;

    Nodo(const T& elem) : elemento(elem), izq(nullptr), der(nullptr) {}
};

template <class T>
class ArbolB {
    Nodo<T>* raiz;

public:
    ArbolB() : raiz(nullptr) {}

    bool insertar(const T& e) {
        return _insertar(raiz, e);
    }

    void enOrden() {
        _enOrden(raiz);
    }

    T* buscar(const T& e) {
        return _buscar(raiz, e);
    }

    bool eliminar(const T& e) {
        bool eliminado = false;
        raiz = _eliminar(raiz, e, eliminado);
        return eliminado;
    }

    void verificarMayorMultiploDe3() {
        if (raiz == nullptr) {
            cout << "El árbol está vacío." << endl;
            return;
        }
        Nodo<T>* mayorNodo = encontrarMayor(raiz);
        if (mayorNodo->elemento.edad %3 == 0) {
            cout << "El elemento del nodo mayor (" << mayorNodo->elemento.edad << ") es múltiplo de 3." << endl;
        }
        else {
            cout << "El elemento del nodo mayor (" << mayorNodo->elemento.edad << ") no es múltiplo de 3." << endl;
        }
    }

    bool esPrimo(int n) const {
        if (n <= 1) return false;
        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

private:
    bool _insertar(Nodo<T>*& nodo, const T& e) {
        if (nodo == nullptr) {
            nodo = new Nodo<T>(e);
            return true;
        }
        if (e < nodo->elemento) {
            return _insertar(nodo->izq, e);
        }
        else {
            return _insertar(nodo->der, e);
        }
    }

    void _enOrden(Nodo<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        std::cout << nodo->elemento << " ";
        _enOrden(nodo->der);
    }

    T* _buscar(Nodo<T>* nodo, const T& e) {
        if (nodo == nullptr) return nullptr;
        if (e == nodo->elemento) return &nodo->elemento;
        if (e < nodo->elemento) return _buscar(nodo->izq, e);
        return _buscar(nodo->der, e);
    }

    Nodo<T>* _eliminar(Nodo<T>* nodo, const T& e, bool& eliminado) {
        if (nodo == nullptr) return nodo;
        if (e < nodo->elemento) {
            nodo->izq = _eliminar(nodo->izq, e, eliminado);
        }
        else if (e > nodo->elemento) {
            nodo->der = _eliminar(nodo->der, e, eliminado);
        }
        else {
            eliminado = true;
            if (nodo->izq == nullptr) {
                Nodo<T>* temp = nodo->der;
                if (esPrimo(nodo->elemento.edad)) {
                    cout << "El número eliminado (" << nodo->elemento.edad << ") es primo." << endl;
                }
                delete nodo;
                return temp;
            }
            else if (nodo->der == nullptr) {
                Nodo<T>* temp = nodo->izq;
                if (esPrimo(nodo->elemento.edad)) {
                    cout << "El número eliminado (" << nodo->elemento.edad << ") es primo." << endl;
                }
                delete nodo;
                return temp;
            }

            Nodo<T>* temp = encontrarMayor(nodo->izq);
            nodo->elemento = temp->elemento;
            nodo->izq = _eliminar(nodo->izq, temp->elemento, eliminado);
        }
        return nodo;
    }

    Nodo<T>* encontrarMayor(Nodo<T>* nodo) {
        while (nodo->der != nullptr) {
            nodo = nodo->der;
        }
        return nodo;
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
};

#endif // __ARBOLB_HPP__
