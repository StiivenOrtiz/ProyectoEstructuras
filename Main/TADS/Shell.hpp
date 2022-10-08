#pragma once

#include "Secuencia.hpp"

class Shell
{
private:
    string comando;
    list<Secuencia> *secuencia = new list<Secuencia>();

public:
    // Contructor

    Shell();
    Shell(string comand);

    // Modificador
    
    /* int guardar(const string &NombreArchivo); */

    // Analizador

    void cargar(const string &ruta);
    void conteo();
    void listar_Secuencias();
    void histograma(string descripcionSecuencia);
    int esSubsecuencia(string subsecuencia);
    void enmascarar(string subsecuencia);
    void guardar(const string &ruta);
    void salir();


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

