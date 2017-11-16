// // //
// Trabalho 1 de TAG 
// 150032552 - Claudio Segala Rodrigues Silva Filho
// 160071569 - Luis Felipe Braga Gebrim Silva
// // //

#include <bits/stdc++.h>

using namespace std;

// Vetores para armazenar a lista de adjacencia
vector<int> adj[50];
// Vetor para armazer os nomes dos alunos
vector<string> nomes;
// Vetor para armazenar os alunos ordenados por quantidade de amigos(grau)
vector<pair<int,int> > ordenado;
// Vetor para armazenar os cliques maximais encontrados
vector<vector<int> > cliques;

void bron_kerbosh(vector<int> r, vector<int> p, vector<int> e){
	// r = vertices escolhidos para o clique atual
	// p = possiveis vertices para expandir o clique atual
	// e = vertices que nao podem fazer parte do clique atual

	// Caso nao seja possivel adicionar nenhum vertice ao clique atual, "p" esta vazio,
	// e o conjunto de vertices atualmente considerados nao possua nenhum vertice excluido, "e" esta vazio.
	// O clique encontrado eh armazenado no vetor "cliques"
	if(p.empty() && e.empty()) cliques.push_back(r);
	
	// Vetores para marcar os elementos dos vetores "p" e "e" que estao sendo considerados ativos
	bool mark[50], mark2[50];
	memset(mark,0,sizeof mark);
	memset(mark2,0,sizeof mark2);
	
	for(int i = 0; i < p.size(); i++)
		mark[p[i]] = 1;
	for(int i = 0; i < e.size(); i++)
		mark2[e[i]] = 1;
	
	for(int i = 0; i < p.size(); i++){
		// Adiciona um novo vertice, "p[i]" ao clique que se pretende expandir
		r.push_back(p[i]);

		// Vetores "p2" e "e2" representam a intercessao entre os vetores "p" e "e", respectivamente
		// e o conjunto de vizinhos do vertice "p[i]"
		vector<int> p2, e2;
		for(int j = 0; j < adj[p[i]].size(); j++){
			if(mark[adj[p[i]][j]])
				p2.push_back(adj[p[i]][j]);
			if(mark2[adj[p[i]][j]])
				e2.push_back(adj[p[i]][j]);
		}

		// Realiza uma chamada recursiva para tentar expandir o conjunto de vertices de "r"
		// com os vertices de "p2"
		bron_kerbosh(r,p2,e2);

		// Remove o vertice "p[i]" do vetor "r" para procurar cliques em outros conjuntos
		// de vertices nas proximas iteracoes
		r.pop_back();

		// Remove o vertice "p[i]" do vetor "p" e o adiciona ao vetor "e"
		mark[p[i]] = 0;
		mark2[p[i]] = 1;
	}
}

bool comp(vector<int> a, vector<int> b){
	return b.size() < a.size();
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
			adj[num].push_back(vertice);
			adj[vertice].push_back(num);

			// Le o numero do proximo amigo
			scanf("%d",&vertice);
		}
	}

	// Guarda no vetor "ordenado" os graus dos vertices que representam cada aluno
	for(int i = 1; i < 50; i++){
		ordenado.push_back(make_pair(adj[i].size(),i));
	}
	// Ordena o vetor "ordenado" em ordem crescente de grau
	sort(ordenado.begin(), ordenado.end());

	printf("Alunos ordenados por grau:\n\n");
	for(int i = ordenado.size()-1; i >= 0; i--){
		printf("Grau: %d\nNumero: %d\nNome: %s\n",ordenado[i].first, ordenado[i].second, nomes[ordenado[i].second - 1].c_str());
		printf("\n");
	}

	printf("------------------------------------------------------------------------\n");

	// Declaracao dos tres vetores que serao usados no algoritmo de Bron & Kerbosh para encontrar os cliques maximais
	vector<int> r,p,e;
	// Coloca no v
	for(int i = 1; i < 50; i++)
		p.push_back(i);
	bron_kerbosh(r,p,e);
	
	// Ordena o vetor "cliques" em ordem decrescente com relacao ao tamanho dos cliques encontrados
	sort(cliques.begin(), cliques.end(), comp);

	// Mostra o maior clique maximal
	printf("Clique maximo\n");
	printf("Tamanho: %d\n",cliques[0].size());
	printf("Alunos:\n");
	for(int i = 0; i < cliques[0].size(); i++){
		printf("%d %s\n",cliques[0][i],nomes[cliques[0][i] - 1].c_str());
	}

	printf("------------------------------------------------------------------------\n");
	printf("\n");

	// Mostra um outro clique maximal, de tamanho menor ou igual ao primeiro
	printf("Clique maximal\n");
	printf("Tamanho: %d\n",cliques[1].size());
	printf("Alunos:\n");
	for(int i = 0; i < cliques[1].size(); i++){
		printf("%d %s\n",cliques[1][i],nomes[cliques[1][i] - 1].c_str());
	}
    return 0;
}
