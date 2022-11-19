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

    // Shell *s = new Shell();
    // s->comenzar();

    Secuencia secu;
    vector<vector<char>> secuencia = {{'C', 'T', 'C', 'C', 'G', 'G', 'T', 'G', 'A', 'G', 'A', 'A', 'A', 'T', 'T', 'T', 'T', 'G', 'G', 'G', 'A', 'T', 'G', 'T', 'A', 'T', 'C', 'A', 'A', 'A', 'T', 'C', 'A', 'C', 'G', 'G', 'T', 'C', 'C', 'T', 'A', 'C', 'T', 'A', 'C'},
                                      {'T', 'C', 'C', 'C', 'T', 'T', 'C', 'A', 'C', 'G', 'C', 'G', 'A', 'A', 'G', 'G', 'A', 'G', 'T', 'C', 'G', 'G', 'A', 'A', 'G', 'T', 'G', 'A', 'T', 'C', 'T', 'G', 'T', 'A', 'T', 'G', 'A', 'A', 'G', 'C', 'T', 'A', 'T', 'T', 'A'},
                                      {'C', 'C', 'C', 'T', 'A', 'G', 'G', 'T', 'G', 'G', 'C', 'C', 'A', 'C', 'A', 'C', 'C', 'T', 'A', 'C'}};

    // vector<vector<char>> secuencia = {{'C', 'C', 'C'},
    //                                   {'C', 'C', 'C'},
    //                                   {'C', 'C', 'C'}};
    secu.insertarInformacionSec(secuencia);
    Grafo grafo(secu);
    grafo.imprimirGrafo();
    vector<vector<float>> costos = grafo.dijkstra(0, 0);
    for (int i = 0; i < costos.size(); i++)
    {
        cout << endl;
        for (int j = 0; j < costos[i].size(); j++)
            cout << costos[i][j] << "\t-\t";
        cout << endl;
    }
    cout << endl;

    return 0;
}