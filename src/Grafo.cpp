#include "Grafo.h"

#include <list>
#include <unordered_set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <climits>

Grafo::Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice) { //COMPLEXIDADE N2! TENTAR AJUSTAR!
    //MOTIVOS: CRIACAO ARESTA / CRIACAO LKISTA VERTICE.
    this->in_direcionado = direcionado;
    this->in_ponderado_aresta= ehPondAresta;
    this->in_ponderado_vertice= ehPondVertice;
    this->ordem = 0;
}

Grafo::Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice, int ordem) { //COMPLEXIDADE N2! TENTAR AJUSTAR!
    //MOTIVOS: CRIACAO ARESTA / CRIACAO LKISTA VERTICE.
    this->in_direcionado = direcionado;
    this->in_ponderado_aresta= ehPondAresta;
    this->in_ponderado_vertice= ehPondVertice;
    this->ordem=ordem;
}

Grafo::~Grafo() {
    delete this->lista_arestas;
    for (No* n : this->lista_adj) {
        delete n;
    }
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

int Grafo::encontraIndiceNo(const char idNo) {
    int indice=-1; //valor inicial -1 p verificacao
    for (int j = 0; j < int(lista_adj.size()); j++) {
        if (this->lista_adj[j]->id == idNo) {
            indice=j; //encontra indice
            break;
        }
    }
    return indice; //retorna indice valido ou -1 caso no nao exista !
}

bool Grafo::verificaExistenciaNo(const char idNo) {
    for (int i=0; i < int(lista_adj.size()); i++) { //percorre todos itens
        if (this->lista_adj[i]->id == idNo) {
            return true; //se achar no retorna true e para o for
        }
    }
    return false; //se nao achar ao fim do for retorna false
}

void Grafo::processarArestaIda(const char idOrigem, const char idAlvoAresta,const int peso) {
    if (!(verificaExistenciaNo(idOrigem) && verificaExistenciaNo(idAlvoAresta))) { // se o no for invalido, quebra e nao processa a aresta
        cout << "Erro! No invalido na aresta! Nao adicionada, tente novamente" << endl; //imprime mensagem de erro;
        return; //retorna sem adicionar aresta
    }
    const int indice = encontraIndiceNo(idOrigem); //busca indice
    lista_adj[indice]->criaAresta(idAlvoAresta); //cria aresta

    if (this->in_ponderado_aresta) {
        this->lista_adj[indice]->arestas.back()->peso=peso; //adiciona peso caso seja ponderado
    }
}

void Grafo::processarArestaVolta(char idAlvo, char idOrigem, int peso) { //praticamente o contrario de processar Aresta Ida
    if (!(verificaExistenciaNo(idOrigem) && verificaExistenciaNo(idAlvo))) { // se o no for invalido, quebra e nao processa a aresta
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
    for (auto conexao: this->lista_arestas->conexoes) {
        if (get<1>(conexao) == id_no)
            retorno.push_back(get<0>(conexao));
    }
    return retorno;
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    unordered_set<char> calculoRetorno; //cria unorderedSet ao inves de retorno a fim de melhorar processamento
    queue<char> filaProcessamento; //cria fila em que sempre teremos o proximo item
    //A FILA E IMPORTANTE POIS FOI A MELHOR MANEIRA DE GARANTIR QUE ELE QUEBRE APENAS QUANDO NAO HOUVER MAIS CONEXOES A SEREM PROCESSADAS!


    filaProcessamento.push(id_no); // Inicia com o no final! Ele é o destino final, ou seja, o primeiro no ""caminhamento contrario"".

    while (!filaProcessamento.empty()){ // enquanto a fila nao tiver vazia, processa o proximo item

        char processando=filaProcessamento.front(); //define o destino a ser processado (ele vai voltando)
        filaProcessamento.pop(); //remove ele da fila. //Assim mantemos nenhum item na fila durante processamento, e salvamos apenas se encontrar outro a processar
        //Isto garante que o while quebre corretamente (caso nao ache mais vertices a serem processados) -> ISSO TAVA SENDO O MAIOR PROBLEMA EM CICLOS! causado pela ordem formada pela lista de arestas.

        for (auto conexao: this->lista_arestas->conexoes) { //pra cada processamento olhamos todas as conexoes
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
    vector<char> caminhoFinal; //vector p armazenar os vertices do caminho min
    unordered_map<char, int> verticeIndice;
    unordered_map<int, char> indiceVertice;
    for (int i = 0; i < (int)lista_adj.size(); ++i){
        verticeIndice[lista_adj[i]->id] = i; //com unordered relaciona vertice c id
        indiceVertice[i] = lista_adj[i]->id; //com unordered realciona indice c vertice
    }

    //declara os vertices dos parametros como inteiros
    int origem = verticeIndice[id_no_a];
    int destino = verticeIndice[id_no_b];

    int n = int(lista_adj.size());

    vector<int> pesoCaminho(n, numeric_limits<int>::max()); //marca os pesos do caminho
    vector<int> pai(n, -1); //marca o caminho de volta
    vector<bool> visitado(n, false); // marca os nós visitados
    pesoCaminho[origem] = 0;

    //uma queue com priority de minima
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> fila;
    fila.emplace(0, origem);

    //algoritmo
    while (!fila.empty()){
        int u = fila.top().second; //pega o menor nó
        fila.pop();//tira da fila

        //marca como visitado
        if (visitado[u]) continue;
        visitado[u] = true;

        //declraçao do nó atual para rodar a partir dele(o menor atual da fila
        No* noAtual = lista_adj[u];

        //itera por arestas reproduzindo a tabela feita em sala
        for (Aresta* aresta : noAtual->arestas) {
            int v = verticeIndice[aresta->id_no_alvo]; //indice do vertice alvo
            int peso = (in_ponderado_aresta ? aresta->peso : 1); //se não for ponderado, peso = 1

            if ((pesoCaminho[u]+peso) < pesoCaminho[v]) {
                pesoCaminho[v] = pesoCaminho[u] + peso;
                pai[v] = u;
                fila.emplace(pesoCaminho[v], v);
            }
        }
    }

    //se nao achar retorna o q tem
    if (pesoCaminho[destino] == numeric_limits<int>::max()) {
        cout << "Não existe caminho entre " << id_no_a << " e " << id_no_b << endl;
        return caminhoFinal;
    }

    //armazena o caminho numa stack
    stack<char> pilha_caminho;
    for (int v = destino; v != -1; v = pai[v]) {
        pilha_caminho.push(indiceVertice[v]);
    }
    //passa a stack pra vector caminhoFinal
    while (!pilha_caminho.empty()) {
        caminhoFinal.push_back(pilha_caminho.top());
        pilha_caminho.pop();
    }

    return caminhoFinal;
}

vector<char> Grafo::caminho_minimo_floyd(char id_no_a, char id_no_b) {


    // execução 1x
    if (!floydPronto) {
        // Inicializa estruturas
        for (int i = 0; i < ordem; i++) {
            indiceNos[lista_adj[i]->id] = i;
        }

        distFloyd.resize(ordem, vector<int>(ordem, INT_MAX));
        proxNo.resize(ordem, vector<int>(ordem, -1));

        // preenche matrizes iniciais
        for (int i = 0; i < ordem; i++) {
            distFloyd[i][i] = 0;
            for (Aresta* ar : lista_adj[i]->arestas) {
                int j = indiceNos[ar->id_no_alvo];
                distFloyd[i][j] = ar->peso;
                proxNo[i][j] = j;

                if (!in_direcionado) {
                    distFloyd[j][i] = ar->peso;
                    proxNo[j][i] = i;
                }
            }
        }

        // cmf
        for (int k = 0; k < ordem; k++) {
            for (int i = 0; i < ordem; i++) {
                for (int j = 0; j < ordem; j++) {
                    if (distFloyd[i][k] != INT_MAX &&
                        distFloyd[k][j] != INT_MAX &&
                        distFloyd[i][j] > distFloyd[i][k] + distFloyd[k][j]) {

                        distFloyd[i][j] = distFloyd[i][k] + distFloyd[k][j];
                        proxNo[i][j] = proxNo[i][k];
                    }
                }
            }
        }
        floydPronto = true;
    }

    // reconstrução do caminho
    int origem = indiceNos[id_no_a];
    int destino = indiceNos[id_no_b];

    if (proxNo[origem][destino] == -1) {
        cout << "Não existe caminho entre " << id_no_a << " e " << id_no_b << endl;
        return {};
    }

    vector<char> caminho;
    caminho.push_back(id_no_a);

    int atual = origem;
    while (atual != destino) {
        atual = proxNo[atual][destino];
        caminho.push_back(lista_adj[atual]->id);
    }

    return caminho;
}

Grafo * Grafo::criaSubGrafoVerticeInduzido(const vector <char>& ids_nos) {
    auto* subGrafo = new Grafo(this->in_direcionado, this->in_ponderado_aresta, this->in_ponderado_vertice); // gera grafo inical
    for (char id : ids_nos) { // percorre cada id para copiar nos
        int indice = this->encontraIndiceNo(id); // encontra indice
        if (indice == -1) { //verifica se achou
            cout << "No de ID:" << id << " nao encontrado! Pulamos este." << endl;
        }
        else {
            subGrafo->lista_adj.push_back(new No(this->lista_adj[indice])); // adiciona no com sua arestas na lista
        }
    }
    for (No* no : subGrafo->lista_adj) { //deletaremos agor aarestas com alvos que nao existem
        for (int i=(int(no->arestas.size()) - 1); i>=0 ; i--) {  //para evitar erros com erase, que encurta o vetor e quebra a deletacao correta, iteramos ao contrario
            if (!subGrafo->verificaExistenciaNo(no->arestas[i]->id_no_alvo)) { // se id alvo nao existir no grafo, deleta!
                no->arestas.erase(no->arestas.begin() + i); //remove aresta
            }
        }
    }
    subGrafo->criaListaArestas(); //cria lista de arestas
    subGrafo->ordem = int(subGrafo->lista_adj.size()); //define ordem
    //assim o subgrafo esta completo.
    return subGrafo;
}

Grafo * Grafo::arvore_geradora_minima_prim(const vector<char>& ids_nos) {
    //Primeiro passo: gerar subgrafo
    Grafo* Inicial = criaSubGrafoVerticeInduzido(ids_nos);

    //Segundo passo: inicializa fila com o primeiro no e grafo de retorno
    priority_queue<tuple<int, char, char>, vector<tuple<int, char, char>>, greater<>> fila;
    unordered_set<char> visitados;

    char idInicial = Inicial->lista_adj[0]->id; //define no inicial como o primeiro da lista (provalvemnte alterar p cin de4pois)
    visitados.insert(idInicial); //insere raiz como visitado
    for (Aresta* a : Inicial->lista_adj[0]->arestas) {
        fila.emplace(a->peso, idInicial, a->id_no_alvo); //define primeiros processamentos como arestas da raiz
    }
    vector<tuple<char,char,int>> nosProcessados; //salvar arestas que serao usadas para ser copiadas depois

    //Terceiro passo: Processamento de nós
    while (!fila.empty()) { //processamento enquanto nao tiver vazio
        //salva cada variavel a ser usada baseada no item de menor peso
        int peso = get<0>(fila.top()); 
        char origem = get<1>(fila.top()); 
        char destino = get<2>(fila.top()); 
        fila.pop(); //e depois o remove da fila

        // verifica se ja esta no MST
        if (visitados.count(destino))
            continue; //caso esteja, pula pra prox interacao

        //processamento em si    
        visitados.insert(destino); //salva que foi visitado
        nosProcessados.emplace_back(origem, destino, peso); //salva aresta como valida

        //acha indice no inicial para que possamos achar proximos vertices
        int indice = Inicial->encontraIndiceNo(destino);
        //verifica se encontrou indice na arvore inicial
        if (indice == -1)
            continue; //caso nao esteja e erro e pula prqa prox interacao. apenas uma medida de segurança

        No* noAtual = Inicial->lista_adj[indice]; //define o no atual como o destino determinado
        for (Aresta* a : noAtual->arestas) {
            if (!visitados.count(a->id_no_alvo)) { //garante que so salva se nao tiver sido visitado
                fila.emplace(a->peso, destino, a->id_no_alvo); //salva cada aresta dele para proximo processamento, a fila fica encarregada de organizar os pesos
            }
        }
    }

    //copia arestas definidas como certas para o grafo retorno
    auto * retorno = new Grafo(Inicial->in_direcionado, Inicial->in_ponderado_aresta, false); //define sem peso nos vertices
    for (auto item : nosProcessados) {
        char idOrigem = get<0>(item);
        char idAlvo = get<1>(item);
        int peso = get<2>(item);
        //cria nos se nao existirem
        if (!retorno->verificaExistenciaNo(idOrigem))
            retorno->inserirNos(idOrigem,-1);
        if (!retorno->verificaExistenciaNo(idAlvo))
            retorno->inserirNos(idAlvo,-1);
        //salva aresta
        retorno->processarArestaIda(idOrigem,idAlvo,peso);
        retorno->processarArestaVolta(idAlvo,idOrigem,peso);
    }
    //cria lista de arestas apos processamento
    retorno->criaListaArestas();
    delete Inicial;
    return retorno; //retorna arvore gerada
}

char Grafo::find(char x) {
    if (pais[x] != x)
        pais[x] = find(pais[x]); // Path compression
    return pais[x];
}

void Grafo::union_sets(char a, char b) {
    a = find(a);
    b = find(b);
    if (a != b)
        pais[b] = a;
}

Grafo * Grafo::arvore_geradora_minima_kruskal(const vector<char>& ids_nos)
{
    //Primeiro passo: gerar subgrafo e fazer condicoes
    Grafo* grafoInicial = criaSubGrafoVerticeInduzido(ids_nos);

    //Segundo passo: armazenar todas as arestas
    grafoInicial->pais.clear();
    for (No* no : grafoInicial->lista_adj) {
        grafoInicial->pais[no->id] = no->id;
    }

    //ordena arestas por peso
    vector<tuple<int, char, char>> arestasOrdenadas;
    unordered_set<string> arestasInseridas;

    //algoritmo principal
    for (No* no : grafoInicial->lista_adj) {
        char u = no->id;
        for (Aresta* a : no->arestas) {
            char v = a->id_no_alvo;
            int peso = a->peso;
            //evitar duplicata
            string chave = u < v ? string{u, v} : string{v, u};
            if (arestasInseridas.find(chave) == arestasInseridas.end()) {
                arestasOrdenadas.emplace_back(peso, u, v);
                arestasInseridas.insert(chave);
            }
        }
    }

    sort(arestasOrdenadas.begin(), arestasOrdenadas.end());

    //Ultimo passo: crIar grafo de retonro
    auto * retorno = new Grafo(false, grafoInicial->in_ponderado_aresta, false); //define sem peso nos vertices

    for (No* no : grafoInicial->lista_adj) {
        retorno->inserirNos(no->id, -1);
    }

    for (auto& aresta : arestasOrdenadas) {
        int peso = get<0>(aresta);
        char u = get<1>(aresta);
        char v = get<2>(aresta);

        if (grafoInicial->find(u) != grafoInicial->find(v)) {
            grafoInicial->union_sets(u, v);
            retorno->processarArestaIda(u, v, peso);
            retorno->processarArestaVolta(v, u, peso);
        }
    }
    //cria lista de arestas apos processamento
    retorno->criaListaArestas();
    return retorno; //retorna arvore gerada
}

Grafo * Grafo::arvore_caminhamento_profundidade(char id_no) {
    //Verifica se o no inicial existe
    int indiceInicial = encontraIndiceNo(id_no);
    if (indiceInicial == -1) {
        cout << "No inicial nao encontrado!" << endl;
        return nullptr;
    }

    //Cria grafo para arvore de busca por profundidade
    auto* arvore = new Grafo(true, this->in_ponderado_aresta, this->in_ponderado_vertice);

    //Marca nós como não visitados (caso seja alterado por outro metodo)
    for (auto no: lista_adj) {
        no->setVisitado(false);
    }

    //Chama a função auxiliar iterativa para construir a arvore
    buscaProfundidadeAux(lista_adj[indiceInicial], arvore);
    arvore->ordem = int(lista_adj.size()); //altera a ordem da arvore
    return arvore;
}

void Grafo::buscaProfundidadeAux(No* atual, Grafo* arvore) {
    if (!atual) return;

    stack<No*> pilha;
    unordered_map<char, bool> visitados;

    pilha.push(atual);
    visitados[atual->id] = true;
    arvore->inserirNos(atual->id, atual->peso);

    while (!pilha.empty()) {
        atual = pilha.top();
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

// Calcula a matriz de distâncias mínimas entre todos os pares de vértices do grafo
vector<vector<int>> Grafo::calcularMatrizDistancias() {
    // Inicializa matriz de distâncias com valores infinitos (INT_MAX)
    vector<vector<int>> distancias(ordem, vector<int>(ordem, INT_MAX));

    // A distância de um vértice para ele mesmo é sempre 0
    for (int i = 0; i < ordem; i++) {
        distancias[i][i] = 0;
    }

    // Calcula distâncias mínimas entre todos os pares de vértices
    for (int i = 0; i < ordem; i++) {
        char origem = lista_adj[i]->id; // Vértice de origem

        for (int j = 0; j < ordem; j++) {
            if (i == j) continue; // Pula a diagonal principal (já definida como 0)

            char destino = lista_adj[j]->id; // Vértice de destino

            // Obtém o caminho mínimo entre origem e destino usando Dijkstra
            vector<char> caminho = caminho_minimo_dijkstra(origem, destino);

            if (!caminho.empty()) { // Se existe caminho entre os vértices
                // Calcula a distância total somando os pesos das arestas do caminho
                int distancia = 0;
                for (int k = 0; k < (int)caminho.size() - 1; k++) {
                    int idxAtual = encontraIndiceNo(caminho[k]);

                    // Procura a aresta que leva ao próximo vértice no caminho
                    for (Aresta* ar : lista_adj[idxAtual]->arestas) {
                        if (ar->id_no_alvo == caminho[k+1]) {
                            // Soma o peso da aresta (1 se grafo não ponderado)
                            distancia += (in_ponderado_aresta ? ar->peso : 1);
                            break;
                        }
                    }
                }
                distancias[i][j] = distancia; // Armazena a distância calculada
            }
            // Se não houver caminho, mantém INT_MAX (infinito)
        }
    }

    return distancias; // Retorna a matriz de distâncias completas
}

// Calcula a excentricidade de cada vértice do grafo
vector<int> Grafo::calcularExcentricidades() {
    // Obtém a matriz de distâncias mínimas entre todos os pares de vértices
    const vector<vector<int>> distancias = calcularMatrizDistancias();
    vector<int> excentricidades(ordem); // Vetor para armazenar as excentricidades

    // Para cada vértice no grafo...
    for (int i = 0; i < ordem; i++) {
        int max_dist = -1; // Inicializa a maior distância encontrada

        // Procura a maior distância a partir do vértice i (excentricidade)
        for (int dist : distancias[i]) {
            // Considera apenas distâncias válidas (diferentes de infinito)
            if (dist != INT_MAX && dist > max_dist) {
                max_dist = dist;
            }
        }

        // Se não encontrou nenhuma distância válida (vértice isolado), excentricidade = 0
        // Caso contrário, armazena a maior distância encontrada
        excentricidades[i] = (max_dist == -1) ? 0 : max_dist;
    }

    return excentricidades; // Retorna o vetor de excentricidades
}

int Grafo::raio(const vector <int> &excentricidade) {
    int menor = excentricidade[0];
    for (int e : excentricidade) {
        if (e < menor)
            menor = e;
    }
    return menor;
}

int Grafo::diametro(const vector <int> &excentricidade) {
    int maior = excentricidade[0];
    for (int e : excentricidade) {
        if (e > maior)
            maior = e;
    }
    return maior;
}

vector<char> Grafo::calculoCentroPeriferia(const vector <int>& excentricidade, int valorComparar) { //juntei as duas funcoes pois o processamento e o mesmo, mudando o parametro jogado
    vector<char> retorno;
    for (int i=0; i<(int(excentricidade.size()));i++) {
        if (excentricidade[i]==valorComparar)
            retorno.push_back(this->lista_adj[i]->id);
    }
    return retorno;
}

/*
vector<char> Grafo::vertices_de_articulacao(vector <int> excentricidade) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}
*/

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
    for (int i = 0; i < int(lista_adj.size()); i++) {
        if (lista_adj[i] != nullptr)
            this->lista_adj[i]->imprimeFormato(this->in_ponderado_aresta);
    }
}

    void Grafo::impressaoFinal() {
        cout << this->in_direcionado << " " << this->in_ponderado_aresta << " " << this->in_ponderado_vertice << endl;
        cout << this->lista_adj.size() << endl; //arruma impressão
        for (int i = 0; i < int(lista_adj.size()); i++) {
            if (lista_adj[i] != nullptr) {
                this->lista_adj[i]->impressaoFinal();
            }
        }
    }


