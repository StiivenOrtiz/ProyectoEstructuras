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
        this->secuencia->clear();
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
            cout << ruta << " no contiene ninguna secuencia." << endl;
        }
        else
        {
            /**
             * @brief Con esta línea se pretende ignorar a la primera del archivo
             * así, sólo en este caso se trabaja con la columna 0.
             *
             */
            getline(miRuta, linea);
            secuenciaTemp->insertarDescripcion(linea);

            contador++;

            while (getline(miRuta, linea))
            {
                /* Si la linea inicia una secuencia, describo el nombre de la secuencia en un nuevo iterador*/
                if (linea[0] == '>')
                {
                    secuenciaTemp->insertarInformacionSec(matrizTemporal);
                    this->secuencia->push_back(*secuenciaTemp);
                    // secuenciaTemp->ImprimirSecuencia();
                    secuenciaTemp->insertarDescripcion(linea);
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
            secuenciaTemp->insertarInformacionSec(matrizTemporal);
            this->secuencia->push_back(*secuenciaTemp);
            // secuenciaTemp->ImprimirSecuencia();
        }

        if (this->secuencia->size() == 1)
            cout << "1 secuencia cargada correctamente desde " << ruta << "." << endl;
        else
            cout << this->secuencia->size() << " secuencias cargadas correctamente desde " << ruta << "." << endl;
    }
    catch (const exception &e)
    {
        cout << ruta << " no se encuentra o no puede leerse." << endl;
    }
}

/// @brief Esta función indica el número de secuencias cargadas en memoria.
void Shell::conteo()
{
    if (secuencia->size() == 0)
        cout << "No hay secuencias cargadas en memoria.\n";
    else if (secuencia->size() == 1)
        cout << "1 secuencia en memoria." << endl;
    else
        cout << this->secuencia->size() << " secuencias en memoria.\n";
}

/// @brief Esta función, muestra en la interfaz de comandos, la información de las secuencias e indica la cantidad de bases.
void Shell::listarSecuencias()
{
    list<Secuencia>::iterator it;

    if (secuencia->size() == 0)
        cout << "No hay secuencias cargadas en memoria.\n";
    else
    {
        for (it = secuencia->begin(); it != secuencia->end(); it++)
        {
            cout << it->obtenerTamanioIndentacion() << endl;
            it->imprimirSecuencia();
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
            if (it->obtenerDescripcion() == aux)
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
        cout << "No hay secuencias cargadas en memoria.\n";
    else
    {
        for (it = secuencia->begin(); it != secuencia->end(); it++)
            secuenciaRepetida += it->esSubSecuencia(esSubsecuencia);
    }
    if (secuenciaRepetida == 0)
    {
        cout << "La secuencia dada no existe\n";
        return secuenciaRepetida;
    }
    else
    {
        cout << "La secuencia dada se repite: " << secuenciaRepetida << " veces.\n";
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
        cout << "No hay secuencias cargadas en memoria.\n";
    else
    {
        // Enmascara en relación a la cantidad de elementos que componen la subsecuencia
        for (it = secuencia->begin(); it != secuencia->end(); it++)
        {
            secuenciaRepetida += it->esSubSecuencia(subsecuencia);
            it->enmascarar(subsecuencia);
        }
    }
    if (secuenciaRepetida == 0)
        cout << "La secuencia dada no existe, por tanto no se enmascara nada\n";
    else if (secuenciaRepetida == 1)
        cout << "1 secuencia ha sido enmascarada." << endl;
    else
        cout << secuenciaRepetida << " secuencias han sido enmascaradas.\n";
}

/// @brief Genera un archivo .fa, con las secuencias modificadas.
/// @param ruta
void Shell::guardar(const string &ruta)
{

    list<Secuencia>::iterator it;
    ofstream salida;
    salida.open(ruta);
    string strxlinea = "";

    if (salida.is_open())
    {
        if (secuencia->size() == 0)
            cout << "No hay secuencias cargadas en memoria." << endl;
        else
        {
            for (it = secuencia->begin(); it != secuencia->end(); it++)
            {
                salida << it->obtenerDescripcion() << endl;
                vector<vector<char>> vectortemporal = it->obtenerInformacionSec();

                for (int i = 0; i < vectortemporal.size(); i++)
                {
                    for (int j = 0; j < vectortemporal[i].size(); j++)
                        strxlinea += vectortemporal[i][j];

                    salida << strxlinea << endl;
                    strxlinea = "";
                }
            }
            salida.close();
            cout << "Las secuencias han sido guardadas en " << ruta << "." << endl;
        }
    }
    else
        cout << "Error guardando en " << ruta << "." << endl;
}

int Shell::cantidadTotalBases()
{

    list<Secuencia>::iterator it;
    int acumulador;

    for (it = secuencia->begin(); it != secuencia->end(); it++)
        acumulador += it->numeroBases();

    return acumulador;
}

/// @brief
/// @return
string Shell::frecuenciasTotalesString()
{

    map<char, long long int> mapaTemporalAcumulado;
    map<char, long long int> mapaTemporal;

    //----------------------------------------------------------------

    list<Secuencia>::iterator it = secuencia->begin();
    map<char, long long int>::iterator mapit;
    string str = "[";
    string str1 = "";
    string str2 = "";
    string str3 = "";

    mapaTemporalAcumulado = it->histograma();

    for (it = next(it, 1); it != secuencia->end(); it++)
    {
        mapaTemporal = it->histograma();
        str3 = "";
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

map<char, long long int> Shell::frecuenciasTotalesMap()
{

    map<char, long long int> mapaTemporalAcumulado;
    map<char, long long int> mapaTemporal;

    //----------------------------------------------------------------

    list<Secuencia>::iterator it = secuencia->begin();
    map<char, long long int>::iterator mapit;

    mapaTemporalAcumulado = it->histograma();

    for (it = next(it, 1); it != secuencia->end(); it++)
    {
        mapaTemporal = it->histograma();
        for (mapit = mapaTemporal.begin(); mapit != mapaTemporal.end(); mapit++)
        {
            mapaTemporalAcumulado[mapit->first] = mapaTemporalAcumulado[mapit->first] + mapit->second;
        }
    }

    return mapaTemporalAcumulado;
}

void Shell::codificarSecuencia(const string &ruta)
{
    if (this->secuencia->size() != 0)
    {
        map<char, long long int> histograma;              // Generación del histograma que se utilizará para generar el arbol.
        map<char, string> hojasArboles;                   // Será el resultado del arbol.
        ArbolHuffman *arbolTemporal = new ArbolHuffman(); // ArbolHuffman para obtener los codigos.

        // Genero el mapa de frecuencias
        histograma = this->frecuenciasTotalesMap();

        map<char, long long int>::iterator histo;

        for (histo = histograma.begin(); histo != histograma.end(); histo++)
            if (histo->second == 0)
            {
                histograma.erase(histo->first);
                histo = histograma.begin();
            }

        // A partir de este mapa, genero el arbol con los códigos
        arbolTemporal = arbol->GenerarArbol(histograma);
        // A partir del mapa de frecuencias también, genero el mapa de códigos
        hojasArboles = arbol->GenerarCodigo(histograma);

        map<char, long long int>::iterator reMap; // Declaración del iterador que se usará para recorrer las hojas del arbol.

        // Reinicia el archivo y escribe el primer elemento
        ofstream writer(ruta, ios::out | ios::binary);
        if (!writer)
        {
            cout << "No es posible abrir el archivo" << endl;
            return;
        }

        // n es un número entero de 2 bytes que representa la cantidad de bases diferentes presentes en las secuencia cargadas en ese momento en memoria.
        vector<unsigned char> binary = ObtenerCodigosBytes(bitset<_2B>(histograma.size()).to_string()); // Declaramos vector de binario para recibir los bytes que obtengamos de la conversiones, y obtenemos el tamaño del histograma y lo pasamos a 2 bytes.

        unsigned char basesDiferentes[2]; // declaración de los dos bytes que utilizaremos para almacenar el numero de bases diferentes.

        for (int i = 0; i < 2; i++)
            basesDiferentes[i] = binary[i]; // Se guardan los bytes en un arreglo de unsigned char de un tamaño maximo de 2 (2 bytes)

        writer.write((char *)basesDiferentes, sizeof(basesDiferentes)); // almacenamos el numero de bases diferentes en el archivo.
        binary.clear();                                                 // borramos el codigo binario almacenado en el vector de bytes.

        // ci y fi son dos números entero de 1 y 8 bytes, respectivamente, que representan un código de la base de genoma y su frecuencia asociada (i.e. cuántas veces aparece en todas las secuencias.
        for (reMap = histograma.begin(); reMap != histograma.end(); reMap++) // recorremos el histograma.
        {
            unsigned char codigoFrecuencia[9]; // Declaración de codigo y frecuencia, [0] -> 1 byte código base de genoma y >[0] -> 8 bytes frecuencia almacenada.

            binary = ObtenerCodigosBytes(bitset<_1B>((int)reMap->first).to_string()); // Obtenemos los bytes de código base de genoma.
            codigoFrecuencia[0] = binary[0];                                          // Guardamos el valor en el arreglo de bytes. (1 byte)
            binary.clear();                                                           // Eliminamos los bytes dentro del vector de bytes.

            binary = ObtenerCodigosBytes(bitset<_8B>(reMap->second).to_string()); // Obtenemos los bytes de la frecuencia asociada al código base del genoma.
            for (int i = 0; i < 8; i++)
                codigoFrecuencia[i + 1] = binary[i]; // Guardamos el valor en el arreglo de bytes en las posiciones >[0] (8 bytes)
            binary.clear();                          // Eliminamos los bytes dentro del vector de bytes.

            writer.write((char *)codigoFrecuencia, sizeof(codigoFrecuencia)); // Escribimos en el archivo el codigo de genoma y la frecuencia asociada en bytes.
        }

        binary = ObtenerCodigosBytes(bitset<_4B>(this->secuencia->size()).to_string()); // Obtenemos los bytes correspondientes a la cantidad de las secuencias presentes en la memoria.
        unsigned char cantidadSecuencias[4];                                            // Declaramos los 4 bytes en los que será almacenado el valor obtenido en la conversión.

        for (int i = 0; i < 4; i++)
            cantidadSecuencias[i] = binary[i]; // Guardamos el valor obtenido en la conversión.

        writer.write((char *)cantidadSecuencias, sizeof(cantidadSecuencias)); // Escribimos la cantidad de secuencias presentes en memoria.
        binary.clear();

        list<Secuencia>::iterator it;                               // Declaración del iterador que utilizaremos para recorrer la lista de secuencias.
        for (it = secuencia->begin(); it != secuencia->end(); it++) // Recorremos la lista de secuencias presentes en la memoria.
        {
            //  li es un número entero de 2 bytes que representa el tamaño del nombre de la i-ésima secuencia.
            binary = ObtenerCodigosBytes(bitset<_2B>(it->obtenerDescripcion().size()).to_string()); // Obtenemos los bytes correspondientes al tamaño del nombre de la secuencia en la que nos encontramos.
            unsigned char tamNombreSecuencia[2];                                                    // Declaramos los 2 bytes en los que será almacenado el valor obtenido en la conversión.

            for (int i = 0; i < 2; i++)
                tamNombreSecuencia[i] = binary[i]; // Guardamos el valor obtenido en la conversión.

            writer.write((char *)tamNombreSecuencia, sizeof(tamNombreSecuencia)); // Escribimos el tamaño del nombre de la secuencia actual.
            binary.clear();

            // sij es el caracter que se encuentra en la j-ésima posición del nombre de la i-ésima secuencia.
            char descripcionSec[it->obtenerDescripcion().size()];

            for (int i = 0; i < it->obtenerDescripcion().size(); i++)
                descripcionSec[i] = it->obtenerDescripcion()[i];

            writer.write((char *)descripcionSec, sizeof(descripcionSec));

            // wi es un número entero de 8 bytes que representa la longitud de la i-ésima secuencia.
            binary = ObtenerCodigosBytes(bitset<_8B>(UnirCodigos(DivididosSinCero(arbol->Codificar(it->obtenerInformacionSec(), hojasArboles))).size()).to_string()); // Obtenemos los bytes correspondientes al tamaño de la secuencia en la que nos encontramos.
            unsigned char longitudSecuencia[8];                                                                                                                       // Declaramos los 8 bytes en los que será almacenado el valor obtenido en la conversión.

            for (int i = 0; i < 8; i++)
                longitudSecuencia[i] = binary[i]; // Guardamos el valor obtenido en la conversión.

            writer.write((char *)longitudSecuencia, sizeof(longitudSecuencia)); // Escribimos el tamaño de la secuencia actual.
            binary.clear();

            // xi es un número entero de 2 bytes que representa la indentación de la i-ésima secuencia.
            binary = ObtenerCodigosBytes(bitset<_2B>(it->obtenerTamanioIndentacion()).to_string()); // Obtenemos los bytes correspondientes a la identación secuencia en la que nos encontramos.
            unsigned char identacion[2];                                                            // Declaramos los 2 bytes en los que será almacenado el valor obtenido en la conversión.

            for (int i = 0; i < 2; i++)
                identacion[i] = binary[i]; // Guardamos el valor obtenido en la conversión.

            writer.write((char *)identacion, sizeof(identacion)); // Escribimos el tamaño del nombre de la secuencia actual.
            binary.clear();

            // binary_codei es la secuencia binaria (unos y ceros) que representa la i-ésima secuencia. Note que si la secuencia no es múltiplo de 8, se debe completar con los “0” necesarios.
            binary = ObtenerCodigosBytes(arbol->Codificar(it->obtenerInformacionSec(), hojasArboles));
            unsigned char binaryCode[binary.size()];

            for (int i = 0; i < binary.size(); i++)
                binaryCode[i] = binary[i];

            writer.write((char *)binaryCode, sizeof(binaryCode)); // Escribimos el binary code de la secuencia actual.
            binary.clear();
        }
        writer.close();
        cout << "Secuencias codificadas y almacenadas en " << ruta << "." << endl;
    }
    else
        cout << "No se pueden guardar las secuencias cargadas en " << ruta << "." << endl;
}

/// @brief
/// @param ruta
void Shell::decodificarSecuencia(const string &ruta)
{

    ifstream f(ruta, ios::binary);
    if (f.is_open())
    {
        // Variables para leer el archivo binario
        unsigned char basesDiferentes[2];    // Para la lectura de las bases diferentes del histograma.
        unsigned char codigoFrecuencia[9];   // Histograma por linea.
        unsigned char cantidadSecuencias[4]; // Cantidad de secuencias que habían en la memoría.
        unsigned char tamNombreSecuencia[2]; // Tamaño del nombre de la secuencia a leer.
        unsigned char longitudSecuencia[8];  // Longitud de la secuencia a leer.
        unsigned char identacion[2];         // Identación de la secuencia a leer.
        string binario;                      // Auxiliar que juntara los valores resultantes.

        this->secuencia->clear();            // Borramos la lista para evitar que se añadan.
        map<char, long long int> histograma; // Generación del histograma que se utilizará para generar el arbol.
        map<char, string> hojasArboles;      // Será el resultado del arbol.
        ArbolHuffman *arbolTemporal = new ArbolHuffman();

        f.read((char *)&basesDiferentes, sizeof(basesDiferentes));
        for (int i = 0; i < 2; i++)
            binario += bitset<_1B>((int)basesDiferentes[i]).to_string();

        uint16_t basesDiferents = BinaryCast2B(binario);
        binario.clear();

        for (uint16_t i = 0; i < basesDiferents; i++)
        {
            f.read((char *)&codigoFrecuencia, sizeof(codigoFrecuencia));

            for (int i = 1; i < 9; i++)
                binario += bitset<_1B>((int)codigoFrecuencia[i]).to_string();

            histograma[BinaryCast2B(bitset<_1B>((int)codigoFrecuencia[0]).to_string())] = BinaryCast8B(binario);
            binario.clear();
        }

        arbolTemporal = arbol->GenerarArbol(histograma);
        hojasArboles = arbol->GenerarCodigo(histograma);

        f.read((char *)&cantidadSecuencias, sizeof(cantidadSecuencias));
        for (int i = 0; i < 4; i++)
            binario += bitset<_1B>((int)cantidadSecuencias[i]).to_string();

        uint32_t cantSecuencias = BinaryCast4B(binario);
        binario.clear();

        for (uint32_t j = 0; j < cantSecuencias; j++)
        {
            Secuencia temp;
            f.read((char *)&tamNombreSecuencia, sizeof(tamNombreSecuencia));
            for (int i = 0; i < 2; i++)
                binario += bitset<_1B>((int)tamNombreSecuencia[i]).to_string();

            uint16_t tamDescripcion = BinaryCast2B(binario);
            binario.clear();

            char descripcionChar[tamDescripcion];

            f.read((char *)&descripcionChar, sizeof(descripcionChar));
            for (int i = 0; i < tamDescripcion; i++)
                binario += descripcionChar[i];

            temp.insertarDescripcion(binario);
            binario.clear();

            f.read((char *)&longitudSecuencia, sizeof(longitudSecuencia));
            for (int i = 0; i < 8; i++)
                binario += bitset<_1B>((int)longitudSecuencia[i]).to_string();

            uint64_t longitudSec = BinaryCast8B(binario);
            binario.clear();

            f.read((char *)&identacion, sizeof(identacion));
            for (int i = 0; i < 2; i++)
                binario += bitset<_1B>((int)identacion[i]).to_string();

            uint16_t identacionC = BinaryCast2B(binario);
            binario.clear();

            uint64_t lectura = 0;

            if ((((float)longitudSec / (float)8) - ((uint64_t)longitudSec / (int)8)) > 0)
                lectura = (longitudSec / 8) + 1;
            else
                lectura = longitudSec / 8;

            char codigos[lectura];

            f.read((char *)&codigos, sizeof(codigos));

            vector<unsigned char> bytes;

            for (int i = 0; i < lectura; i++)
                bytes.push_back(codigos[i]);

            binario = BytesACodificado(bytes);

            for (int i = 0; i < ((lectura * 8) - longitudSec); i++)
                binario.pop_back();

            string codificado = arbol->deCodificar(arbolTemporal, binario);
            vector<vector<char>> infoSec;
            vector<char> varInfo;
            uint16_t ident = 0;

            for (int i = 0; i < codificado.size(); i++)
            {
                varInfo.push_back(codificado[i]);
                ident++;
                if (ident == identacionC)
                {
                    infoSec.push_back(varInfo);
                    ident = 0;
                    varInfo.clear();
                }
            }
            if (varInfo.size() > 0)
                infoSec.push_back(varInfo);

            temp.insertarInformacionSec(infoSec);
            this->secuencia->push_back(temp);
        }
        f.close();
        cout << "Secuencias decodificadas desde " << ruta << " y cargadas en memoria." << endl;
    }
    else
        cout << "No se pueden cargar las secuencias en " << ruta << "." << endl;
}

map<char, long long int> Shell::stringaMapa(string stringToMap)
{
    stringstream ss(stringToMap);
    string temp_str;
    map<char, long long int> myMap;

    while (getline(ss, temp_str, ']'))
    {
        string temp_str2;
        string temp_str3;
        temp_str.erase(temp_str.begin());
        temp_str.erase(temp_str.begin() + 1);
        temp_str2.append(temp_str.begin(), temp_str.begin() + 1);
        temp_str3.append(temp_str.begin() + 1, temp_str.end());
        myMap.insert(pair<char, int>(temp_str2[0], stoi(temp_str3)));
        temp_str2.clear();
        temp_str3.clear();
    }

    return myMap;
}

/// @brief Encargado de dar el string que es contenido en el comando.
/// @return string
string Shell::obtenerCommando()
{
    return comando;
}

/// @brief configurar comando agregado.
/// @param Comando
void Shell::insertarComando(string Comando)
{
    comando = Comando;
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

/// @brief Se sale de la función en cualquier punto
void Shell::salir()
{
    exit(0);
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
            listarSecuencias();
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
                codificarSecuencia(entrada[1]);
                insertarComando(entrada[0]);
            }
            else
                cout << "No se especifico el archivo." << endl;
        }
        else if (entrada[0] == "decodificar")
        {
            if (entrada.size() == 2)
            {
                decodificarSecuencia(entrada[1]);
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
