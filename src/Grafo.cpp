#include "Grafo.h"

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
        No* addNo = new No(id_add_no,ehPondVertice);
        this->lista_adj.push_back(addNo);
    }

    //insercao de arestas
    for (int i = 0; i < ordem; i++) {
        char idNoOrigem;
        cin>>idNoOrigem; //define no de origem
        int indice=-1; //valor inicial -1 p verificacao
        for (int j = 0; j < ordem; j++) {
            if (this->lista_adj[j]->id == idNoOrigem) {
                indice=j; //encontra indice
                break;
            }
        }

        if (indice==-1) { //verifica se indice eh valido
            No* addNo = new No(idNoOrigem,ehPondVertice); //se nao for, adiciona no novo
            this->lista_adj.push_back(addNo);
        }

        char idAlvoAresta;
        cin>>idAlvoAresta;
        this->lista_adj[indice]->criaAresta(idAlvoAresta); // define aresta nova "na ida"

        int pesoAresta; // declaracao anterior para nao causar erros
        if (ehPondAresta) { // define peso da aresta caso seja ponderado
            cin>>pesoAresta; // caso contrario, peso NAO E INSERIDO
            this->lista_adj[indice]->arestas.back()->peso=pesoAresta;
        }

        if (!direcionado && (idNoOrigem!=idAlvoAresta)) { // faz processo contrario, pois no não direcionado ambos terao a conexao
            //PROCESSO NÃO E FEITO CASO SEJA LACO, pois isto causa duplicatas! (pois não e preciso registrar "a volta", tendo em vista que eh identica à ida)
            int indiceVolta=-1;
            for (int k = 0; k < ordem; k++) {
                if (this->lista_adj[k]->id == idAlvoAresta) {
                    indiceVolta=k; //define indice
                    break;
                }
            }

            if (indiceVolta==-1) { //verifica se indice eh valido
                No* addNo = new No(idAlvoAresta,ehPondVertice); //se nao for, adiciona no novo
                this->lista_adj.push_back(addNo);
            }

            this->lista_adj[indiceVolta]->criaAresta(this->lista_adj[indice]->id); //cria aresta "de volta"

            if (ehPondAresta) { // define o peso ja digitado caso seja ponderado
                this->lista_adj[indiceVolta]->arestas.back()->peso=pesoAresta;
            }

        }
    }

    //criacao da lista de arestas
    this->lista_arestas = new listaArestas(this->lista_adj);
}

Grafo::~Grafo() {
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
    this->lista_arestas->imprimeArestas();
    cout << "Lista de Adjacencias: " << endl;
    for (int i = 0; i < this->ordem; i++) {
        this->lista_adj[i]->imprimeConexoes(this->in_ponderado_aresta);
    }
}