#include <fstream>
#include <iostream>
#include "Gerenciador.h"
#include "LeituraArquivos.h"
using namespace std;

int main(int argc, char *argv[]) {
    // Caminho padrão se nenhum argumento for passado
    string caminho = (argc > 1) ? argv[1] : "./input/g_25_0.16_0_1_0.txt";

    ifstream arquivoTeste(caminho); //verificar se o caminho ta correto
    if (!arquivoTeste) {
        cerr << "Erro: Arquivo não encontrado!\n";
        cerr << "Tentando abrir: " << caminho << "\n";
        cerr << "Execute com: " << argv[0] << " ./input/g_25_0.16_0_1_0.txt\n";
        return 1;
    }
    arquivoTeste.close();

    Grafo* grafo = LeituraArquivos::lerGrafodoArquivo(caminho);
    Gerenciador::comandos(grafo);
    return 0;
}
