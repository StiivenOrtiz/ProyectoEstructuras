#include "Shell.hxx"

void InsertarSecuencias(const vector<Secuencia> &Secuencias)
{
}

void Cargar(const string &ruta)
{
    try
    {
        ifstream miRuta;

        miRuta.open(ruta);
        if (miRuta.peek() == ifstream::traits_type::eof())
        {
            cout << "El archivo esta vacio" << endl;
        }
        else
        {
        }
    }
    catch (const std::exception &e)
    {
        cout << "No se pudo encontrar el archivo o leerse" << endl;
    }
}