#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "Secuencia.hpp"

using namespace std;

struct Arco
{
    pair<int, int> vertice1;
    pair<int, int> vertice2;
    float costo;
};

/// @brief
class Grafo
{
private:
    // (bases)

    vector<vector<char>> vertices; // vertices[x][y]
    // ((posicion1, posicion2), costo)
    vector<Arco> aristas;
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
