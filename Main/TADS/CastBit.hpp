#pragma once

#include <stdint.h>
#include <string>
#include <bitset>

const int _1B = 8;
const int _2B = 16;
const int _4B = 32;
const int _8B = 64;

// ---------    = 1 byte  = 8  bits
// short int    = 2 bytes = 16 bits
// int          = 4 bytes = 32 bits
// long long    = 8 bytes = 64 bits

using namespace std;

uint16_t BinaryCast2B(string binario)
{
    uint16_t retorno = 0;
    int potencia = 1;

    for (int i = binario.length() - 1; i >= 0; i--)
    {
        if (binario[i] == '1')
            retorno += 1 * potencia;
        potencia *= 2;
    }

    return retorno;
}

uint32_t BinaryCast4B(string binario)
{
    uint32_t retorno = 0;
    int potencia = 1;

    for (int i = binario.length() - 1; i >= 0; i--)
    {
        if (binario[i] == '1')
            retorno += 1 * potencia;
        potencia *= 2;
    }

    return retorno;
}

uint64_t BinaryCast8B(string binario)
{
    uint64_t retorno = 0;
    int potencia = 1;

    for (int i = binario.length() - 1; i >= 0; i--)
    {
        if (binario[i] == '1')
            retorno += 1 * potencia;
        potencia *= 2;
    }

    return retorno;
}

vector<unsigned char> ConvertirABytes(vector<string> paraConvertir)
{
    vector<unsigned char> bytes;

    for (int i = 0; i < paraConvertir.size(); i++)
        bytes.push_back(BinaryCast2B(paraConvertir[i]));

    return bytes;
}

string UnirCodigos(vector<string> ParaUnir)
{
    string unidos = "";

    for (int i = 0; i < ParaUnir.size(); i++)
        unidos += ParaUnir[i];

    return unidos;
}

string BytesACodificado(vector<unsigned char> bytes)
{
    string codificado = "";
    vector<string> codigos;

    for (int i = 0; i < bytes.size(); i++)
    {
        codigos.push_back(bitset<8>((int)bytes[i]).to_string());
    }

    codificado = UnirCodigos(codigos);

    return codificado;
}

vector<string> Divididos(vector<string> paraDividir)
{
    vector<string> guardar;
    string unidos = UnirCodigos(paraDividir);

    int cont = 0;
    string paraGuardar = "";

    for (int i = 0; i < unidos.size(); i++)
    {
        paraGuardar += unidos[i];
        cont += 1;
        if (cont == 8)
        {
            guardar.push_back(paraGuardar);
            paraGuardar = "";
            cont = 0;
        }
    }

    if (paraGuardar.size() > 0)
    {
        for (int i = paraGuardar.size(); i < 8; i++)
            paraGuardar += "0";

        guardar.push_back(paraGuardar);
    }

    return guardar;
}

vector<string> Divididos(string paraDividir)
{
    vector<string> guardar;

    int cont = 0;
    string paraGuardar = "";

    for (int i = 0; i < paraDividir.size(); i++)
    {
        paraGuardar += paraDividir[i];
        cont += 1;
        if (cont == 8)
        {
            guardar.push_back(paraGuardar);
            paraGuardar = "";
            cont = 0;
        }
    }

    if (paraGuardar.size() > 0)
    {
        for (int i = paraGuardar.size(); i < 8; i++)
            paraGuardar += "0";

        guardar.push_back(paraGuardar);
    }

    return guardar;
}

vector<string> DivididosSinCero(string paraDividir)
{
    vector<string> guardar;

    int cont = 0;
    string paraGuardar = "";

    for (int i = 0; i < paraDividir.size(); i++)
    {
        paraGuardar += paraDividir[i];
        cont += 1;
        if (cont == 8)
        {
            guardar.push_back(paraGuardar);
            paraGuardar = "";
            cont = 0;
        }
    }

    if (paraGuardar.size() > 0)
        guardar.push_back(paraGuardar);

    return guardar;
}

vector<unsigned char> ObtenerCodigosBytes(string Codigo)
{
    return ConvertirABytes(Divididos(Codigo));
}