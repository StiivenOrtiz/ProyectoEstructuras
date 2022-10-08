#include "Shell.hpp"
#include "Secuencia.cpp"
#include <iterator>
#include <fstream>

// Constructores

Shell::Shell()
{
    comando = "";
}

Shell::Shell(string comand)
{
    comando = comand;
}

/* Modificadores */

/// @brief Esta función permite cargar un archivo ".fa" a la memoria del computador, funciona con vectores y es compatible con la sección de grafos
/// @param ruta
void Shell::cargar(const string &ruta)
{
    secuencia->clear();
    try
    {
        ifstream miRuta(ruta);
        string linea = "";

        Secuencia *secuenciaTemp = new Secuencia();
        vector<char> vectorTemporal;
        vector<vector<char>> matrizTemporal;

        int contador = 0;
        int fila = 0;

        // Línea para indicar si el archivo está vacío

        if (miRuta.peek() == ifstream::traits_type::eof())
        {
            cout << ruta << "El archivo esta vacio" << endl;
        }
        else
        {
            /**
             * @brief Con esta línea se pretende ignorar a la primera del archivo
             * así, sólo en este caso se trabaja con la columna 0.
             *
             */
            getline(miRuta, linea);
            secuenciaTemp->InsertarDescripcion(linea);

            contador++;

            while (getline(miRuta, linea))
            {
                /* Si la linea inicia una secuencia, describo el nombre de la secuencia en un nuevo iterador*/
                if (linea[0] == '>')
                {
                    secuenciaTemp->InsertarInformacionSec(matrizTemporal);
                    this->secuencia->push_back(*secuenciaTemp);
                    // secuenciaTemp->ImprimirSecuencia();
                    secuenciaTemp->InsertarDescripcion(linea);
                    matrizTemporal.clear();
                    vectorTemporal.clear();
                    contador++;
                }
                else
                {
                    copy(linea.begin(), linea.end(), back_inserter(vectorTemporal));
                    matrizTemporal.push_back(vectorTemporal);
                    vectorTemporal.clear();

                    // cout << linea << endl;
                    contador++;
                }
            }
            /**
             * al igual que antes de iniciar, una vez terminado el proceso, se realiza la inserción
             * para los elementos de la última línea
             *
             */
            secuenciaTemp->InsertarInformacionSec(matrizTemporal);
            this->secuencia->push_back(*secuenciaTemp);
            // secuenciaTemp->ImprimirSecuencia();
        }

        if (secuencia->size() == 1)
        {
            cout << "1 secuencia a cargada correctamente desde " << ruta << endl;
        }
        else if (secuencia->size() > 1)
        {
            cout << "Han sido cargadas " << secuencia->size() << " lineas desde " << ruta << endl;
        }
    }
    catch (const exception &e)
    {
        cout << ruta << "No se encuentra o no puede leerse." << endl;
    }
}

/// @brief Esta función indica el número de secuencias cargadas en memoria.
void Shell::conteo()
{
    if (secuencia->size() == 0)
    {
        cout << "No hay secuencias cargadas en memoria.\n";
    }
    else
    {
        cout << "Hay " << this->secuencia->size() << " Secuencias cargadas en memoria.\n";
    }
}

/// @brief Esta función, muestra en la interfaz de comandos, la información de las secuencias e indica la cantidad de bases.
void Shell::listar_Secuencias()
{

    list<Secuencia>::iterator it;

    if (secuencia->size() == 0)
    {
        cout << "No hay secuencias cargadas en memoria.\n";
    }
    else
    {
        for (it = secuencia->begin(); it != secuencia->end(); it++)
        {
            it->ImprimirSecuencia();
            cout << endl;
        }
    }
}

/// @brief Esta función, aunque no imprime como tal un histograma gráfico, si muestra su tabla, dando código y frecuencia.
/// @param descripcionSecuencia
void Shell::histograma(string descripcionSecuencia)
{
    list<Secuencia>::iterator it;
    bool flagExistencia = false;
    string aux = ">" + descripcionSecuencia;

    if (secuencia->size() == 0)
    {
        cout << "No hay secuencias cargadas en memoria.\n";
    }
    else
    {
        for (it = secuencia->begin(); it != secuencia->end(); it++)
        {
            if (it->ObtenerDescripcion() == aux)
            {
                it->imprimirHistograma();
                flagExistencia = true;
                break;
            }
        }
        if (!flagExistencia)
        {
            cout << "Secuencia invalida" << endl;
        }
    }
}

/// @brief Indica si una secuencia dada por el usuario, es subsecuencia de las secuencias cargadas en memoria, en caso de que así sea, indica cuantas veces está la subsecuencia dentro de las secuencias cargadas
/// @param esSubsecuencia
/// @return
int Shell::esSubsecuencia(string esSubsecuencia)
{

    list<Secuencia>::iterator it;
    int secuenciaRepetida = 0;

    if (secuencia->size() == 0)
    {
        cout << "No hay secuencias cargadas en memoria.\n";
    }
    else
    {
        for (it = secuencia->begin(); it != secuencia->end(); it++)
        {
            secuenciaRepetida += it->EsSubSecuencia(esSubsecuencia);
        }
    }
    if (secuenciaRepetida == 0)
    {
        cout << "La secuencia dada, no existe\n";
        return secuenciaRepetida;
    }
    else
    {
        cout << "La secuencia dada, se repite: " << secuenciaRepetida << " veces.\n";
        return secuenciaRepetida;
    }
}

/// @brief Dada una secuancia, esta función indica si esta es subsecuencia, de la secuencia principal, y enmascara en la secuencia principal con 'X' los valores que sean subsecuencias de la secuencia principal
/// @param subsecuencia
void Shell::enmascarar(string subsecuencia)
{

    list<Secuencia>::iterator it;
    int secuenciaRepetida = 0;

    if (secuencia->size() == 0)
    {
        cout << "No hay secuencias cargadas en memoria.\n";
    }
    else
    {
        // Enmascara en relación a la cantidad de elementos que componen la subsecuencia
        for (it = secuencia->begin(); it != secuencia->end(); it++)
        {
            secuenciaRepetida += it->EsSubSecuencia(subsecuencia);
            it->Enmascarar(subsecuencia);
        }
    }
    if (secuenciaRepetida == 0)
    {
        cout << "La secuencia dada, no existe, por tanto no se enmascara nada\n";
    }
    else
    {
        cout << secuenciaRepetida << " secuencia(s) ha(n) sido enmascarada(s).\n";
    }
}

/// @brief Genera un archivo .fa, con las secuencias modificadas.
/// @param ruta
void Shell::guardar(const string &ruta)
{

    list<Secuencia>::iterator it;
    ofstream salida;
    salida.open(ruta);
    string strxlinea = "";

    if (secuencia->size() == 0)
    {
        cout << "No hay secuencias cargadas en memoria.\n";
    }
    else
    {
        for (it = secuencia->begin(); it != secuencia->end(); it++)
        {
            salida << it->ObtenerDescripcion() << endl;
            vector<vector<char>> vectortemporal = it->ObtenerInformacionSec();

            for (int i = 0; i < vectortemporal.size(); i++)
            {
                for (int j = 0; j < vectortemporal[i].size(); j++)
                {
                    strxlinea += vectortemporal[i][j];
                }
                salida << strxlinea << endl;
                strxlinea = "";
            }
        }
        salida.close();
    }
}

/// @brief Se sale de la función en cualquier punto
string Shell::salir()
{
    comando = "salir";
}

/// @brief Encargado de desplegar los comandos con los que se puede usar la shell.
void Shell::ayuda()
{
    cout << "---------------------------------| C O M A N D O S |---------------------------------" << endl;
    cout << ">cargar [nombre_archivo]:\nCarga en memoria los datos contenidos en el archivo identificado por nombre_archivo.\n"
         << endl;
    cout << ">conteo:\nImprime por pantalla la cantidad de secuencias cargadas en memoria.\n"
         << endl;
    cout << ">listar_secuencias:\nImprime en n lineas la informacion basica de cada secuencia.\n"
         << endl;
    cout << ">histograma [descripcion_secuencia]:\nImprime el histograma de una secuencia, en caso de que exista.\n"
         << endl;
    cout << ">es_subsecuencia [secuencia]:\nDetermina si una secuencia dada, existe dentro de las secuencias cargadas.\n"
         << endl;
    cout << ">enmascarar [secuencia]:\nEnmascara una secuencia dada por el usuario, si existe.\n"
         << endl;
    cout << ">guardar [nombre_archivo]:\nGuarda en el archivo nombre_archivo las secuencias cargadas en memoria.\n"
         << endl;
    cout << ">codificar [nombre_archivo.fabin]:\nGenera un archivo .fabin con la codificacion de Huffman almacenandolo en disco.\n"
         << endl;
    cout << ">decodificar [nombre_archivo.fabin]:\nCarga en memoria las secuencias codificadas en Huffman dentro en un archivo .fabin.\n"
         << endl;
    cout << ">ruta_mas_corta [descripcion_secuencia i j x y]:\nImprime la secuencia de vertices del grafo que describen la ruta mas corta entre\n";
    cout << "la base de la posicion [i, j] y la base de la posicion [x, y]. Tambien imprime el\n";
    cout << "costo total de la ruta.\n"
         << endl;
    cout << ">base_remota [descripcion_secuencia i j]:\nPara la base de la posicion [i, j] de la matriz de la secuencia busca la ubicacion,\n";
    cout << "de la misma base (misma letra) mas lejana dentro de la matriz. Para esta base\n";
    cout << "remota, imprime su ubicacion, la secuencia de vertices que describen la ruta\n";
    cout << "entre la base origen y la base remota, y el costo total de la ruta, teniendo\n";
    cout << "en cuenta el peso que tiene cada conexion entre bases.\n"
         << endl;
    cout << ">salir:\nCierra el programa.\n";
}

/// @brief Encargado de dar el string que es contenido en el comando.
/// @return string
string Shell::obtenerCommando()
{
    return comando;
}

/// @brief
/// @param Comando
void Shell::insertarComando(string Comando)
{
    comando = Comando;
}

/// @brief Inicia a correr el shell.
void Shell::comenzar()
{
    string opcion;
    do
    {
        cout << "$ ";
        getline(cin, opcion);
        insertarComando(opcion);
        evaluarComando();
    } while (obtenerCommando() != "salir");
}

/// @brief Se encarga de determinar y ejecutar las funciones.
void Shell::evaluarComando()
{
    vector<string> entrada;

    string aux;
    string::iterator it;

    for (it = comando.begin(); it != comando.end(); it++)
    {
        if ((*it == ' ') || (it == comando.end()--))
        {
            entrada.push_back(aux);
            aux.clear();
        }
        else
        {
            aux = aux + *it;
        }
    }

    entrada.push_back(aux);

    if (entrada[0] != "")
    {
        if (entrada[0] == "cargar")
        {
            if (entrada.size() == 2)
            {
                cargar(entrada[1]);
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico el archivo .fa." << endl;
        }
        else if (entrada[0] == "conteo")
        {
            conteo();
            insertarComando(entrada[0]);
        }
        else if (entrada[0] == "listar_secuencias")
        {
            listar_Secuencias();
            insertarComando(entrada[0]);
        }
        else if (entrada[0] == "histograma")
        {
            if (entrada.size() == 2)
            {
                histograma(entrada[1]);
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico la secuencia." << endl;
        }
        else if (entrada[0] == "es_subsecuencia")
        {
            if (entrada.size() == 2)
            {
                esSubsecuencia(entrada[1]);
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico la subsecuencia." << endl;
        }
        else if (entrada[0] == "enmascarar")
        {
            if (entrada.size() == 2)
            {
                enmascarar(entrada[1]);
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico la secuencia." << endl;
        }
        else if (entrada[0] == "guardar")
        {
            if (entrada.size() == 2)
            {
                guardar(entrada[1]);
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico el archivo." << endl;
        }
        else if (entrada[0] == "codificar")
        {
            if (entrada.size() == 2)
            {
                cout << "En construccion";
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico el archivo." << endl;
        }
        else if (entrada[0] == "decodificar")
        {
            if (entrada.size() == 2)
            {
                cout << "En construccion" << endl;
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico el archivo." << endl;
        }
        else if (entrada[0] == "ruta_mas_corta")
        {
            if (entrada.size() == 6)
            {
                cout << "En construccion" << endl;
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico el archivo." << endl;
        }
        else if (entrada[0] == "base_remota")
        {
            if (entrada.size() == 4)
            {
                cout << "En construccion" << endl;
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico el archivo." << endl;
        }
        else if (entrada[0] == "salir")
        {
            salir();
        }
        else if (entrada[0] == "ayuda")
        {
            ayuda();
        }
        else if (entrada[0] == "clear")
        {
            system("CLS");
        }
        else
        {
            cout << "Comando inexistente." << endl;
        }
        cout << endl;
    }
}