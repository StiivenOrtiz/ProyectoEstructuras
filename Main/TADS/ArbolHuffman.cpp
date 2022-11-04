<<<<<<< Updated upstream
=======
#include "ArbolHuffman.hpp"
#include <queue>

ArbolHuffman::ArbolHuffman()
{
    this->izquierdo = this->Derecho = NULL;
}

ArbolHuffman::ArbolHuffman(char caracter, int frecuencia)
{
    this->frecuenciaDato = frecuencia;
    this->dato = caracter;
    this->izquierdo = this->Derecho = NULL;
}

// crea árbol y Genera código
map<char, string> ArbolHuffman::GenerarCodigo(map<char, long long int> &m)
{

    map<char, long long int>::iterator it;
    priority_queue<ArbolHuffman *, vector<ArbolHuffman *>, compare> queueDeArboles;

    for (it = m.begin(); it != m.end(); it++)
    {
        /* cout << "|\t" << it->first << "\t|\t" << it->second << "\t|" << endl; */
        queueDeArboles.push(new ArbolHuffman(it->first, it->second));
    }

    while (queueDeArboles.size() != 1)
    {

        izquierdo = queueDeArboles.top();
        /* cout<<"Top: "<<queueDeArboles.top()->dato << endl; */
        queueDeArboles.pop();

        Derecho = queueDeArboles.top();
        queueDeArboles.pop();

        ArbolHuffman *raiz = new ArbolHuffman('*', izquierdo->frecuenciaDato + Derecho->frecuenciaDato);
        raiz->Derecho = Derecho;
        raiz->izquierdo = izquierdo;

        /* cout<<"Dato y frecuencia 1: "<<raiz->dato<<" , "<<raiz->frecuenciaDato<<
        " Dato y frecuencia 2: "<<raiz->Derecho->dato<<" , "<<raiz->Derecho->frecuenciaDato<<
        " Dato y frecuencia 3: "<<raiz->izquierdo->dato<<" , "<<raiz->izquierdo->frecuenciaDato<<endl; */

        queueDeArboles.push(raiz);
    }

    map<char, string> mapaCodigos;

    imprimirCodigosInterno(queueDeArboles.top(), "", mapaCodigos);

    return mapaCodigos;
}

ArbolHuffman *ArbolHuffman::GenerarArbol(map<char, long long int> &m)
{

    map<char, long long int>::iterator it;
    priority_queue<ArbolHuffman *, vector<ArbolHuffman *>, compare> queueDeArboles;

    for (it = m.begin(); it != m.end(); it++)
    {
        queueDeArboles.push(new ArbolHuffman(it->first, it->second));
    }

    while (queueDeArboles.size() != 1)
    {

        izquierdo = queueDeArboles.top();
        /* cout<<"Top: "<<queueDeArboles.top()->dato << endl; */
        queueDeArboles.pop();

        Derecho = queueDeArboles.top();
        queueDeArboles.pop();

        ArbolHuffman *raiz = new ArbolHuffman('*', izquierdo->frecuenciaDato + Derecho->frecuenciaDato);
        raiz->Derecho = Derecho;
        raiz->izquierdo = izquierdo;

        /* cout<<"Dato y frecuencia 1: "<<raiz->dato<<" , "<<raiz->frecuenciaDato<<
        " Dato y frecuencia 2: "<<raiz->Derecho->dato<<" , "<<raiz->Derecho->frecuenciaDato<<
        " Dato y frecuencia 3: "<<raiz->izquierdo->dato<<" , "<<raiz->izquierdo->frecuenciaDato<<endl; */

        queueDeArboles.push(raiz);
    }

    return queueDeArboles.top();
}

void ArbolHuffman::imprimirCodigosInterno(ArbolHuffman *root, string str, map<char, string> &m)
{

    if (!root)
        return;

    if (root->dato != '*')
    {
        m[root->dato] = str;
        /* cout << root->dato << ": " << str << "\n"; */
    }

    imprimirCodigosInterno(root->izquierdo, str + "0", m);
    imprimirCodigosInterno(root->Derecho, str + "1", m);
}

string ArbolHuffman::Codificar(vector<vector<char>> secuencia, map<char, string> codigo)
{

    string str = "";
    for (int i = 0; i < secuencia.size(); i++)
    {
        for (int j = 0; j < secuencia[i].size(); j++)
        {
            str += codigo[secuencia[i][j]];
        }
    }
    return str;
}

string ArbolHuffman::deCodificar(ArbolHuffman *raiz, string codigoHuffman)
{

    string str = "";
    ArbolHuffman *temporal = raiz;

    // Al terminar un camino, se agrega el elemento en código correspondiente en una string que tendrá la respuesta.

    for (int i = 0; i < codigoHuffman.size(); i++)
    {
        if (codigoHuffman[i] == '0')
        {
            temporal = temporal->izquierdo;
        }
        else
        {
            temporal = temporal->Derecho;
        }

        if (temporal->izquierdo == NULL && temporal->Derecho == NULL)
        {
            str += temporal->dato;
            // Se reinicia la raíz
            temporal = raiz;
        }
    }

    return str;
}
>>>>>>> Stashed changes
