#pragma once
#include "Secuencia.hpp"
#include <string>

using namespace std;

class ArbolHuffman
{ 
    
public:

    unsigned frecuenciaDato;
    char dato;
    ArbolHuffman* izquierdo;
    ArbolHuffman* Derecho;  
    // Contructor

    ArbolHuffman();
    ArbolHuffman(char caracter, int frecuencia);

    // Analizadora

    // Recibe un mapa general
    map<char,string> GenerarCodigo(map<char,int> &m);
    ArbolHuffman* GenerarArbol(map<char,int> &m);
    string Codificar(vector<vector<char>> secuencia, map<char,string> codigo); // Retorna la secuencia codificada
    string deCodificar(ArbolHuffman* raiz, string codigoHuffman); // Decodifica la secuencia

    // Modificador

    void imprimirCodigos();
    void imprimirCodigosInterno(ArbolHuffman* root, string str, map<char,string> &m);
    
    friend class compare;
};

struct compare {
 
    bool operator()(ArbolHuffman* l, ArbolHuffman* r)
 
    {
        return (l->frecuenciaDato > r->frecuenciaDato);
    }
};