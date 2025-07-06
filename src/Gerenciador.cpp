#include "Gerenciador.h"
#include <fstream>
#include <algorithm>

#include "LeituraArquivos.h"

static Grafo* grafoAtual = nullptr;

void salvaFechoArquivo(const string& caminhoArquivo, const string& tipo, const char& id_no, const vector<char>& vetorImprimir) {
    ofstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao criar arquivo " + caminhoArquivo);
    }

    // Escreve cabeçalho (direcionado, ponderado aresta, ponderado vértice)
    arquivo << "Fecho transitivo " << tipo << " do Nó " << id_no << ": \n";

    // Escreve cada nó e suas adjacências
    for (char c: vetorImprimir){
        if (c!=vetorImprimir[0])
            arquivo << ",";
        arquivo << c;
    }
    arquivo << endl;
    arquivo.close();
}

void salvaCaminhoMinimoArquivo(const string& caminhoArquivo, const string& tipo, const char& id_no_1, const char& id_no_2, const vector<char>& vetorImprimir) {
    ofstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao criar arquivo " + caminhoArquivo);
    }

    // Escreve cabeçalho (direcionado, ponderado aresta, ponderado vértice)
    arquivo << "Caminho Minimo de "<< tipo << " do " << id_no_1 << " a " << id_no_2 << ": \n";

    // Escreve cada nó e suas adjacências
    for (char c: vetorImprimir) {
        if (c!=vetorImprimir[0])
            arquivo << ",";
        arquivo << c;
    }
    arquivo << endl;
    arquivo.close();
}

void imprimeFuncoesExcentricidadeTela(const int& raio, const int& diametro, const vector<char>& centro, const vector<char>& periferia) {
    cout << raio << endl;
    cout << diametro << endl;
    for (char a : centro) {
        if (a!=centro[0])
            cout << ",";
        cout << a;
    }
    cout << endl;
    for (char a : periferia) {
        if (a!=periferia[0])
            cout << ",";
        cout << a;
    }
    cout << endl;
}

void salvaFuncoesExcentricidadeArquivo(const int& raio, const int& diametro, const vector<char>& centro, const vector<char>& periferia) {
    ofstream arqExcentricidade("./output/raio_diametro_centro_periferia.txt");
    if (!arqExcentricidade.is_open()) {
        throw runtime_error("Erro ao criar arquivo ./output/raio_diametro_centro_periferia.txt");
    }

    arqExcentricidade << raio << endl;
    arqExcentricidade << diametro << endl;
    for (char a : centro) {
        if (a!=centro[0])
            arqExcentricidade << ",";
        arqExcentricidade << a;
    }
    arqExcentricidade << endl;
    for (char a : periferia) {
        if (a!=periferia[0])
            arqExcentricidade << ",";
        arqExcentricidade << a;
    }
}


void Gerenciador::comandos(Grafo* grafo) {
    grafoAtual = grafo;

    cout<<"Digite uma das opcoes abaixo e pressione enter:"<<endl<<endl;
    cout<<"(a) Fecho transitivo direto de um no;"<<endl;
    cout<<"(b) Fecho transitivo indireto de um no;"<<endl;
    cout<<"(c) Caminho minimo (Djikstra);"<<endl;
    cout<<"(d) Caminho minimo (Floyd);"<<endl;
    cout<<"(e) Arvore Geradora Minima (Algoritmo de Prim);"<<endl;
    cout<<"(f) Arvore Geradora Minima (Algoritmo de Kruskal);"<<endl;
    cout<<"(g) Arvore de caminhamento em profundidade;"<<endl;
    cout<<"(h) Raio, diametro, centro e periferia do grafo;"<<endl;
    cout<<"(j) Imprimir grafo;"<<endl;
    cout <<"(m) Alterar Arquivo de teste;" <<endl;
    cout<<"(0) Sair;"<<endl<<endl;

    char resp;
    cin >> resp;
    switch (resp) {
        case 'a': {

            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_direto = grafo->fecho_transitivo_direto(id_no);
            //metodo de impressao em tela
            cout << "Fecho transitivo direto do Nó " << id_no << ": " <<endl;
            for (char item : fecho_transitivo_direto) {
                if (item!=fecho_transitivo_direto[0])
                    cout << ",";
                cout << item;
            }
            cout << endl;

            if(pergunta_imprimir_arquivo("fecho_trans_dir.txt")) {
                salvaFechoArquivo("./output/fecho_trans_dir.txt","direto",id_no,fecho_transitivo_direto);
            }


            break;
        }

        case 'b':{

            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_indireto = grafo->fecho_transitivo_indireto(id_no);
            //metodo de impressao em tela
            cout << "Fecho transitivo indireto do Nó " << id_no << ": " <<endl;
            for (char item : fecho_transitivo_indireto) {
                if (item!=fecho_transitivo_indireto[0])
                    cout << ",";
                cout << item;
            }
            cout << endl;

            if(pergunta_imprimir_arquivo("fecho_trans_indir.txt")) {
                salvaFechoArquivo("./output/fecho_trans_indir.txt","indireto",id_no,fecho_transitivo_indireto);
            }

;
            break;
        }

        case 'c': {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_dijkstra = grafo->caminho_minimo_dijkstra(id_no_1,id_no_2);
            cout << "Caminho minimo de Dijkstra do " << id_no_1 << " a " << id_no_2 << ": "  << endl;
            for (char no: caminho_minimo_dijkstra) {
                if (no!=caminho_minimo_dijkstra[0])
                    cout << ",";
                cout << no;            }
            cout << endl;

            if(pergunta_imprimir_arquivo("caminho_minimo_dijkstra.txt")) {
                salvaCaminhoMinimoArquivo("./output/caminho_minimo_dijkstra.txt","Dijkstra",id_no_1,id_no_2,caminho_minimo_dijkstra);
            }


            break;
        }

        case 'd': {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_floyd = grafo->caminho_minimo_floyd(id_no_1,id_no_2);
            cout << "Caminho minimo de Floyd do " << id_no_1 << " a " << id_no_2 << ": "  << endl;
            for (char no: caminho_minimo_floyd) {
                if (no!=caminho_minimo_floyd[0])
                    cout << ",";
                cout << no;
            }
            cout << endl;

            if(pergunta_imprimir_arquivo("caminho_minimo_floyd.txt")) {
                salvaCaminhoMinimoArquivo("./output/caminho_minimo_floyd.txt","Floyd",id_no_1,id_no_2,caminho_minimo_floyd);
            }


            break;
        }
        case 'e': {

            int tam;
            cout<<"Digite o tamanho do subconjunto: ";
            cin>>tam;

            if(tam > 0 && tam <= grafo->ordem) {

                vector<char> ids = get_conjunto_ids(grafo,tam);
                Grafo* arvore_geradora_minima_prim = grafo->arvore_geradora_minima_prim(ids);
                arvore_geradora_minima_prim->impressaoFinal();

                if(pergunta_imprimir_arquivo("agm_prim.txt")) {
                    arvore_geradora_minima_prim->salvarGrafoEmArquivo("./output/agm_prim.txt");
                }

                delete arvore_geradora_minima_prim;

            }else {
                cout<<"Valor invalido"<<endl;
            }

            break;
        }

        case 'f': {

            int tam;
            cout<<"Digite o tamanho do subconjunto: ";
            cin>>tam;

            if(tam > 0 && tam <= grafo->ordem) {

                vector<char> ids = get_conjunto_ids(grafo,tam);
                Grafo* arvore_geradora_minima_kruskal = grafo->arvore_geradora_minima_kruskal(ids);
                arvore_geradora_minima_kruskal->impressaoFinal();

                if(pergunta_imprimir_arquivo("agm_kruskal.txt")) {
                    arvore_geradora_minima_kruskal->salvarGrafoEmArquivo("./output/agm_kruskal.txt");
                }

                delete arvore_geradora_minima_kruskal;

            }else {
                cout<<"Valor invalido"<<endl;
            }

            break;
        }

        case 'g': {

            char id_no = get_id_entrada();
            Grafo* arvore_caminhamento_profundidade = grafo->arvore_caminhamento_profundidade(id_no);
            arvore_caminhamento_profundidade->impressaoFinal();

            if(pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                arvore_caminhamento_profundidade->salvarGrafoEmArquivo("./output/arvore_caminhamento_profundidade.txt");
            }

            delete arvore_caminhamento_profundidade;
            break;
        }

        case 'h': {
            vector<int> excentricidades = grafo->calcularExcentricidades();
            int raio = grafo->raio(excentricidades);
            int diametro = grafo->diametro(excentricidades);
            vector<char> centro = grafo->calculoCentroPeriferia(excentricidades,raio);
            vector<char> periferia = grafo->calculoCentroPeriferia(excentricidades,diametro);
            //impressao
            imprimeFuncoesExcentricidadeTela(raio,diametro,centro,periferia);
            if(pergunta_imprimir_arquivo("raio_diametro_centro_periferia.txt")) {
                salvaFuncoesExcentricidadeArquivo(raio,diametro,centro,periferia);
            }

            break;
        }
        case 'j': {
            grafo->imprimirGrafo();
            cout<<endl;
            break;
        }
        case 'm': {
            string caminhoBase = "./input/";
            cout << "\nDigite o nome do novo arquivo de teste: ";
            string nomeArquivo;
            cin >> nomeArquivo;

            string caminhoCompleto = caminhoBase+nomeArquivo;

            ifstream arquivo(caminhoCompleto); //Verifica se o caminho existe
            if (!arquivo) {
                cerr<<"Arquivo nao existe, caminho não encontrado"<<endl;
                exit(1);
            }
            arquivo.close();

            try {
                cout << "Processando: " << caminhoCompleto << endl;
                Grafo* novoGrafo = LeituraArquivos::lerGrafodoArquivo(caminhoCompleto);
                delete grafoAtual;
                Gerenciador::comandos(novoGrafo);
            }catch (const exception& e) {
                cerr << "Erro ao carregar o arquivo: " << e.what() << endl;
                exit(1);
            }

            break;
        }
        case '0': {
            delete grafo;
            exit(0);
        }
        default: {
            cout<<"Opção inválida"<<endl;
        }
    }

    comandos(grafo);

}

char Gerenciador::get_id_entrada() {
    cout<<"Digite o id de um no: ";
    char id;
    cin>>id;
    cout<<endl;
    return id;
}

vector<char> Gerenciador::get_conjunto_ids(const Grafo *grafo, const int& tam) {
    vector<char> ids = {};
    while(static_cast<int>(ids.size()) < tam) {
        char id_no =get_id_entrada();
        bool existe = false;
        for(No* no: grafo->lista_adj){
            if(no->id == id_no){
                existe = true;
                break;
            }
        }

        if(!existe){
            cout<<"Vertice nao existe"<<endl;
        }else{
            if(find(ids.begin(), ids.end(),id_no) != ids.end()) {
                    cout<<"Valor repetido"<<endl;
            }else {
                ids.push_back(id_no);
            }
        }

    }

    return ids;
}


bool Gerenciador::pergunta_imprimir_arquivo(const string& nome_arquivo) {

    cout<<"Imprimir em arquivo externo? ("<<nome_arquivo<<")"<<endl;
    cout<<"(1) Sim;"<<endl;
    cout<<"(2) Nao."<<endl;
    int resp;
    cin>>resp;
    cout<<endl;

    switch (resp) {
        case 1:
            return true;
        case 2:
            return false;
        default:
            cout<<"Resposta invalida"<<endl;
            return pergunta_imprimir_arquivo(nome_arquivo);
    }
}

void Gerenciador::mudarArquivoTeste() {
    string caminhoBase = "./input/";
    cout << "\nDigite o nome do novo arquivo de teste: ";
    string nomeArquivo;
    getline(cin, nomeArquivo);

    string caminhoCompleto = caminhoBase+nomeArquivo;

    ifstream arquivo(caminhoCompleto); //Verifica se o caminho existe
    if (!arquivo) {
        cerr<<"Arquivo nao existe, caminho não encontrado"<<endl;
        exit(1);
    }
    arquivo.close();

    try {
        cout << "Processando: " << caminhoCompleto << endl;
        Grafo* novoGrafo = LeituraArquivos::lerGrafodoArquivo(caminhoCompleto);
        delete grafoAtual;
        Gerenciador::comandos(novoGrafo);
    }catch (const exception& e) {
        cerr << "Erro ao carregar o arquivo: " << e.what() << endl;
        exit(1);
    }
}