#include "Grafo.hpp"

/// @brief Constructor
/// @param secuencia
Grafo::Grafo(Secuencia secuencia)
{
    this->vertices.clear();
    this->aristas.clear();
    this->visitados.clear();

    this->vertices = secuencia.obtenerInformacionSec();

    for (int fila = 0; fila < this->vertices.size(); fila++)
    {
        for (int columna = 0; columna < this->vertices[fila].size(); columna++)
        {
            this->visitados[to_string(fila) + "," + to_string(columna)] = false;

            if ((columna - 1) != -1)
                this->aristas.push_back({{fila, columna}, {fila, columna - 1}, (float)((float)1 / ((float)1 + (float)(abs(this->vertices[fila][columna] - this->vertices[fila][columna - 1]))))});
            if ((fila - 1) != -1)
                this->aristas.push_back({{fila, columna}, {fila - 1, columna}, (float)((float)1 / ((float)1 + (float)(abs(this->vertices[fila][columna] - this->vertices[fila][columna - 1]))))});
        }
    }
}

/// @brief Destructor
Grafo::~Grafo()
{
    this->vertices.clear();
    this->aristas.clear();
    this->visitados.clear();
}

/// @brief
/// @return
int Grafo::ordenGrafo()
{
    return this->vertices.size();
}

/// @brief
void Grafo::imprimirGrafo()
{
    for (int i = 0; i < this->aristas.size(); i++)
    {
        cout << "Vertice 1: { x: " << aristas[i].vertice1.first << " y: " << aristas[i].vertice1.second << " } Vertice 2: { x: " << aristas[i].vertice2.first << " y: " << aristas[i].vertice2.second << " } Costo: " << aristas[i].costo << endl;
    }
}