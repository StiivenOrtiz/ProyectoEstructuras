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
                this->aristas.push_back({{{fila, columna}, {fila, columna - 1}}, (1 / (1 + (abs(this->vertices[fila][columna] - this->vertices[fila][columna - 1]))))});

            if ((fila - 1) != -1)
                this->aristas.push_back({{{fila, columna}, {fila - 1, columna - 1}}, (1 / (1 + (abs(this->vertices[fila][columna] - this->vertices[fila - 1][columna]))))});
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
    }
}