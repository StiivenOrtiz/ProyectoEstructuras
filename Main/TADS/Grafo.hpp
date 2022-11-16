#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Secuencia.cpp"

using namespace std;

class Grafo
{
private:
    vector<pair<pair<string, char>, vector<pair<string, float>>>> grafo;
    unordered_map<string, bool> visitados;

public:
    Grafo();
    ~Grafo();

    int ordenGrafo();
};
