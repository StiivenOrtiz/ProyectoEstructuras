#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "Secuencia.cpp"

using namespace std;

/// @brief
class Grafo
{
private:
    // (bases)
    vector<vector<char>> vertices;
    // ((posicion1, posicion2), costo)
    vector<pair<pair<pair<int, int>, pair<int, int>>, float>> aristas;
    unordered_map<string, bool> visitados;

public:
    // Contructor
    Grafo(Secuencia secuencia);
    // Destructor
    ~Grafo();

    // Funciones de Grafo necesarias
    int ordenGrafo();

    // Imprirmir grafo
    void imprimirGrafo();

    // Funciones claves
    void baseRemota();
    void rutaMasCorta();
};
