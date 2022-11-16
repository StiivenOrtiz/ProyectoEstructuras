#include "Grafo.hpp"

Grafo::Grafo()
{
    this->grafo.clear();
}

Grafo::~Grafo()
{
    this->grafo.clear();
}

int Grafo::ordenGrafo()
{
    return this->grafo.size();
}