#include "Secuencia.hxx"

//
// S e c u e n c i a : : S e c u e n c i a
//
// Parametros: N/A
//
// Constructor de clase Secuencia sin parametros, inicializa descripción.
//
Secuencia::Secuencia()
{
    descripcion = "";
}

//
// S e c u e n c i a : : S e c u e n c i a
//
// Parametros: Descripcion (string), vVectorChar (vector<vector<char>>) Informacion de la secuencia
//
// Constructor de Secuencia con parametros (Descripcion, Informacion de Secuencia).
//
Secuencia::Secuencia(const string &Descripcion, const vVectorChar &InformacionSecuencia)
{
    descripcion = Descripcion;
    informacionSecuencia = InformacionSecuencia;
}

//
// S e c u e n c i a : : S e c u e n c i a
//
// Parametros: Secuencia (Secuencia)
//
// Constructor de Secuencia con ayuda de otra secuencia, se copian la descripción y la información de secuencia.
//
Secuencia::Secuencia(const Secuencia &Secuencia)
{
    descripcion = Secuencia.descripcion;
    informacionSecuencia = Secuencia.informacionSecuencia;
}

//
// v o i d
// S e c u e n c i a : : I n s e r t a r D e s c r i p c i o n
//
// Parametros: Descripción (string)
//
// La descripción de la secuencia toma la descripción ingresada.
//
void Secuencia::InsertarDescripcion(const string &Descripcion)
{
    descripcion = Descripcion;
}

//
// v o i d
// S e c u e n c i a : : I n s e r t a r I n f o r m a c i o n S e c
//
// Parametros: Informacion de Secuencia (vector<vector<char>> vVectorChar)
//
// Ingresar como parametros un vector de vector de char
// (Informacion de secuencia), para finalmente insertarlo
// al vector de vector de char (Informacion de Secuencia) de la clase.
//
void Secuencia::InsertarInformacionSec(const vVectorChar &InformacionSecuencia)
{
    informacionSecuencia = InformacionSecuencia;
}

//
// s t r i n g
// S e c u e n c i a : : O b t e n e r D e s c r i p c i o n
//
// Parametros: N/A
//
// Encargada de retornar la descripción de la secuencia.
//
string Secuencia::ObtenerDescripcion() const
{
    return descripcion;
}

//
// v V e c t o r C h a r
// S e c u e n c i a : : O b t e n e r I n f o r m a c i o n S e c
//
// Parametros: N/A
//
// Encargada de obtener la información de la secuencia (vVectorChar o vector<vector<char>).
//
vVectorChar Secuencia::ObtenerInformacionSec() const
{
    return informacionSecuencia;
}

//
// v o i d
// S e c u e n c i a : : I m p r i m i r S e c u e n c i a
//
// Parametros: N/A
//
// Metodo encargado de imprimir la secuencia.
//
void Secuencia::ImprimirSecuencia() const
{
    int bases = 0;
    bool codigoCompleto = true;

    cout << ">" << descripcion << endl;

    for (int i = 0; i < informacionSecuencia.size(); i++)
    {
        for (int j = 0; j < informacionSecuencia[i].size(); j++)
        {
            cout << informacionSecuencia[i][j];

            if (codigoCompleto && informacionSecuencia[i][j] == '-')
            {
                codigoCompleto = false;
            }

            bases++;
        }
        cout << endl;
    }

    if (codigoCompleto)
    {
        cout << "Secuencia  >" << descripcion << " contiene " << bases << " bases." << endl;
    }
    else
    {
        cout << "Secuencia  >" << descripcion << " contiene al menos" << bases << " bases." << endl;
    }
}

//
// h i s t o g r a m a (vector<pair<char, int>>)
// S e c u e n c i a : : H i s t o g r a m a
//
// Parametros: vectorChar (vector<char>)
//
// Metodo encargado de retornar el histograma de la secuencia.
//
histograma Secuencia::Histograma(const vectorChar &Datos) const
{
    histograma histogramaFinal;
    par auxiliar;
    auxiliar.second = 0;

    for (int i = 0; i < Datos.size(); i++)
    {
        auxiliar.first = Datos[i];
        histogramaFinal.push_back(auxiliar);
    }

    for (int i = 0; i < informacionSecuencia.size(); i++)
    {
        for (int j = 0; j < informacionSecuencia[i].size(); j++)
        {
            int iterador = 0;

            while ((informacionSecuencia[i][j] != histogramaFinal[iterador].first) && (iterador != histogramaFinal.size()))
            {
                iterador++;
            }

            if (iterador != histogramaFinal.size() || iterador > histogramaFinal.size())
            {
                histogramaFinal[iterador].second = histogramaFinal[iterador].second + 1;
            }
        }
    }

    return histogramaFinal;
}

//
// i n t
// S e c u e n c i a : : E n m a s c a r a r
//
// Parametros: vectorChar (vector<char>)
//
// Metodo encargado de retornar el histograma de la secuencia.
//
int Secuencia::Enmascarar(const string &Secuencia)
{
    // Opcional
}

//
// i n t
// S e c u e n c i a : : E n m a s c a r a r
//
// Parametros: N/A
//
// Metodo encargado de retornar la cantidad de veces en las que esta secuencia dada se repite.
//
int Secuencia::EsSubSecuencia(const string &Secuencia) const
{

    vector<string> vString;

    for (int i = 0; i < informacionSecuencia.size(); i++)
    {
        string linea = "";

        for (int j = 0; j < informacionSecuencia[i].size(); j++)
        {
            linea = linea + informacionSecuencia[i][j];
        }

        vString.push_back(linea);
    }

    size_t Coincidencias;
    int contador = 0;

    for (int i = 0; i < vString.size(); i++)
    {
        Coincidencias = vString[i].find(Secuencia);

        while (Coincidencias != string::npos)
        {
            contador++;
            Coincidencias = vString[i].find(Secuencia, Coincidencias + Secuencia.size());
        }
    }

    return Coincidencias;
}

//
// v o i d
// S e c u e n c i a : : C o p i a r S e c u e n c i a
//
// Parametros: NuevaSecuencia (Secuencia)
//
// Metodo encargado de hacer una copia de la secuencia actual a una nueva.
//
void Secuencia::CopiarSecuencia(Secuencia *&NuevaSecuencia) const
{
    if (this != NULL)
    {
        NuevaSecuencia = new Secuencia(*this);
    }
}

//
// S e c u e n c i a : : ~S e c u e n c i a
//
// Parametros: Secuencia a destruir
//
// Destructor de Secuencia.
//
Secuencia::~Secuencia()
{
    if (this != NULL)
    {
        delete this;
    }
}