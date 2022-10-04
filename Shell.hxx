#ifndef __SHELL
#define __SHELL

#include "Secuencia.hxx"
#include "Shell.cpp"
#include <fstream>
#include <string.h>

using namespace std;

class Shell
{
private:
    vector<Secuencia> secuencias;
    string comando;

public:
    // Contructor
    Shell();

    // Getters
    vector<Secuencia> ObtenerSecuencias() const;

    // Setters
    void InsertarSecuencias(const vector<Secuencia> &Secuencias);

    // Modificador
    void Cargar(const string &ruta);

    // Destructor
    ~Shell();
};

#endif
