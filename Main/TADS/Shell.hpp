#pragma once

#include "Secuencia.hpp"
#include "ArbolHuffman.hpp"
#include "Codigo.hpp"

class Shell
{
private:
    string comando;
    list<Secuencia> *secuencia = new list<Secuencia>();
    ArbolHuffman *arbol = new ArbolHuffman();
    Codigo *c = new Codigo();

public:
    // Contructor

    Shell();
    Shell(string comand);

    // Primera parte del proyecto

    void cargar(const string &ruta);
    void conteo();
    void listar_Secuencias();
    void histograma(string descripcionSecuencia);
    int esSubsecuencia(string subsecuencia);
    void enmascarar(string subsecuencia);
    void guardar(const string &ruta);
    void salir();

    // Segunda parte del proyecto
    void codificarSecuencua(const string &ruta);
    void decodificarSecuencua(const string &ruta);
    int cantidadTotalBases();
    string frecuenciasTotales();


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

