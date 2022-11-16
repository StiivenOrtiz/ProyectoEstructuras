#include "shell.cpp"
#include <iostream>

using namespace std;

int main()
{
    Shell *s = new Shell();
<<<<<<< Updated upstream
    s->comenzar();
    return 0;
=======
    s->cargar("test_genome.fa");
    // s->conteo();
    // s->listarSecuencias();
    // s->histograma("Full_SEQUENCE");
    // s->esSubsecuencia("A");
    // s->enmascarar("A");
    // s->listarSecuencias();
    // s->guardar("nuevo.fa");
    s->codificarSecuencia("final.fabin");
    s->decodificarSecuencia("final.fabin");
    s->listarSecuencias();
    s->salir();

    // Shell *s = new Shell();
    // s->comenzar();
>>>>>>> Stashed changes
}