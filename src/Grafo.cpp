#include "Grafo.h"

#include <list>

Grafo::Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice, int ordem) { //COMPLEXIDADE N2! TENTAR AJUSTAR!
    //MOTIVOS: CRIACAO ARESTA / CRIACAO LKISTA VERTICE. UNICOS MOMENTOS N2 ATE A IMPRESSAO SIMPLES.
    this->in_direcionado = direcionado;
    this->in_ponderado_aresta= ehPondAresta;
    this->in_ponderado_vertice= ehPondVertice;
    this->ordem=ordem;

    //insercao de nos
    for (int i = 0; i < ordem; i++) {
        char id_add_no;
        cin >> id_add_no;
        inserirNos(id_add_no);
    }

    //insercao de arestas
    for (int i = 0; i < this->ordem; i++) {
        char idNoOrigem;
        cin>>idNoOrigem; //define no de origem

        int indice = encontraIndiceNo(idNoOrigem);

        if (indice==-1) { //verifica se indice eh valido
            inserirNos(idNoOrigem);
            indice = lista_adj.size() -1; //TA DANDO LOOP QUANDO INSIRO NO NOVO
        }

        char idAlvoAresta;
        cin>>idAlvoAresta;

        int pesoAresta = processarArestaIda(indice, idAlvoAresta);

        if (!direcionado && (idNoOrigem != idAlvoAresta)){
            processarArestaVolta(idAlvoAresta, idNoOrigem, pesoAresta);
        }
    }

    //criacao da lista de arestas
    this->lista_arestas = new listaArestas(this->lista_adj);
}

Grafo::~Grafo() {
}

void Grafo::inserirNos(int id) {
    No* addNo = new No(id, in_ponderado_vertice);
    this->lista_adj.push_back(addNo);
}

void Grafo::imprimirNos() {
    for (auto no : lista_adj) {
        cout << "Nó " << no->id;
        if (in_ponderado_vertice) {
            cout << " (Peso: " << no->peso << ")";
        }
        cout << endl;
    }
}

int Grafo::encontraIndiceNo(char idNo) {
    int indice=-1; //valor inicial -1 p verificacao
    for (int j = 0; j < lista_adj.size(); j++) {
        if (this->lista_adj[j]->id == idNo) {
            indice=j; //encontra indice
            break;
        }
    }
    return indice;
}

int Grafo::processarArestaIda(int indiceOrigem, char idAlvoAresta) {
    lista_adj[indiceOrigem]->criaAresta(idAlvoAresta);

    int pesoAresta;
    if (in_ponderado_aresta) {
        cin >> pesoAresta;
        lista_adj[indiceOrigem]->arestas.back()->peso = pesoAresta;
    }

    return pesoAresta;
}

void Grafo::processarArestaVolta(char idAlvo, char idOrigem, int peso) {
    int indiceVolta = encontraIndiceNo(idAlvo); //busca indice

    if (indiceVolta == -1) { //se o no for invalido, cria um novo no
        No* addNo = new No(idAlvo, in_ponderado_vertice);
        this->lista_adj.push_back(addNo);
        indiceVolta = lista_adj.size()-1;
    }

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