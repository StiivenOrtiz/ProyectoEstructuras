#include "Shell.hpp"
#include "Secuencia.cpp"
#include "ArbolHuffman.cpp"
#include <iterator>
#include <numeric>
#include <fstream>
#include <string>

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
            cout << "El archivo esta vacio" << endl;
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

        cout << "Han sido cargadas: " << contador << " lineas desde: " << ruta << endl;
    }
    catch (const exception &e)
    {
        cout << "No se pudo encontrar el archivo o leerse" << endl;
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
            cout << "Secuencia inválida" << endl;
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

int Shell::cantidadTotalBases()
{

    list<Secuencia>::iterator it;
    int acumulador;

    for (it = secuencia->begin(); it != secuencia->end(); it++)
    {
        acumulador += it->numeroBases();
    }
    return acumulador;
}

string Shell::frecuenciasTotales()
{

    map<char, int> mapaTemporalAcumulado;
    map<char, int> mapaTemporal;

    //----------------------------------------------------------------

    list<Secuencia>::iterator it = secuencia->begin();
    map<char, int>::iterator mapit;
    string str = "[";
    string str1 = "";
    string str2 = "";
    string str3 = "";

    mapaTemporalAcumulado = it->Histograma();

    for (it = next(it, 1); it != secuencia->end(); it++)
    {
        str3 = "";
        mapaTemporal = it->Histograma();
        for (mapit = mapaTemporal.begin(); mapit != mapaTemporal.end(); mapit++)
        {
            mapaTemporalAcumulado[mapit->first] = mapaTemporalAcumulado[mapit->first] + mapit->second;

            str1 = mapit->first;
            str2 = to_string(mapaTemporalAcumulado[mapit->first]) + "]";
            str3 += str + str1 + "," + str2;
        }
    }
    return str3;
}

void Shell::codificarSecuencua(const string &ruta)
{
    list<Secuencia>::iterator it;
    map<char, int> mapaTemporalFrecuencias;
    map<char, string> mapaTemporalCodigos;
    ArbolHuffman *arbolTemporal = new ArbolHuffman();

    // Reinicia el archivo y escribe el primer elemento
    ofstream writer(ruta, ios::out | ios::binary);
    if (!writer)
    {
        cout << "No es posible abrir el archivo" << endl;
        return;
    }

    int cantidadSecuencias = secuencia->size();
    int cantidadTotalBases = this->cantidadTotalBases();
    string mapas = this->frecuenciasTotales();
    char arraychar[mapas.size() + 1];
    strcpy(arraychar, mapas.c_str());

    writer.write((char *)&cantidadTotalBases, sizeof(cantidadTotalBases));
    writer.write((char *)&arraychar, sizeof(arraychar));
    writer.write((char *)&cantidadSecuencias, sizeof(cantidadSecuencias));
    writer.close();

    if (secuencia->size() == 0)
    {
        cout << "No hay secuencias cargadas en memoria.\n";
    }
    else
    {
        // Toma el histograma de cada secuencia en particular
        for (it = secuencia->begin(); it != secuencia->end(); it++)
        {
            mapaTemporalFrecuencias = it->Histograma();

            mapaTemporalCodigos = arbol->GenerarCodigo(mapaTemporalFrecuencias);
            arbolTemporal = arbol->GenerarArbol(mapaTemporalFrecuencias);

            // El mapa queda codificado

            string codigo = arbol->Codificar(it->ObtenerInformacionSec(), mapaTemporalCodigos);

            Codigo code;
            ofstream writer(ruta, ios::out | ios::binary | ios::app);
            if (!writer)
            {
                cout << "No es posible abrir el archivo" << endl;
                return;
            }

            int n = it->ObtenerDescripcion().size();

            strcpy(code.nombreSecuencia, it->ObtenerDescripcion().c_str());
            code.longitudSecuencia = it->numeroBases();
            code.indentacion = it->ObtenerTamanioIndentacion();
            strcpy(code.secuencia, codigo.c_str());
            writer.write((char *)&code, sizeof(code));
            writer.close();
        }
    }
}

void Shell::decodificarSecuencua(const string &ruta)
{

    string mapss = this->frecuenciasTotales();
    char arraycharlectura[mapss.size() + 1];
    Codigo codigoLeido;
    int prueba;
    int basesTotales;

    // Variables para decodificar

    list<Secuencia>::iterator it;
    map<char, int> mapaTemporalFrecuencias;
    map<char, string> mapaTemporalCodigos;
    ArbolHuffman *arbolTemporal = new ArbolHuffman();

    ifstream f(ruta, ios::binary);

    if (f.is_open())
    {
        cout<<"\n\n------------------------------------------------------------------------------------------------\n\n";
        
        f.read((char *)&basesTotales, sizeof(int));
        cout << "Cantidad total Bases: " << basesTotales << endl;

        f.read((char *)&arraycharlectura, sizeof(arraycharlectura));
        cout << "Bases y frecuencias: " << arraycharlectura << endl;

        f.read((char *)&prueba, sizeof(int));
        cout << "Cantidad Secuencias: " << prueba << endl;

        f.read((char *)&codigoLeido, sizeof(Codigo));

        // Para decondificar tengo que generar el arbol de cada secuencia
        it = secuencia->begin();

        while (!f.eof())
        {
            cout<<"\n\n------------------------------------------------------------------------------------------------\n\n";
            cout << "Nombre Secuencia: " << codigoLeido.nombreSecuencia << endl;
            cout << "Longitud Secuencia: " << codigoLeido.longitudSecuencia << endl;
            cout << "Indentación: " << codigoLeido.indentacion << endl;
            cout << "\nCodigo: \n" << codigoLeido.secuencia << endl;

            mapaTemporalFrecuencias = it->Histograma();
            mapaTemporalCodigos = arbol->GenerarCodigo(mapaTemporalFrecuencias);
            arbolTemporal = arbol->GenerarArbol(mapaTemporalFrecuencias);

            string decode = arbol->deCodificar(arbolTemporal, codigoLeido.secuencia);
            cout << "\ndecodificado: ";
            for (int i = 0; i < decode.size(); i++)
            {
                if(i % codigoLeido.indentacion == 0){
                    cout<<endl;
                }
                cout <<decode[i];

            }
            cout<<"\n\n------------------------------------------------------------------------------------------------\n\n";
            it++;
            f.read((char *)&codigoLeido, sizeof(Codigo));
        }
    }
    else
        cout << "No se pueden cargar las secuencias en -agregar nomarchivo-." << endl;
    f.close();
}

/// @brief Se sale de la función en cualquier punto
void Shell::salir()
{
    exit(0);
}