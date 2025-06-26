#include "Grafo.h"

#include <list>

Grafo::Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice, int ordem) { //COMPLEXIDADE N2! TENTAR AJUSTAR!
    //MOTIVOS: CRIACAO ARESTA / CRIACAO LKISTA VERTICE. UNICOS MOMENTOS N2 ATE A IMPRESSAO SIMPLES.
    this->in_direcionado = direcionado;
    this->in_ponderado_aresta= ehPondAresta;
    this->in_ponderado_vertice= ehPondVertice;
    this->ordem=ordem;

}

Grafo::~Grafo() {
}

void Grafo::inserirNos(char id, int pesoNo) {
    No* addNo = new No(id, this->in_ponderado_vertice ? pesoNo : pesoNo = -1); //cria um novo no com id e peso (caso seja necessario)
    this->lista_adj.push_back(addNo); //adiciona na lista de adjacencias
}

void Grafo::criaListaArestas() {
    this->lista_arestas = new listaArestas(this->lista_adj);
}

void Grafo::imprimirNos() {
    for (auto no : lista_adj) {
        cout << "Nó " << no->id; //imprime id do no
        if (in_ponderado_vertice) {
            cout << " (Peso do Nó: " << no->peso << ")"; //imprime seu peso caso seja ponderado vertice
        }
        cout << endl;
    }
}

int Grafo::encontraIndiceNo(char idNo) {
    int indice=-1; //valor inicial -1 p verificacao
    for (int j = 0; j < int(lista_adj.size()); j++) {
        if (this->lista_adj[j]->id == idNo) {
            indice=j; //encontra indice
            break;
        }
    }
    return indice; //retorna indice valido ou -1 caso no nao exista !
}

bool Grafo::verificaExistenciaNo(char idNo) {
    for (int i=0; i < int(lista_adj.size()); i++) { //percorre todos itens
        if (this->lista_adj[i]->id == idNo) {
            return true; //se achar no retorna true e para o for
        }
    }
    return false; //se nao achar ao fim do for retorna false
}

void Grafo::processarArestaIda(int idOrigem, char idAlvoAresta, int peso) {
    if (!(verificaExistenciaNo(idOrigem) && verificaExistenciaNo((idAlvoAresta)))) { // se o no for invalido, quebra e nao processa a aresta
        cout << "Erro! No invalido na aresta! Nao adicionada, tente novamente" << endl; //imprime mensagem de erro;
        return; //retorna sem adicionar aresta
    }
    int indice = encontraIndiceNo(idOrigem); //busca indice
    lista_adj[indice]->criaAresta(idAlvoAresta); //cria aresta

    if (this->in_ponderado_aresta) {
        this->lista_adj[indice]->arestas.back()->peso=peso; //adiciona peso caso seja ponderado
    }
}

void Grafo::processarArestaVolta(char idAlvo, char idOrigem, int peso) { //praticamente o contrario de processar Aresta Ida
    if (!(verificaExistenciaNo(idOrigem) && verificaExistenciaNo((idAlvo)))) { // se o no for invalido, quebra e nao processa a aresta
        //nao imprime mensagem de erro pois o aviso sera emitido ja na aresta de ida, independente da aresta de volta ser chamada ou nao.
        return; //retorna sem adicionar aresta
    }
    int indiceVolta = encontraIndiceNo(idAlvo); //busca indice
    this->lista_adj[indiceVolta]->criaAresta(idOrigem); //cria aresta partindo do alvo pra origem

    //atribui peso se for ponderado
    if (in_ponderado_aresta) {
        lista_adj[indiceVolta]->arestas.back()->peso = peso;
    }
}

vector<char> Grafo::fecho_transitivo_direto(char id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_floyd(char id_no, char id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

Grafo * Grafo::arvore_geradora_minima_prim(vector<char> ids_nos) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

Grafo * Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

Grafo * Grafo::arvore_caminhamento_profundidade(char id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

int Grafo::raio() {
    cout<<"Metodo nao implementado"<<endl;
    return 0;
}

int Grafo::diametro() {
    cout<<"Metodo nao implementado"<<endl;
    return 0;
}

vector<char> Grafo::centro() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::periferia() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::vertices_de_articulacao() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

void Grafo::imprimirGrafo(){
    cout << this->in_direcionado << " " << this ->in_ponderado_aresta << " " << this->in_ponderado_vertice << endl;
    cout << this->ordem << endl;
    imprimirNos();
    this->lista_arestas->imprimeArestas();
    cout << "Lista de Adjacencias: " << endl;
    for (int i = 0; i < this->ordem; i++) {
        this->lista_adj[i]->imprimeConexoes(this->in_ponderado_aresta);
    }
}