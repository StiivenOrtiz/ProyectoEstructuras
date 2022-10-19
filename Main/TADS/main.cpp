#include "shell.cpp"
#include <iostream>

using namespace std;

int main()
{
    Shell* s = new Shell();
    s->cargar("AligSeq85678.fa");
    /* s->conteo();
    s->listar_Secuencias(); 
    s->histograma("Full_SEQUENCE");
    s->esSubsecuencia("A");
    s->enmascarar("A");
    s->listar_Secuencias();
    s->guardar("nuevo.fa"); */
    s->codificarSecuencua("Prueba.fabin");
    s->decodificarSecuencua("Prueba.fabin");
    s->salir();
}