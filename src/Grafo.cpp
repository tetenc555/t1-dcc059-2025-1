#include "Grafo.h"

Grafo::Grafo(bool direcionado, bool paresta, bool pvertice, int ordem) {
    this->in_direcionado = direcionado;
    this->in_ponderado_aresta= paresta;
    this->in_ponderado_vertice= pvertice;
    this->ordem=ordem;
    //insercao de nos
    for (int i = 0; i < ordem; i++) {
        char idAddNo;
        cin >> idAddNo;
        No* addNo = new No(idAddNo,pvertice);
        this->lista_adj.push_back(addNo);
    }
    //insercao de arestas
    for (int i = 0; i < ordem; i++) {
        char idNoOrigem;
        cin>>idNoOrigem;
        int indice=-1;
        for (int j = 0; j < ordem; j++) {
            if (this->lista_adj[j]->id == idNoOrigem) {
                indice=j; //define indice
                break;
            }
        }
        if (indice==-1) { //verifica se indice eh valido
            break; /// TROCAR ISSO PRA FICAR VALIDO! ADICIONAR VALIDACOES MAIS CORRETAS !
        }
        char idAlvoAresta;
        cin>>idAlvoAresta;
        this->lista_adj[indice]->criaAresta(idAlvoAresta);

        int pesoAresta;
        if (paresta) {
            cin>>pesoAresta;
            this->lista_adj[indice]->arestas.back()->peso=pesoAresta;
        }

        if (!direcionado) { // faz processo contrario, pois no nao direcionado ambos terao a conexao
            int indiceVolta=-1;
            for (int k = 0; k < ordem; k++) {
                if (this->lista_adj[k]->id == idAlvoAresta) {
                    indiceVolta=k; //define indice
                    break;
                }
            }
            this->lista_adj[indiceVolta]->criaAresta(this->lista_adj[indice]->id);
            if (paresta) {
                this->lista_adj[indiceVolta]->arestas.back()->peso=pesoAresta;
            }

        }
    }
    //criacao da lista de arestas
    this->lista_arestas = new listaArestas(this->lista_adj,direcionado);
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