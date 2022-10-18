#include "Shell.hpp"
#include "Secuencia.cpp"
#include "ArbolHuffman.cpp"
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

/// @brief Se sale de la función en cualquier punto
void Shell::salir()
{
    exit(0);
}

void Shell::codificarSecuencua()
{
    list<Secuencia>::iterator it;
    map<char, int> mapaTemporalFrecuencias;
    map<char, string> mapaTemporalCodigos;
    ArbolHuffman *arbolTemporal = new ArbolHuffman();

    /* ofstream writer("Prueba.fabin", ios::out | ios::binary | ios::app);
    if (!writer)
    {
        cout << "Cannot open file!" << endl;
        return;
    } */

    // Vector de árboles

    vector<map<char, int>> vectorArboles;

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
            /* map<char, int>::iterator itmap;
            for (itmap = mapaTemporalFrecuencias.begin(); itmap != mapaTemporalFrecuencias.end(); itmap++)
            {
                cout << "|\t" << itmap->first << "\t|\t" << itmap->second << "\t|" << endl;
            } */

            mapaTemporalCodigos = arbol->GenerarCodigo(mapaTemporalFrecuencias);
            arbolTemporal = arbol->GenerarArbol(mapaTemporalFrecuencias);

            // El mapa queda codificado
            /* map<char, string>::iterator itmap2;
            for (itmap2 = mapaTemporalCodigos.begin(); itmap2 != mapaTemporalCodigos.end(); itmap2++)
            {
                cout << "|\t" << itmap2->first << "\t|\t" << itmap2->second << "\t|" << endl;
            } */
            string codigo = arbol->Codificar(it->ObtenerInformacionSec(), mapaTemporalCodigos);

            /* cout<<"Cantidad secuencias: " << secuencia->size() << endl;
            cout<<"Tamanio nombre: " << it->ObtenerDescripcion().size()-1 <<endl;
            cout<<"Nombre Secuencia: " << it->ObtenerDescripcion() <<endl;
            cout<<"Longitud Secuencia: "<< it->numeroBases()<<endl;
            cout<<"Indentación: "<< it->ObtenerTamanioIndentacion()<<endl;
            cout<<"Codigo: "<<codigo<<endl; */
            Codigo code;
            ofstream writer("Prueba.fabin", ios::out | ios::binary);
            if (!writer)
            {
                cout << "Cannot open file!" << endl;
                return;
            }
            // c->CantidadBases = it->numeroBases() numero total de bases cargadas en memoria función
            // c->m, hay que crear una función que me devuelva la totalidad de veces que se repite un elemento en todas las secuencias
            code.cantidadSecuencias = secuencia->size();
            code.tamanioNombre = it->ObtenerDescripcion().size() - 1;
            it->ObtenerDescripcion().copy(code.nombreSecuencia, it->ObtenerDescripcion().size() + 1);
            code.longitudSecuencia = it->numeroBases();
            code.indentacion = it->ObtenerTamanioIndentacion();
            codigo.copy(code.secuencia, codigo.size() + 1);

            writer.write((char *)&code, sizeof(code));
            writer.close();

            Codigo codigoLeido;

            ifstream f("Prueba.fabin", ios::binary);

            if (f.is_open())
            {
                f.read((char *)&codigoLeido, sizeof(Codigo));
                while (!f.eof())
                {
                

                    cout << "Cantidad secuencias: " << codigoLeido.cantidadSecuencias << endl;
                    cout << "Tamanio nombre: " << codigoLeido.tamanioNombre << endl;
                    cout << "Nombre Secuencia: " << codigoLeido.nombreSecuencia << endl;
                    cout << "Longitud Secuencia: " << codigoLeido.longitudSecuencia << endl;
                    cout << "Indentación: " << codigoLeido.indentacion << endl;
                    cout << "Codigo: " << codigoLeido.secuencia << endl;
                    f.read((char *)&codigoLeido, sizeof(Codigo));
                }
            }
            else
                cout << "Error de apertura de archivo." << endl;
            f.close();
        }
        
    }
}