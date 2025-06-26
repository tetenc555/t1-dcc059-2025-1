#include <iostream>
#include "Gerenciador.h"
#include "LeituraArquivos.h"
using namespace std;
int main(int argc, char *argv[])
{
    Grafo* grafo = LeituraArquivos::lerGrafodoArquivo("./input/grafo100.txt");

    Gerenciador::comandos(grafo);

    return 0;
}
