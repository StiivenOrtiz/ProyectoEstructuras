#pragma once
#include <map>
#include <string>

using namespace std;

class Codigo{
    public:
    /* int CantidadBases;
    map<char, int> m; */
    int cantidadSecuencias;
    int tamanioNombre;
    char nombreSecuencia[100];
    int longitudSecuencia;
    int indentacion;
    char secuencia[5000];
};