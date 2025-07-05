#include "Grafo.h"

#include <list>
#include <unordered_set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <limits>

Grafo::Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice) { //COMPLEXIDADE N2! TENTAR AJUSTAR!
    //MOTIVOS: CRIACAO ARESTA / CRIACAO LKISTA VERTICE. UNICOS MOMENTOS N2 ATE A IMPRESSAO SIMPLES.
    this->in_direcionado = direcionado;
    this->in_ponderado_aresta= ehPondAresta;
    this->in_ponderado_vertice= ehPondVertice;
    this->ordem = 0;
}

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
    if (!verificaExistenciaNo(id)) {
        No* addNo = new No(id, this->in_ponderado_vertice ? pesoNo : -1);
        this->lista_adj.push_back(addNo);
        this->ordem++;
    }
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
    if (!this->in_direcionado) { //se for nao direcionado, retorna vazio
        cout<<"Nao é direcionado!"<<endl;
        return {};
    }
    vector <char> retorno;
    for (tuple conexao: this->lista_arestas->conexoes) {
        if (get<1>(conexao) == id_no)
            retorno.push_back(get<0>(conexao));
    }
    return retorno;
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    if (!this->in_direcionado) { //se for nao direcionado, retorna vazio
        cout<<"Nao é direcionado!"<<endl;
        return {};
    }

    unordered_set<char> calculoRetorno; //cria unorderedSet ao inves de retorno a fim de melhorar processamento
    queue<char> filaProcessamento; //cria fila em que sempre teremos o proximo item
    //A FILA E IMPORTANTE POIS FOI A MELHOR MANEIRA DE GARANTIR QUE ELE QUEBRE APENAS QUANDO NAO HOUVER MAIS CONEXOES A SEREM PROCESSADAS!


    filaProcessamento.push(id_no); // Inicia com o no final! Ele é o destino final, ou seja, o primeiro no ""caminhamento contrario"".

    while (!filaProcessamento.empty()){ // enquanto a fila nao tiver vazia, processa o proximo item

        char processando=filaProcessamento.front(); //define o destino a ser processado (ele vai voltando)
        filaProcessamento.pop(); //remove ele da fila. //Assim mantemos nenhum item na fila durante processamento, e salvamos apenas se encontrar outro a processar
        //Isto garante que o while quebre corretamente (caso nao ache mais vertices a serem processados) -> ISSO TAVA SENDO O MAIOR PROBLEMA EM CICLOS! causado pela ordem formada pela lista de arestas.

        for (tuple conexao: this->lista_arestas->conexoes) { //pra cada processamento olhamos todas as conexoes
            char origemAresta = get<0>(conexao);
            char destinoAresta = get<1>(conexao);

            if (destinoAresta == processando) { //verifica se o destino desta conexao e o que estamos processando
                if (calculoRetorno.find(origemAresta) == calculoRetorno.end()) { //MOTIVO PRINCIPAL DE USAR UNORDERED SET! -> verificacao se a origem ja foi registrada
                    //vi no stackoverflow que assim o processamento e menor, e resolve o problema de ter que usar +1 lista de arestas (jaPassou anterior) pra essa verificação
                    calculoRetorno.insert(origemAresta); //insere origem como retorno valido
                    filaProcessamento.push(origemAresta); //define origem como proximo destino valido p ser processsado
                }
            }
        }
    }
    calculoRetorno.erase(id_no); //remove no em si - ele aparece em caso de loop ou ciclo.
    vector<char> retorno(calculoRetorno.begin(), calculoRetorno.end()); //usa funcao nativa pra copiar pra vetor
    return retorno;
}


vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b) {
    vector<char> caminho_resultado;

    if (!verificaExistenciaNo(id_no_a) || !verificaExistenciaNo(id_no_b)) {
        cout << "Um dos vertices nao foi encontrado!" << endl;
        return caminho_resultado;
    }

    unordered_map<char, int> id_para_indice;
    unordered_map<int, char> indice_para_id;

    for (int i = 0; i < lista_adj.size(); ++i) {
        id_para_indice[lista_adj[i]->id] = i;
        indice_para_id[i] = lista_adj[i]->id;
    }

    int origem = id_para_indice[id_no_a];
    int destino = id_para_indice[id_no_b];

    int n = lista_adj.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<int> pai(n, -1);
    vector<bool> visitado(n, false);

    dist[origem] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> fila;
    fila.push({0, origem});

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        if (visitado[u]) continue;
        visitado[u] = true;

        No* no_atual = lista_adj[u];

        for (Aresta* aresta : no_atual->arestas) {
            int v = id_para_indice[aresta->id_no_alvo];
            int peso = (in_ponderado_aresta ? aresta->peso : 1); // se não for ponderado, peso = 1

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pai[v] = u;
                fila.push({dist[v], v});
            }
        }
    }

    if (dist[destino] == numeric_limits<int>::max()) {
        return caminho_resultado;
    }

    stack<char> pilha_caminho;
    for (int v = destino; v != -1; v = pai[v]) {
        pilha_caminho.push(indice_para_id[v]);
    }

    while (!pilha_caminho.empty()) {
        caminho_resultado.push_back(pilha_caminho.top());
        pilha_caminho.pop();
    }

    return caminho_resultado;
}

vector<char> Grafo::caminho_minimo_floyd(char id_no, char id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

Grafo * Grafo::criaSubGrafoVerticeInduzido(vector <char> ids_nos) {
    Grafo* subGrafo = new Grafo(this->in_direcionado, this->in_ponderado_aresta, this->in_ponderado_vertice); // gera grafo inical
    for (char id : ids_nos) { // percorre cada id para copiar nos
        int indice = this->encontraIndiceNo(id); // encontra indice
        if (indice == -1) { //verifica se achou
            cout << "No de ID:" << id << " nao encontrado! Pulamos este." << endl;
        }
        else
            subGrafo->lista_adj.push_back(this->lista_adj[indice]); // adiciona no com sua arestas na lista
    }
    for (No* no : subGrafo->lista_adj) { //deletaremos agor aarestas com alvos que nao existem
        for (int i=(int(no->arestas.size()) - 1); i>=0 ; i--) {  //para evitar erros com erase, que encurta o vetor e quebra a deletacao correta, iteramos ao contrario
            if (!subGrafo->verificaExistenciaNo(no->arestas[i]->id_no_alvo)) { // se id alvo nao existir no grafo, deleta!
                no->arestas.erase(no->arestas.begin() + i); //remove aresta
            }
        }
    }
    subGrafo->criaListaArestas(); //cria lista de arestas
    subGrafo->ordem = subGrafo->lista_adj.size(); //define ordem
    //assim o subgrafo esta completo.
    return subGrafo;
}

Grafo * Grafo::arvore_geradora_minima_prim(vector<char> ids_nos) {
    //Primeiro passo: gerar subgrafo
    Grafo* Inicial = criaSubGrafoVerticeInduzido(ids_nos);
    Inicial->imprimirGrafo();
    return nullptr; //retorna nulo pois nao implementado
}

Grafo * Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos)
{
    //condicoes // verifica se eh conexo? //verificar return
    if (!this->in_ponderado_aresta) { //se nao for ponderado vai de arrasta
        cout<<"Nao eh ponderado!"<<endl;
        return {};
    }
    if (this->in_direcionado){ // se eh direcionado vai de arrasta
        cout<<"Eh direcionado!" << endl;
        return nullptr;
    }

    //uma lista com ponderamento de arestas em ordem
    //uma vazia para passar a ordem
    //retornar essa "vazia"
    for (int arestasArvoreGeradora=0; ordem-1 != 0; arestasArvoreGeradora++) //condicao de uma arvore geradora de kruskal
    {
        //verificar se a aresta (dois vertices que se ligam) tem algum vertice em comum
    }
    cout<<"Metodo nao implementado"<<endl;
    return nullptr; //retorno a lista da arvore geradora
}

Grafo * Grafo::arvore_caminhamento_profundidade(char id_no) {
    //Verifica se o no inicial existe
    int indiceInicial = encontraIndiceNo(id_no);
    if (indiceInicial == -1) {
        cout << "No inicial nao encontrado!" << endl;
        return nullptr;
    }

    //Cria grafo para arvore de busca por profundidade
    Grafo* arvore = new Grafo(true, this->in_ponderado_aresta, this->in_ponderado_vertice);

    //Marca nós como não visitados (caso seja alterado por outro metodo)
    for (auto no: lista_adj) {
        no->setVisitado(false);
    }

    //Chama a função auxiliar iterativa para construir a arvore
    buscaProfundidadeAux(lista_adj[indiceInicial], arvore);
    arvore->ordem = lista_adj.size(); //altera a ordem da arvore
    return arvore;
}

void Grafo::buscaProfundidadeAux(No* inicio, Grafo* arvore) {
    if (!inicio) return;

    stack<No*> pilha;
    unordered_map<char, bool> visitados;

    pilha.push(inicio);
    visitados[inicio->id] = true;
    arvore->inserirNos(inicio->id, inicio->peso);

    while (!pilha.empty()) {
        No* atual = pilha.top();
        pilha.pop();

        // Processa arestas em ordem inversa para manter ordem correta
        for (auto it = atual->arestas.rbegin(); it != atual->arestas.rend(); ++it) {
            auto aresta = *it;
            if(!visitados[aresta->id_no_alvo]) {
                int vizinhoIdx = encontraIndiceNo(aresta->id_no_alvo);
                if (vizinhoIdx != -1) {
                    No* vizinho = lista_adj[vizinhoIdx];
                    visitados[vizinho->id] = true;
                    arvore->inserirNos(vizinho->id, vizinho->peso);
                    arvore->processarArestaIda(atual->id, vizinho->id,
                        arvore->in_ponderado_aresta ? aresta->peso : -1);
                    pilha.push(vizinho);
                }
            }
        }
    }
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

void Grafo::imprimirFormato() {
    cout << this->in_direcionado << " " << this->in_ponderado_aresta << " " << this->in_ponderado_vertice << endl;
    cout << this->lista_adj.size() << endl; //arruma impressão
    cout << "Lista de Adjacencias: " << endl;
    for (int i = 0; i < lista_adj.size(); i++) {
        if (lista_adj[i] != nullptr)
            this->lista_adj[i]->imprimeFormato(this->in_ponderado_aresta);
    }
}