#include "shell.cpp"
#include "Grafo.cpp"
#include <iostream>

using namespace std;

int main()
{
    // Shell *s = new Shell();
    //  s->cargar("test_genome.fa");
    //  s->conteo();
    //  s->listarSecuencias();
    //  s->histograma("Full_SEQUENCE");
    //  s->esSubsecuencia("A");
    //  s->enmascarar("A");
    //  s->listarSecuencias();
    //  s->guardar("nuevo.fa");
    //  s->codificarSecuencia("final.fabin");
    //  s->decodificarSecuencia("final.fabin");
    //  s->listarSecuencias();
    //  s->salir();

    Shell *s = new Shell();
    s->comenzar();

    // Secuencia secu;
    // vector<vector<char>> secuencia = {{'C', 'T', 'C', 'C', 'G', 'G', 'T', 'G', 'A', 'G', 'A', 'A', 'A', 'T', 'T', 'T', 'T', 'G', 'G', 'G', 'A', 'T', 'G', 'T', 'A', 'T', 'C', 'A', 'A', 'A', 'T', 'C', 'A', 'C', 'G', 'G', 'T', 'C', 'C', 'T', 'A', 'C', 'T', 'A', 'C'},
    //                                   {'T', 'C', 'C', 'C', 'T', 'T', 'C', 'A', 'C', 'G', 'C', 'G', 'A', 'A', 'G', 'G', 'A', 'G', 'T', 'C', 'G', 'G', 'A', 'A', 'G', 'T', 'G', 'A', 'T', 'C', 'T', 'G', 'T', 'A', 'T', 'G', 'A', 'A', 'G', 'C', 'T', 'A', 'T', 'T', 'A'},
    //                                   {'C', 'C', 'C', 'T', 'A', 'G', 'G', 'T', 'G', 'G', 'C', 'C', 'A', 'C', 'A', 'C', 'C', 'T', 'A', 'C'}};

    // vector<vector<char>> secuencia = {{'C', 'P', 'C'},
    //                                   {'C', 'J', 'C'},
    //                                   {'A', 'A', 'A'},
    //                                   {'C', 'C'}};

    // vector<vector<char>> secuencia = {{'C', 'P', 'A'},
    //                                   {'C', 'J', 'C'},
    //                                   {'A', 'A'}};

    // string paspi = "Paspi";
    // secu.insertarInformacionSec(secuencia);
    // secu.insertarDescripcion(paspi);

    // Grafo grafo(secu);

    // cout << endl;

    // grafo.imprimirGrafo();

    // vector<vector<pair<pair<int, int>, float>>> costos = grafo.dijkstra(2, 0);
    // grafo.imprimirCostos(costos);
    // grafo.imprimirCaminos(costos);

    // cout << endl;
    // grafo.imprimirVertices();
    // cout << endl;
    // grafo.baseRemota(2, 0);
    // cout << endl;
    // grafo.rutaMasCorta(0, 0, 1, 0);

    return 0;
}