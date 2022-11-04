#pragma once

#include "Secuencia.hpp"
<<<<<<< Updated upstream
=======
#include "ArbolHuffman.hpp"
#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "CastBit.hpp"
>>>>>>> Stashed changes

class Shell
{
private:
    string comando;
    list<Secuencia> *secuencia = new list<Secuencia>();
<<<<<<< Updated upstream
=======
    ArbolHuffman *arbol = new ArbolHuffman();
>>>>>>> Stashed changes

public:
    // Contructor

    Shell();
    Shell(string comand);

    // Modificador

    /* int guardar(const string &NombreArchivo); */

    // Analizador

    void cargar(const string &ruta);
    void conteo();
    void listarSecuencias();
    void histograma(string descripcionSecuencia);
    int esSubsecuencia(string subsecuencia);
    void enmascarar(string subsecuencia);
    void guardar(const string &ruta);
<<<<<<< Updated upstream
    string obtenerCommando();
    void insertarComando(string Comando);
    string salir();
    void ayuda();
    void comenzar();
    void evaluarComando();
=======
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
>>>>>>> Stashed changes

    /* void listar_Secuencias();
    void enmascarar(string secuencia);
    bool codificar(string nombreArchivo);
    int esSubsecuencia(string subsecuencia);
    void decodificar(string nombreArchivo);
    vector<map<char,int>> histograma(string descripcionSecuencia);
    void baseRemota(string descripcionSecuencia, vector<char> letras);
    void rutaMasCorta(string descripcionSecuencia, vector<char> letras); */

    // Destructor
    ~Shell();
};
