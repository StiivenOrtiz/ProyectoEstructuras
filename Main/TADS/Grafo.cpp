#include "Grafo.hpp"

/// @brief Constructor
/// @param secuencia
Grafo::Grafo(Secuencia secuencia)
{
    this->vertices.clear();
    this->aristas.clear();
    this->visitados.clear();
    this->descripcion = secuencia.obtenerDescripcion();
    this->vertices = secuencia.obtenerInformacionSec();

    for (int fila = 0; fila < this->vertices.size(); fila++)
    {
        for (int columna = 0; columna < this->vertices[fila].size(); columna++)
        {
            this->visitados[to_string(fila) + "," + to_string(columna)] = false;

            if ((columna - 1) != -1)
                this->aristas.push_back({{fila, columna}, {fila, columna - 1}, (float)((float)1.0 / ((float)1.0 + (float)(abs(this->vertices[fila][columna] - this->vertices[fila][columna - 1]))))});
            if ((fila - 1) != -1)
                this->aristas.push_back({{fila, columna}, {fila - 1, columna}, (float)((float)1.0 / ((float)1.0 + (float)(abs(this->vertices[fila][columna] - this->vertices[fila - 1][columna]))))});
        }
    }
}

/// @brief Destructor
Grafo::~Grafo()
{
    this->vertices.clear();
    this->aristas.clear();
    this->visitados.clear();
}

/// @brief
void Grafo::desmarcarGrafo()
{
    unordered_map<string, bool>::iterator it;
    for (it = this->visitados.begin(); it != this->visitados.end(); it++)
        it->second = false;
}

/// @brief
/// @param x
/// @param y
void Grafo::marcarVertice(int i, int j)
{
    string posicion = to_string(i) + "," + to_string(j);
    this->visitados[posicion] = true;
}

/// @brief
/// @param i
/// @param j
/// @param x
/// @param y
/// @return
float Grafo::costoArco(int i, int j, int x, int y)
{
    for (int indice = 0; indice < this->aristas.size(); indice++)
    {
        if (this->aristas[indice].vertice1.first == i && this->aristas[indice].vertice1.second == j)
            if (this->aristas[indice].vertice2.first == x && this->aristas[indice].vertice2.second == y)
                return this->aristas[indice].costo;

        if (this->aristas[indice].vertice1.first == x && this->aristas[indice].vertice1.second == y)
            if (this->aristas[indice].vertice2.first == i && this->aristas[indice].vertice2.second == j)
                return this->aristas[indice].costo;
    }
    return -1;
}

/// @brief
/// @param i
/// @param j
void Grafo::desmarcarVertice(int i, int j)
{
    string posicion = to_string(i) + "," + to_string(j);
    this->visitados[posicion] = false;
}

/// @brief
/// @param i
/// @param j
/// @return
bool Grafo::marcadoVertice(int i, int j)
{
    string posicion = to_string(i) + "," + to_string(j);
    return this->visitados[posicion];
}

/// @brief
/// @param costo
/// @return
pair<int, int> Grafo::siguienteVertice(vector<vector<pair<pair<int, int>, float>>> costos)
{
    pair<int, int> menor = {-1, -1};
    for (int fila = 0; fila < this->vertices.size(); fila++)
        for (int columna = 0; columna < this->vertices[fila].size(); columna++)
            if (!marcadoVertice(fila, columna) && costos[fila][columna].second != -1)
                if ((menor.first == -1 && menor.second == -1) || costos[menor.first][menor.second].second > costos[fila][columna].second)
                {
                    menor.first = fila;
                    menor.second = columna;
                }

    if (menor.second == -1)
        return {-1, -1};
    else
    {
        menor.second + 1;
        return menor;
    }
}

/// @brief
/// @param i
/// @param j
/// @return
vector<vector<pair<pair<int, int>, float>>> Grafo::dijkstra(int i, int j)
{
    int fila, columna;
    float costo;
    vector<vector<pair<pair<int, int>, float>>> costos;
    pair<int, int> v = {i, j};
    desmarcarGrafo();

    for (fila = 0; fila < this->vertices.size(); fila++)
    {
        vector<pair<pair<int, int>, float>> temp;
        for (columna = 0; columna < this->vertices[fila].size(); columna++)
            temp.push_back({v, costoArco(i, j, fila, columna)});
        costos.push_back(temp);
    }

    marcarVertice(v.first, v.second);
    costos[i][j] = {{-1, -1}, 0};

    while (validacion(v, costos) != -1)
    {
        marcarVertice(v.first, v.second);
        for (fila = 0; fila < this->vertices.size(); fila++)
        {
            for (columna = 0; columna < this->vertices[fila].size(); columna++)
            {
                if (!marcadoVertice(fila, columna) && ((costo = costoArco(v.first, v.second, fila, columna)) != -1))
                    if (costos[fila][columna].second == -1)
                        costos[fila][columna] = {v, (costos[v.first][v.second].second + costo)};
                    else
                        costos[fila][columna] = {v, min(costos[fila][columna].second, costos[v.first][v.second].second + costo)};
            }
        }
    }

    return costos;
}

int Grafo::validacion(pair<int, int> &v, vector<vector<pair<pair<int, int>, float>>> &costos)
{
    v = siguienteVertice(costos);
    return v.second;
}

/// @brief
void Grafo::imprimirGrafo()
{
    for (int i = 0; i < this->aristas.size(); i++)
        cout << "Vertice 1: {x: " << aristas[i].vertice1.first << " y: " << aristas[i].vertice1.second << "} Vertice 2: {x: " << aristas[i].vertice2.first << " y: " << aristas[i].vertice2.second << "} Costo: " << aristas[i].costo << endl;
}

/// @brief
/// @param base
/// @return
vector<pair<int, int>> Grafo::posicionMismosVertices(int i, int j)
{
    vector<pair<int, int>> retorno;
    char base = this->vertices[i][j];

    for (int fila = 0; fila < this->vertices.size(); fila++)
        for (int columna = 0; columna < this->vertices[fila].size(); columna++)
            if (base == this->vertices[fila][columna] && (fila != i || columna != j))
                retorno.push_back({fila, columna});

    return retorno;
}

/// @brief
/// @param i
/// @param j
/// @return
bool Grafo::baseRemota(int i, int j)
{
    vector<pair<int, int>> basesIguales = posicionMismosVertices(i, j);
    if (basesIguales.size() > 0)
    {
        vector<vector<pair<pair<int, int>, float>>> direccionamiento = dijkstra(i, j);
        vector<vector<pair<int, int>>> caminos;

        for (int indice = 0; indice < basesIguales.size(); indice++)
        {
            pair<int, int> posicion = {basesIguales[indice].first, basesIguales[indice].second};
            vector<pair<int, int>> aux;
            do
            {
                aux.push_back(posicion);
                posicion = direccionamiento[posicion.first][posicion.second].first;
            } while (posicion.first != -1 && posicion.second != -1);
            caminos.push_back(aux);
        }

        int posMax = 0;
        for (int fila = 0; fila < caminos.size(); fila++)
            if (fila != 0 && caminos[fila].size() > caminos[fila - 1].size())
                posMax = fila;

        cout << "Para la secuencia " << this->descripcion.substr(1, (descripcion.size() - 1)) << ", la base remota esta ubicada en [" << basesIguales[posMax].first << "," << basesIguales[posMax].second << "],"
             << "\ny la ruta entre la base en [" << i << "," << j << "] y la base remota en [" << basesIguales[posMax].first << "," << basesIguales[posMax].second << "] es:\n\n";

        for (int columna = (caminos[posMax].size() - 1); columna >= 0; columna--)
        {
            cout << "[" << caminos[posMax][columna].first << "," << caminos[posMax][columna].second << "] ";
            if (columna != 0)
                cout << "- ";
        }
        cout << "\n\n"
             << "El costo total de la ruta es: " << direccionamiento[basesIguales[posMax].first][basesIguales[posMax].second].second << endl;

        return true;
    }
    return false;
}

/// @brief
/// @param i
/// @param j
/// @param x
/// @param y
/// @return
void Grafo::rutaMasCorta(int i, int j, int x, int y)
{
    pair<bool, bool> origenDestino = {false, false};

    if (i < this->vertices.size())
        if (j < this->vertices[i].size())
            origenDestino.first = true;

    if (origenDestino.first == false)
        cout << "La base en la posicion [" << i << "," << j << "] no existe." << endl;

    if (x < this->vertices.size())
        if (y < this->vertices[x].size())
            origenDestino.second = true;

    if (origenDestino.second == false)
        cout << "La base en la posición [" << x << "," << y << " ] no existe." << endl;

    if (origenDestino.first == true && origenDestino.second == true)
    {
        vector<vector<pair<pair<int, int>, float>>> direccionamiento = dijkstra(i, j);
        vector<pair<int, int>> caminos;
        pair<int, int> posicion = {x, y};

        do
        {
            caminos.push_back(posicion);
            posicion = {direccionamiento[posicion.first][posicion.second].first};
        } while (posicion.first != -1 && posicion.second != -1);

        cout << "\nPara la secuencia " << this->descripcion.substr(1, (descripcion.size() - 1)) << ", la ruta mas corta entre la base en [" << i << "," << j << "] y la base en"
             << " [" << x << "," << y << "] es:\n\n";

        for (int indice = (caminos.size() - 1); indice >= 0; indice--)
        {
            cout << "[" << caminos[indice].first << "," << caminos[indice].second << "] ";
            if (indice != 0)
                cout << "- ";
        }

        cout << "\n\nEl costo total de la ruta es: " << direccionamiento[x][y].second << "\n\n";
    }
}

/// @brief
void Grafo::imprimirVertices()
{
    for (int i = 0; i < this->vertices.size(); i++)
    {
        for (int j = 0; j < this->vertices[i].size(); j++)
        {
            cout << "[" << i << "," << j << "]: " << this->vertices[i][j] << "      ";
            if (j != this->vertices[i].size() - 1)
                cout << "- ";
        }
        cout << endl;
    }
}

void Grafo::imprimirCostos(vector<vector<pair<pair<int, int>, float>>> &costos)
{
    cout << endl;
    for (int i = 0; i < costos.size(); i++)
    {
        for (int j = 0; j < costos[i].size(); j++)
        {
            cout << "[" << i << "," << j << "]: ";
            if (costos[i][j].second >= 0 && costos[i][j].second < 10)
                cout << "0";
            cout << fixed << setprecision(3) << costos[i][j].second << " ";
            if (j != costos[i].size() - 1)
                cout << "-";
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Grafo::imprimirCaminos(vector<vector<pair<pair<int, int>, float>>> &costos)
{
    cout << endl;
    for (int i = 0; i < costos.size(); i++)
    {
        for (int j = 0; j < costos[i].size(); j++)
        {
            if (costos[i][j].first.first == -1 || costos[i][j].first.second == -1)
                cout << "[" << i << "," << j << "]: x,y    ";
            else
                cout << "[" << i << "," << j << "]: " << costos[i][j].first.first << "," << costos[i][j].first.second << "    ";
            if (j != costos[i].size() - 1)
                cout << "-";
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}