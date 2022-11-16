#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <string.h>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <iterator>
#include <unordered_map>

using namespace std;

class Secuencia
{
private:
    string descripcion;
    vector<vector<char>> informacionSecuencia;
    vector<char> formatoFasta = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M',
                                 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};

public:
    // Constructores
    Secuencia();
    Secuencia(string &Descripcion, vector<vector<char>> &InformacionSecuencia);
    Secuencia(const Secuencia &Secuencia);

    // Setters
    void insertarDescripcion(string &Descripcion);
    void insertarInformacionSec(vector<vector<char>> &InformacionSecuencia);

    // Getters
    string obtenerDescripcion();
    vector<vector<char>> obtenerInformacionSec() const;
    int numeroBases() const;
    int obtenerTamanioIndentacion() const;

    // Metodos
    void imprimirSecuencia() const;
    map<char, long long int> histograma() const;
    void imprimirHistograma() const;
    void enmascarar(const string &subSecuencia);
    int esSubSecuencia(const string &Secuencia) const;

    // Eliminar Secuencia
    ~Secuencia();

    /* void CopiarSecuencia(Secuencia *&NuevaSecuencia) const; */
};