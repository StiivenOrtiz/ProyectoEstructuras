/* Programa desarrollado por Alejandro Uscategui-Torres */

#include <bits/stdc++.h> 

using namespace std;

<<<<<<< Updated upstream
int main(int argc, char *argv[]){

    int a = 0;
    int b = 0;
    int c = 0;
    cout<<"holas\n";
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;
}
=======
int main()
{
    string str = "0110000101100010011000111";
    vector<char> vch;
    // Convierte 01100001 -> A
    // Convierte 01100010 -> B
    // Convierte 01100011 -> C
    // Convertir 10000000 -> CaracterDesconocido
    vch.push_back('A');
    vch.push_back('B');
    vch.push_back('C');
    vch.push_back('Z');

    int bitsSobrantes = (vch.size()*8) - str.size();
    cout<<"Este es el tamaño de el código: "<<str.size()<<endl;
    cout<<"Este es el tamaño de los bits que tiene el vector: "<<vch.size()*8<<endl;
    cout<<"Sobraron: "<<bitsSobrantes<<" bits"<<endl;

    // 01100001011000100110001110000000
    // 0110000101100010011000111
}

>>>>>>> Stashed changes
