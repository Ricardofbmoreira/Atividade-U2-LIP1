#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#define nrepeticoes 1000

using namespace std;
void mostra_vetor(vector<int> vetor, int i)
{
    for (int j = 0; j < i; j++)
    {
        cout << vetor[j] << endl;
    }
    cout << endl;
}

int busca_rec(vector<int> vetor, int alvo, int ls, int ms)
{
    if (ls > ms)
    {
        return -1;
    }

    int meio = ls + (ms - ls) / 2;

    if (vetor[meio] == alvo)
    {
        return meio;
    }
    else if (vetor[meio] < alvo)
    {
        return busca_rec(vetor, alvo, meio + 1, ms);
    }
    else
    {
        return busca_rec(vetor, alvo, ls, meio - 1);
    }
}

int busca_linear(vector<int> vetor, int alvo)
{
    for (int i = 0; i < vetor.size(); i++)
    {
        if (vetor[i] == alvo)
        {
            return i;
        }
    }
    return -1;
}

void popular(vector<int> &vetor, int size)
{
    vetor.clear();
    vetor.reserve(size);
    for (int i = 0; i < size; i++)
    {
        vetor.push_back(i);
    }
}

int gerar_alvo(int valor)
{
    random_device aleatorio;
    mt19937 gerador(aleatorio());
    uniform_int_distribution<int> distribution(0, valor);
    return distribution(gerador);
}

void embaralhar_vetor(vector<int> &vetor, int size)
{
    random_device aleatorio;
    mt19937 gerador(aleatorio());
    uniform_int_distribution<int> distribution(0, size - 1);
    int index1, index2, aux;
    index1 = distribution(gerador);
    for (int i = 0; i < size * 2; i++)
    {
        index1 = distribution(gerador);
        index2 = distribution(gerador);
        aux = vetor[index1];
        vetor[index1] = vetor[index2];
        vetor[index2] = aux;
    }
}

int busca_desordem(vector<int> vetor, int size, int alvo, int index)
{
    if (index == size)
    {
        return -1;
    }
    if (vetor[index] == alvo)
    {
        return index;
    }
    index++;
    return busca_desordem(vetor, size, alvo, index);
}

int main()
{
    float contagem = 1;
    float acerto = 0;
    vector<int> vetor;
    int alvo;
    for (int i = 10; i <= 5000; i += 10)
    {
        popular(vetor, i);

        int result;
        double tempoEmMicrossegundos = 0.0;
        for (int j = 0; j < nrepeticoes; j++)
        {

            contagem += 1;
            alvo = gerar_alvo((i * 2) - 1);
            embaralhar_vetor(vetor, i);
            auto start = chrono::high_resolution_clock::now();

            sort(vetor.begin(), vetor.end());
            result = busca_rec(vetor, alvo, 0, vetor.size() - 1);

            auto end = chrono::high_resolution_clock::now();

            
            chrono::duration<double> duration = end - start;
            tempoEmMicrossegundos += duration.count() * 1000000;
            if (result == -1)
            {
                acerto += 1;
            }
        }
        tempoEmMicrossegundos /= nrepeticoes;
        cout << i << " " << tempoEmMicrossegundos << " microssegundos" << endl;
    }
    float porcento_sucesso = acerto / contagem;

    cout << porcento_sucesso * 100 << "% de sucesso" << endl;

    return 0;
}
