#pragma once

#include "Secuencia.hpp"
#include "ArbolHuffman.hpp"
#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "CastBit.hpp"
#include "Grafo.hpp"

class Shell
{
private:
    string comando;
    list<Secuencia> *secuencia = new list<Secuencia>();
    ArbolHuffman *arbol = new ArbolHuffman();

public:
    // Contructor

    Shell();
    Shell(string comand);

    // Primera parte del proyecto
    void cargar(const string &ruta);
    void conteo();
    void listarSecuencias();
    void histograma(string descripcionSecuencia);
    int esSubsecuencia(string subsecuencia);
    void enmascarar(string subsecuencia);
    void guardar(const string &ruta);
    void salir();

    // Segunda parte del proyecto
    void codificarSecuencia(const string &ruta);
    void decodificarSecuencia(const string &ruta);
    int cantidadTotalBases();
    string frecuenciasTotalesString();
    map<char, long long int> frecuenciasTotalesMap();
    map<char, long long int> stringaMapa(string stringToMap);
    void comenzar();
    void insertarComando(string Comando);
    void evaluarComando();
    void ayuda();
    string obtenerCommando();

    // Tercera parte del proyecto
    void baseRemota(string descripcionSecuencia, int i, int j);
    void rutaMasCorta(string descripcionSecuencia, int i, int j, int x, int y);

    // Destructor
    ~Shell();

private:
    bool isNumber(const string &str)
    {
        for (char const &c : str)
        {
            if (std::isdigit(c) == 0)
                return false;
        }
        return true;
    }
};
