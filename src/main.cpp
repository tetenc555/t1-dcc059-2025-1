#include <iostream>
#include "Gerenciador.h"

using namespace std;
int main(int argc, char *argv[])
{
    bool direcionado, paresta, pvertice;
    int ordem;
    cin >> direcionado >> paresta >> pvertice >> ordem;

    Grafo* grafo = new Grafo(direcionado, paresta, pvertice, ordem);

    Gerenciador::comandos(grafo);

    return 0;
}
