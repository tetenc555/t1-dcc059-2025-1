#include "ProcessarInstancias.hpp"
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include "LeituraArquivos.h"
#include "MinWeightDominatingSet.h"

using namespace std;
using namespace chrono;

// Função para calcular o peso total do conjunto dominante
float calcularPeso(MinWeightDominatingSet* conjunto) {
    float peso = 0.0f;
    // Soma os pesos de todos os nós marcados como dominantes
    for (No* no : conjunto->conjuntoSolucao->lista_adj) {
        if (no->isDominante) {
            peso += no->peso;
        }
    }
    return peso;
}

// Executa o algoritmo guloso randomizado múltiplas vezes e retorna o melhor resultado e tempo médio
tuple<float, double> executarGulosoRandomizado(Grafo* grafo, float alpha, int numExecucoes, int numAlgoritmoRandExec) {
    float melhorResultado = numeric_limits<float>::max();
    double tempoTotal = 0.0;

    // Executa o algoritmo um numero determinado de vezes
    for (int i = 0; i < numExecucoes; i++) {
        auto inicio = high_resolution_clock::now(); //pega o tempo inical
        float melhorExecucao = numeric_limits<float>::max();

        // Executa o Algoritmo Randomizado várias vezes para encontrar a melhor solução nesta execução
        for (int j = 0; j < numAlgoritmoRandExec; j++) {
            auto* setRand = new MinWeightDominatingSet(grafo, 1, alpha);
            float peso = calcularPeso(setRand);
            if (peso < melhorExecucao) melhorExecucao = peso;
            delete setRand;
        }

        auto fim = high_resolution_clock::now(); //pega o tempo final
        tempoTotal += duration_cast<milliseconds>(fim - inicio).count(); //calcula o tempo total
        if (melhorExecucao < melhorResultado) melhorResultado = melhorExecucao; //substitui o valor do melhor
    }

    // Retorna o melhor resultado encontrado e o tempo médio de execução
    return make_tuple(melhorResultado, tempoTotal / numExecucoes);
}

tuple<float, double> executarGulosoAdaptativo(Grafo* grafo, int numExecucoes) {
    float melhorResultado = numeric_limits<float>::max();
    double tempoTotal = 0.0;

    for (int i = 0; i < numExecucoes; i++) {
        auto inicio = high_resolution_clock::now();
        
        auto* setAdapt = new MinWeightDominatingSet(grafo, 2); // 2 para adaptativo reativo
        float peso = calcularPeso(setAdapt);
        if (peso < melhorResultado) melhorResultado = peso;
        
        auto fim = high_resolution_clock::now();
        tempoTotal += duration_cast<milliseconds>(fim - inicio).count();
        delete setAdapt;
    }

    return make_tuple(melhorResultado, tempoTotal / numExecucoes);
}


// Função principal que processa todas as instâncias e gera a tabela comparativa
void processarInstanciasComparativo(const string& arquivoLista) {
    // Constantes para configuração do experimento
    const int NUM_EXECUCOES = 10;       // Número de execuções para cada algoritmo
    const int NUM_ALGRANDEXECUCOES = 30;    // Número de execuções do Randomizado (contando com as 10 iniciais)

    // Abre o arquivo com a lista de instâncias
    ifstream arquivo(arquivoLista);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo de instâncias: " << arquivoLista << endl;
        return;
    }

    vector<ResultadoInstancia> resultados;  // Armazena os resultados de cada instância no vetor da Struct de Resultados
    string nomeArquivo;

    // Processa cada linha do arquivo (cada instância)
    while (getline(arquivo, nomeArquivo)) {
        if (nomeArquivo.empty()) continue;

        string caminhoCompleto = "./input/" + nomeArquivo;

        try {
            ResultadoInstancia resultado;
            resultado.nome = nomeArquivo;

            // Extrai o número de vértices do nome do arquivo
            size_t inicio_n = nomeArquivo.find('_') + 1;
            size_t fim_n = nomeArquivo.find('_', inicio_n);
            resultado.numVertices = stoi(nomeArquivo.substr(inicio_n, fim_n - inicio_n));

            // Carrega o grafo a partir do arquivo
            Grafo* grafo = LeituraArquivos::lerGrafodoArquivo(caminhoCompleto);

            // 1. Executa o algoritmo Guloso tradicional (tempo em nanossegundos)
            float melhorGuloso = numeric_limits<float>::max();
            double tempoGuloso = 0.0;

            for (int i = 0; i < NUM_EXECUCOES; i++) {
                auto inicio = high_resolution_clock::now(); //pega o tempo inicial
                auto* setGuloso = new MinWeightDominatingSet(grafo, 0);  // 0 para guloso tradicional
                float peso = calcularPeso(setGuloso);
                auto fim = high_resolution_clock::now(); //pega o tempo final

                tempoGuloso += duration_cast<nanoseconds>(fim - inicio).count(); //calcula o tempo total de duração da execucao
                if (peso < melhorGuloso) melhorGuloso = peso; //altera o melhor resultado
                delete setGuloso;
            }

            resultado.guloso = melhorGuloso;
            resultado.guloso_tempo = tempoGuloso / NUM_EXECUCOES;

            // 2. Executa as versões randomizadas com diferentes alphas (tempo em milissegundos)
            auto [melhorAlpha02, tempoAlpha02] = executarGulosoRandomizado(grafo, 0.2f, NUM_EXECUCOES, NUM_ALGRANDEXECUCOES);
            resultado.randomizadoAlpha02 = melhorAlpha02;
            resultado.randomizadoAlpha02_tempo = tempoAlpha02;

            auto [melhorAlpha03, tempoAlpha03] = executarGulosoRandomizado(grafo, 0.3f, NUM_EXECUCOES, NUM_ALGRANDEXECUCOES);
            resultado.randomizadoAlpha03 = melhorAlpha03;
            resultado.randomizadoAlpha03_tempo = tempoAlpha03;

            auto [melhorAlpha04, tempoAlpha04] = executarGulosoRandomizado(grafo, 0.4f, NUM_EXECUCOES, NUM_ALGRANDEXECUCOES);
            resultado.randomizadoAlpha04 = melhorAlpha04;
            resultado.randomizadoAlpha04_tempo = tempoAlpha04;

            // 3. Algoritmo adaptativo reativo
            auto [melhorAdaptativo, tempoAdaptativo] = executarGulosoAdaptativo(grafo, NUM_EXECUCOES);
            resultado.adaptativo = melhorAdaptativo;
            resultado.adaptativo_tempo = tempoAdaptativo;

            // Determina a melhor solução
            resultado.bestSolucao = min({
                resultado.guloso,
                resultado.randomizadoAlpha02,
                resultado.randomizadoAlpha03,
                resultado.randomizadoAlpha04,
                resultado.adaptativo
            });

            // Armazena os resultados e libera memória
            resultados.push_back(resultado);
            delete grafo;

            // Exibe progresso
            cout << fixed << setprecision(2);
            cout << "Processado: " << nomeArquivo << " | Tempo Guloso: " << resultado.guloso_tempo << " ns" << endl;
            cout << defaultfloat;

        } catch (const exception& e) {
            cerr << "Erro ao processar " << nomeArquivo << ": " << e.what() << endl;
        }
    }

    arquivo.close();

    // Gera o arquivo CSV com os resultados comparativos
    ofstream arquivoSaida("./output/tabela_comparativa.csv");
    if (!arquivoSaida.is_open()) {
        cerr << "Erro ao criar arquivo de saída." << endl;
        return;
    }

    // Configura formatação numérica
    arquivoSaida << fixed << setprecision(2);

    // Escreve cabeçalho do CSV
    arquivoSaida << "Instancia,Vertices,MelhorSolucao,"
                 << "Guloso_Melhor,Guloso_Tempo(ns),"
                 << "Rand02_Melhor,Rand02_Tempo(ms),"
                 << "Rand03_Melhor,Rand03_Tempo(ms),"
                 << "Rand04_Melhor,Rand04_Tempo(ms),"
                 << "Adaptativo_Melhor,Adaptativo_Tempo(ms)\n";

    // Escreve os dados de cada instância
    for (const auto& res : resultados) {
        arquivoSaida << res.nome << ","
                     << res.numVertices << ","
                     << res.bestSolucao << ","
                     << res.guloso << "," << res.guloso_tempo << ","
                     << res.randomizadoAlpha02 << "," << res.randomizadoAlpha02_tempo << ","
                     << res.randomizadoAlpha03 << "," << res.randomizadoAlpha03_tempo << ","
                     << res.randomizadoAlpha04 << "," << res.randomizadoAlpha04_tempo << ","
                     << res.adaptativo << "," << res.adaptativo_tempo << "\n";
    }

    arquivoSaida.close();
    cout << fixed << setprecision(2);
    cout << "Processamento concluído. Resultados em ./output/tabela_comparativa.csv\n";
    cout << defaultfloat;
}