#include "Secuencia.hpp"
#include <unordered_map>

/* A comment. */
/// @brief Constructor de clase Secuencia sin parametros, inicializa descripción.
Secuencia::Secuencia()
{
}

/// @brief Constructor de Secuencia con parametros (Descripcion, Informacion de Secuencia).
/// @param Descripcion
/// @param InformacionSecuencia
Secuencia::Secuencia(string &Descripcion, vector<vector<char>> &InformacionSecuencia)
{
    descripcion = Descripcion;
    informacionSecuencia = InformacionSecuencia;
}

/// @brief Constructor de Secuencia con ayuda de otra secuencia, se copian la descripción y la información de secuencia.
/// @param Secuencia
Secuencia::Secuencia(const Secuencia &Secuencia)
{
    descripcion = Secuencia.descripcion;
    informacionSecuencia = Secuencia.informacionSecuencia;
}

/// @brief La descripción de la secuencia toma la descripción ingresada.
/// @param Descripcion
void Secuencia::insertarDescripcion(string &Descripcion)
{
    descripcion = Descripcion;
}

/// @brief Ingresar como parametros un vector de vector de char, (Informacion de secuencia), para finalmente insertarlo al vector de vector de char (Informacion de Secuencia) de la clase.
/// @param InformacionSecuencia
void Secuencia::insertarInformacionSec(vector<vector<char>> &InformacionSecuencia)
{
    informacionSecuencia = InformacionSecuencia;
}

/// @brief Encargada de retornar la descripción de la secuencia.
/// @return string
string Secuencia::obtenerDescripcion()
{
    return descripcion;
}

int Secuencia::obtenerTamanioIndentacion() const
{
    return informacionSecuencia[0].size();
}

/// @brief Encargada de obtener la información de la secuencia (vVectorChar o vector<vector<char>).
/// @return vVectorChar
vector<vector<char>> Secuencia::obtenerInformacionSec() const
{
    return informacionSecuencia;
}

/// @brief Metodo encargado de imprimir la secuencia.
void Secuencia::imprimirSecuencia() const
{
    int bases = 0;
    // Indica si el código está completo o no
    bool codigoCompleto = true;

    cout << "Secuencia " << descripcion.substr(1, (descripcion.size() - 1)) << endl;

    for (int i = 0; i < informacionSecuencia.size(); i++)
    {
        for (int j = 0; j < informacionSecuencia[i].size(); j++)
        {
            cout << informacionSecuencia[i][j];

            if (codigoCompleto && informacionSecuencia[i][j] == '-')
                codigoCompleto = false;
        }
        cout << endl;
        bases += informacionSecuencia[i].size();
    }

    if (codigoCompleto)
        cout << "contiene " << bases << " bases." << endl;
    else
        cout << "contiene al menos " << bases << " bases." << endl;
}

int Secuencia::numeroBases() const
{
    int bases = 0;

    for (int i = 0; i < informacionSecuencia.size(); i++)
    {
        bases += informacionSecuencia[i].size();
    }

    return bases;
}

/// @brief Metodo encargado de retornar el histograma de la secuencia.
/// @param Datos
/// @return
map<char, long long int> Secuencia::histograma() const
{
    map<char, long long int> histogramaFinal;

    for (int i = 0; i < formatoFasta.size(); i++)
    {
        histogramaFinal.insert(pair<char, long long int>(formatoFasta[i], 0));
    }

    for (int i = 0; i < informacionSecuencia.size(); i++)
    {
        for (int j = 0; j < informacionSecuencia[i].size(); j++)
        {
            histogramaFinal[informacionSecuencia[i][j]]++;
        }
    }

    return histogramaFinal;
}

/// @brief Imprime el histograma de secuencias, no gráfico
void Secuencia::imprimirHistograma() const
{
    map<char, long long int> histogramaFinal = histograma();

    cout << "\n---------------------------------\n";
    cout << "|    Codigo\t"
         << "|   Frecuencia\t|" << endl;
    cout << "---------------------------------\n";

    for (int i = 0; i < formatoFasta.size(); i++)
    {
        cout << "|\t" << formatoFasta[i] << "\t|\t" << histogramaFinal[formatoFasta[i]] << "\t|" << endl;
    }
    cout << "---------------------------------\n";
}

/// @brief Metodo encargado de retornar la cantidad de veces en las que esta secuencia dada se repite.
/// @param Secuencia
/// @return
int Secuencia::esSubSecuencia(const string &Secuencia) const
{
    int vecesRepetida = 0;
    int posicion = 0;
    int indice = 0;
    string strxlinea = "";

    // Convierto cada línea en un string
    for (int i = 0; i < informacionSecuencia.size(); i++)
    {
        for (int j = 0; j < informacionSecuencia[i].size(); j++)
        {
            strxlinea += informacionSecuencia[i][j];
        }
        // cout<<"Linea "<<i<<": ";
        // cout<<strxlinea<<endl;
        while ((indice = strxlinea.find(Secuencia, posicion)) != string::npos)
        {
            vecesRepetida++;
            // cout<<" Substring encontrado en la posicion "<<indice<<endl;
            // cout<<"En la posicion: "<<i<<" "<<indice<<"esta el código: "<<informacionSecuencia[i][indice]<<endl;
            posicion = indice + 1;
        }
        posicion = 0;
        indice = 0;
        strxlinea = "";
    }

    return vecesRepetida;
}

/// @brief Pone 'x' sobre los códigos equivalentes al string de parámetro que sean substrings del código completo
/// @param Secuencia
void Secuencia::enmascarar(const string &subSecuencia)
{

    int posicion = 0;
    int indice = 0;
    string strxlinea = "";

    // Convierto cada línea en un string
    for (int i = 0; i < informacionSecuencia.size(); i++)
    {
        for (int j = 0; j < informacionSecuencia[i].size(); j++)
        {
            strxlinea += informacionSecuencia[i][j];
        }

        while ((indice = strxlinea.find(subSecuencia, posicion)) != string::npos)
        {
            // Al encontrar la posición en la que está el substring, ubico la nueva variable
            for (int k = 0; k < subSecuencia.size(); k++)
            {
                informacionSecuencia[i][indice + k] = 'X';
            }
            posicion = indice + 1;
        }

        posicion = 0;
        indice = 0;
        strxlinea = "";
    }
}

/**
 * @brief Metodo encargado de hacer una copia de la secuencia actual a una nueva.
 *
 * @param NuevaSecuencia
 */
/* void Secuencia::CopiarSecuencia(Secuencia *&NuevaSecuencia) const
{
    if (this != NULL)
    {
        NuevaSecuencia = new Secuencia(*this);
    }
} */

/// @brief Destruye el objeto de Secuencia
Secuencia::~Secuencia()
{
    if (this != NULL)
    {
        informacionSecuencia = {};
        descripcion = "";
    }
}