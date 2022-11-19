#include "Grafo.hpp"

/// @brief Constructor
/// @param secuencia
Grafo::Grafo(Secuencia secuencia)
{
    this->vertices.clear();
    this->aristas.clear();
    this->visitados.clear();

    this->vertices = secuencia.obtenerInformacionSec();

    for (int fila = 0; fila < this->vertices.size(); fila++)
    {
        for (int columna = 0; columna < this->vertices[fila].size(); columna++)
        {
            this->visitados[to_string(fila) + "," + to_string(columna)] = false;

            if ((columna - 1) != -1)
                this->aristas.push_back({{fila, columna}, {fila, columna - 1}, (float)((float)1 / ((float)1 + (float)(abs(this->vertices[fila][columna] - this->vertices[fila][columna - 1]))))});
            if ((fila - 1) != -1)
                this->aristas.push_back({{fila, columna}, {fila - 1, columna}, (float)((float)1 / ((float)1 + (float)(abs(this->vertices[fila][columna] - this->vertices[fila][columna - 1]))))});
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
pair<int, int> Grafo::siguienteVertice(vector<vector<float>> costos)
{
    pair<int, int> menor = {0, -1};
    for (int fila = 0; fila < this->vertices.size(); fila++)
        for (int columna = 0; columna < this->vertices[fila].size(); columna++)
            if (!marcadoVertice(fila, columna) && costos[fila][columna] != -1)
                if (menor.second == -1 || costos[fila][menor.second] > costos[fila][columna])
                {
                    menor.first = fila;
                    menor.second = columna;
                }

    if (menor.second == -1)
        return {0, -1};
    else
    {
        menor.second;
        return menor;
    }
}

/// @brief
/// @param i
/// @param j
/// @return
vector<vector<float>> Grafo::dijkstra(int i, int j)
{
    int fila, columna;
    float costo;
    vector<vector<float>> costos;
    desmarcarGrafo();

    for (fila = 0; fila < this->vertices.size(); fila++)
    {
        vector<float> temp;
        for (columna = 0; columna < this->vertices[fila].size(); columna++)
            temp.push_back(costoArco(i, j, fila, columna));
        costos.push_back(temp);
    }

    marcarVertice(i, j);
    costos[i][j] = 0;

    pair<int, int> v;
    v.first = i;
    v.second = j;

    while (validacion(v, costos) != -1)
    {
        marcarVertice(v.first, v.second);
        for (fila = 0; fila < this->vertices.size(); fila++)
        {
            for (columna = 0; columna < this->vertices[fila].size(); columna++)
            {
                if (!marcadoVertice(fila, columna) && (costo = costoArco(v.first, v.second, fila, columna)) != -1)
                    if (costos[fila][columna] == -1)
                        costos[fila][columna] = costos[v.first][v.second] + costo;
                    else
                        costos[fila][columna] = min(costos[fila][columna], costos[v.first][v.second] + costo);
            }
        }
    }
    return costos;
}

int Grafo::validacion(pair<int, int> &v, vector<vector<float>> &costos)
{
    v = siguienteVertice(costos);
    return v.second;
}

/// @brief
void Grafo::imprimirGrafo()
{
    for (int i = 0; i < this->aristas.size(); i++)
    {
        cout << "Vertice 1: { x: " << aristas[i].vertice1.first << " y: " << aristas[i].vertice1.second << " } Vertice 2: { x: " << aristas[i].vertice2.first << " y: " << aristas[i].vertice2.second << " } Costo: " << aristas[i].costo << endl;
    }
}