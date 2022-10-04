#ifndef __SECUENCIA
#define __SECUENCIA

#include <iostream>
#include <vector>
#include <utility>
#include "Secuencia.hxx"

using namespace std;

typedef pair<char, int> par;
typedef vector<par> histograma;
typedef vector<char> vectorChar;
typedef vector<vectorChar> vVectorChar;

class Secuencia
{
private:
    string descripcion;
    vVectorChar informacionSecuencia;

public:
    // Constructores
    Secuencia();
    Secuencia(const string &Descripcion, const vVectorChar &InformacionSecuencia);
    Secuencia(const Secuencia &Secuencia);

    // Setters
    void InsertarDescripcion(const string &Descripcion);
    void InsertarInformacionSec(const vVectorChar &InformacionSecuencia);

    // Getters
    string ObtenerDescripcion() const;
    vVectorChar ObtenerInformacionSec() const;

    // Metodos
    void ImprimirSecuencia() const;
    histograma Histograma(const vectorChar &Datos) const;
    int Enmascarar(const string &Secuencia);
    int EsSubSecuencia(const string &Secuencia) const;

    // Eliminar Secuencia
    ~Secuencia();

protected:
    void CopiarSecuencia(Secuencia *&NuevaSecuencia) const;
};

#endif
