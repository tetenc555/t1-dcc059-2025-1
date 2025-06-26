#include "Grafo.h"

#include <list>
#include <unordered_set>

Grafo::Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice, int ordem) { //COMPLEXIDADE N2! TENTAR AJUSTAR!
    //MOTIVOS: CRIACAO ARESTA / CRIACAO LKISTA VERTICE. UNICOS MOMENTOS N2 ATE A IMPRESSAO SIMPLES.
    this->in_direcionado = direcionado;
    this->in_ponderado_aresta= ehPondAresta;
    this->in_ponderado_vertice= ehPondVertice;
    this->ordem=ordem;

    //insercao de nos
    for (int i = 0; i < ordem; i++) { //ouve ordem vezes
        char id_add_no;
        cin >> id_add_no; //escuta id do no
        inserirNos(id_add_no); //adiciona no
    }

    //insercao de arestas
    while (true) { //ouve ate o break acionado pelo espaco
        char idNoOrigem;
        cin.ignore();
        cin.get(idNoOrigem); //define no de origem - necessario usar cin.get p ouvir espaco
        while (idNoOrigem == ' ') {
            cin.get(idNoOrigem); //verificacao para no caso de ouvir o caractere espaco, ouvir ate o proximo
        }
        if (idNoOrigem == '\n') //quebra quando ouve enter
            break;
        char idAlvoAresta;
        cin>>idAlvoAresta; //define no alvo
        int pesoAresta=0;
        if (in_ponderado_aresta) {
            cin >> pesoAresta; //define peso da aresta caso seja ponderado
        }

        this->processarArestaIda(idNoOrigem,idAlvoAresta,pesoAresta); //adiciona aresta de ida

        if (!direcionado && (idNoOrigem != idAlvoAresta)){
            this->processarArestaVolta(idAlvoAresta, idNoOrigem, pesoAresta); //adiciona aresta de volta caso nao seja loop e nao seja direcionado
        }
    }

    //criacao da lista de arestas
    this->lista_arestas = new listaArestas(this->lista_adj);
}

Grafo::~Grafo() {
}

void Grafo::inserirNos(int id) {
    No* addNo = new No(id, this->in_ponderado_vertice); //cria um novo no com id e peso (caso seja necessario)
    this->lista_adj.push_back(addNo); //adiciona na lista de adjacencias
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
    vector <char> retorno;
    for (tuple conexao: this->lista_arestas->conexoes) {
        if (get<1>(conexao) == id_no)
            retorno.push_back(get<0>(conexao));
    }

    // IMPRRESSAO PEA TESTES REMOVER DEPOIS
    for (int i=0; i<int(retorno.size()); i++) {
        cout << retorno[i] << " ";
    }
    cout << endl;
    // apagar ate aqui

    return retorno;
}

/*bool Grafo::verificaSeChega(No* origem, char idDestino, unordered_set<char> NosPercorridos) { //funcao que verifica se um no Origem chega a um no de Destino
    if (origem -> id == idDestino)
        return false;

    if (origem->arestas.empty())
        return false;

    for (auto aresta:origem->arestas) {
        if (aresta->id_no_alvo == idDestino) {
            return true;
        }
        if (!NosPercorridos.count(origem->id)) {
            int indiceProx = this->encontraIndiceNo(aresta->id_no_alvo);
            No* proxOrigem = lista_adj[indiceProx];
            NosPercorridos.insert(origem->id);
            if (verificaSeChega(proxOrigem ,idDestino,NosPercorridos))
                return true;
        }
    }
    return false;
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    if (!this->in_direcionado) {
        cout<<"Nao é direcionado!"<<endl;
        return {};
    }
    vector<char> retorno; //cria vetor p retorno
    for (int i=0; i< int (this->lista_adj.size()); i++) { //verifica para cada item
        No* origem=this->lista_adj[i]; // define o no "origem" para verificacao e adicao caso seja verdadeiro
        unordered_set<char> NosPercorridos;
        if (origem->id != id_no && verificaSeChega(origem,id_no,NosPercorridos)) // nao faz a verificao para o no em si, e faz processamento se o no tiver caminho para o id_no
            retorno.push_back(origem->id); //adiciona no a lista de retorno
    }


    // IMPRRESSAO PEA TESTES REMOVER DEPOIS
    for (int i=0; i<int(retorno.size()); i++) {
        cout << retorno[i] << " ";
    }
    cout << endl;
    // apagar ate aqui

    return retorno; //faz retorno do fecho transitivo indireto, apos processamento
}*/

bool vetorContemChar(vector<char> vetorChar,char item) {
    for (int i=0; i < int(vetorChar.size()); i++) {
        if (vetorChar[i] == item)
            return true;
    }
    return false;
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    if (!this->in_direcionado) {
        cout<<"Nao é direcionado!"<<endl;
        return {};
    }

    unordered_set<char> calculoRetorno; //cria unorderedSet ao inves de retorno a fim de melhorar processamento
    queue<char> filaProcessamento; //cria fila em que sempre teremos o proximo item
    //ISSO E IMPORTANTE POIS FOI A MELHOR MANEIRA DE GARANTIR QUE ELE QUEBRE APENAS QUANDO NAO HOUVER MAIS CONEXOES A SEREM PROCESSADAS! (

    // Inicia com o no final! Ele é o destino final, ou seja, o primeiro no caminhamento contrario.
    filaProcessamento.push(id_no);

    while (!filaProcessamento.empty()){ // enquanto a fila nao tiver vazia, processa o proximo item
        char processando=filaProcessamento.front(); //define o destino a ser processado
        filaProcessamento.pop(); //remove ele da fila. Assim mantemos nenhum item na fila durante processamento, e salvamos apenas se encontrar outro a processar
        //Isto garante que o while quebre corretamente (caso nao ache mais vertices a serem processados)
        for (tuple conexao: this->lista_arestas->conexoes) {
            char origemAresta = get<0>(conexao);
            char destinoAresta = get<1>(conexao);

            if (destinoAresta == processando) {
                if (calculoRetorno.find(origemAresta) == calculoRetorno.end()) { //MOTIVO PRINCIPAL DE USAR UNORDERED SET! -> verificacao se a origem ja foi registrada
                    //vi no stackoverflow que assim o processamento e menor, e resolve o problema de ter que usar +1 lista de arestas (jaPassou anterior) pra essa verificação
                    calculoRetorno.insert(origemAresta); //insere origem como retorno valido
                    filaProcessamento.push(origemAresta); //define origem como proximo destino valido p ser processsado
                }
            }
        }
    }
    calculoRetorno.erase(id_no); //remove no em si - ele aparece em caso de loop ou ciclo.
    vector<char> retorno(calculoRetorno.begin(), calculoRetorno.end());
    // IMPRRESSAO PEA TESTES REMOVER DEPOIS
    for (int i=0; i<int(retorno.size()); i++) {
        cout << retorno[i] << " ";
    }
    cout << endl;
    // apagar ate aqui

    return retorno;

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