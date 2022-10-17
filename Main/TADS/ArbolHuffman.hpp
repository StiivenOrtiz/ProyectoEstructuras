#pragma once
#include "Codigo.cpp"
#include <string>

using namespace std;

class ArbolHuffman
{
private:
    unsigned frecuenciaDato;
    char dato;
    ArbolHuffman* izquierdo;
    ArbolHuffman* Derecho;

public:
    // Contructor

    ArbolHuffman();
    ArbolHuffman(unsigned frecuencia, char caracter);
    
    // Analizadora

    map<char, int> GenerarCodigo();
    string Codificar(); // Retorna la secuencia codificada
    string deCodificar(const string &ruta); // Decodifica la secuencia

    // Modificador


    void imprimirCodigos();
    void imprimirCodigosInterno();



};