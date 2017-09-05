// // //
// Trabalho 1 de TAG 
// 150032552 - Claudio Segala Rodrigues Silva Filho
// 160071569 - Luis Felipe Braga Gebrim Silva
// // //

#include <bits/stdc++.h>

using namespace std;

// Bitmask para armazenar a matriz de adjacencia
long long int adj[50];
// Vetor para armazer os nomes dos alunos
vector<string> nomes;
// Vetor para armazenar os alunos ordenados por quantidade de amigos(grau)
vector<pair<long long,int> > ordenado;
// Vetor para armazenar os cliques maximais encontrados
vector<vector<int> > cliques;

void bron_kerbosh(long long r, long long p, long long e){
	// r = vertices escolhidos para o clique atual
	// p = possiveis vertices para expandir o clique atual
	// e = vertices que nao podem fazer parte do clique atual

	// Caso nao seja possivel adicionar nenhum vertice ao clique atual, "p" esta vazio,
	// e o conjunto de vertices atualmente considerados nao possua nenhum vertice excluido, "e" esta vazio.
	// O clique encontrado eh armazenado no vetor "cliques"
	if(!p && !e){
		vector<int> aux;
		for(int i = 1; i < 50; i++)
			if(r & (1 << i))
				aux.push_back(i);

		cliques.push_back(aux);
		return;
	}
	
	for(int i = 1; i <= 50; i++){
		// Se o vertice que se deseja acrescentar ao clique nao esta disponivel em "p"
		// contuamos para a proxima iteracao
		if(!(p & (1 << i))) continue;
		
		long long r2, p2, e2;
		r2 = r | (1 << i); // Adiciona um novo vertice, "i" ao clique que se pretende expandir
		p2 = p & adj[i]; // novo conjunto de possíveis adições ao clique
		e2 = e & adj[i]; // novo conjunto de excluidos 

		// Realiza uma chamada recursiva para tentar expandir o conjunto de vertices de "r"
		// com os vertices de "p2"
		bron_kerbosh(r2, p2, e2);

		// Remove o vertice "i" do bitmask "p" e o adiciona ao bitmask "e"
		p ^= 1 << i;
		e |= 1 << i;
	}
}

bool comp(vector<int> a, vector<int> b){
	return b.size() < a.size();
}


bool comp_grau(pair<long long,int> a, pair<long long,int> b){
	return __builtin_popcount(b.first) > __builtin_popcount(a.first);
}

int main(){
	int num;

	// Designa o arquivo input.txt como input padrao
	freopen("input.txt", "r", stdin);
	
	// Executa o loop de leitura enquanto houver algo para ler no arquivo
	while(scanf("%d",&num) == 1){
		char nome[100];
		scanf("%[^\n]",nome);
		// Guarda o nome do aluno de numero "i" na i-esima posicao do vetor nomes
		nomes.push_back(nome);
		
		// Le o numero de um amigo no aluno "num"
		int vertice;
		scanf("%d",&vertice);

		// O final da lista de amigos do aluno "num" esta marcada com o numero '0'
		// O loop abaixo le o numero de todos os amigos de "num", e cria arestas entre "num" e seus amigos
		while(vertice != 0){
			// Adiciona uma aresta bidirecional entre "vertice" e "num"
			adj[num] |= 1 << vertice;
			adj[vertice] |= 1 << num;

			// Le o numero do proximo amigo
			scanf("%d",&vertice);
		}
	}

	// Guarda no vetor "ordenado" os graus dos vertices que representam cada aluno
	for(int i = 1; i < 50; i++){
		ordenado.push_back(make_pair(adj[i], i));
	}
	// Ordena o vetor "ordenado" em ordem crescente de grau
	sort(ordenado.begin(), ordenado.end(), comp_grau);

	printf("Alunos ordenados por grau:\n\n");
	for(int i = ordenado.size()-1; i >= 0; i--){
		printf("Grau: %d\nNumero: %d\nNome: %s\n",__builtin_popcount(ordenado[i].first), ordenado[i].second, nomes[ordenado[i].second - 1].c_str());
		printf("\n");
	}

	printf("------------------------------------------------------------------------\n");

	// Declaracao dos tres bitmasks que serao usados no algoritmo de Bron & Kerbosh para encontrar os cliques maximais
	long long r,p,e;
	r = p = e = 0;	

	for(int i = 1; i < 50; i++)
		p |= 1 << i;

	bron_kerbosh(r,p,e);
	
	// Ordena o vetor "cliques" em ordem decrescente com relacao ao tamanho dos cliques encontrados
	sort(cliques.begin(), cliques.end(), comp);

	// Mostra o maior clique maximal
	printf("Clique maximo\n");
	printf("Tamanho: %lu\n",cliques[0].size());
	printf("Alunos:\n");
	for(int i = 0; i < cliques[0].size(); i++){
		printf("%d %s\n",cliques[0][i],nomes[cliques[0][i] - 1].c_str());
	}

	printf("------------------------------------------------------------------------\n");
	printf("\n");

	// Mostra um outro clique maximal, de tamanho menor ou igual ao primeiro
	printf("Clique maximal\n");
	printf("Tamanho: %lu\n",cliques[1].size());
	printf("Alunos:\n");
	for(int i = 0; i < cliques[1].size(); i++){
		printf("%d %s\n",cliques[1][i],nomes[cliques[1][i] - 1].c_str());
	}
    return 0;
}
