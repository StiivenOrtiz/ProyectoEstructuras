#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "Secuencia.hpp"
#include <iomanip>

using namespace std;

struct Arco
{
    pair<int, int> vertice1; // i, j
    pair<int, int> vertice2; // x, y
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
    string descripcion;

public:
    // Contructor
    Grafo(Secuencia secuencia);
    // Destructor
    ~Grafo();

    // Funciones de Grafo necesarias
    void desmarcarGrafo();
    void marcarVertice(int i, int j);
    void desmarcarVertice(int i, int j);
    bool marcadoVertice(int i, int j);
    float costoArco(int i, int j, int x, int y);
    pair<int, int> siguienteVertice(vector<vector<pair<pair<int, int>, float>>> costos);
    int validacion(pair<int, int> &v, vector<vector<pair<pair<int, int>, float>>> &costos);

    // Imprirmir grafo
    void imprimirGrafo();
    void imprimirVertices();
    void imprimirCostos(vector<vector<pair<pair<int, int>, float>>> &costos);
    void imprimirCaminos(vector<vector<pair<pair<int, int>, float>>> &costos);

    // Funciones claves
    vector<vector<pair<pair<int, int>, float>>> dijkstra(int i, int j);
    vector<pair<int, int>> posicionMismosVertices(int i, int j);
    bool baseRemota(int i, int j);
    void rutaMasCorta(int i, int j, int x, int y);
};
