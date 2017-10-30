// // // // // // // // // // // // // // // // // // //
// TAG - Trabalho 2                                   //
// 150032552 - Claudio Segala Rodrigues Silva Filho   //
// 160071569 - Luis Felipe Braga Gebrim Silva         //
// // // // // // // // // // // // // // // // // // //

#include <bits/stdc++.h>
using namespace std;

// Variaveis Globais
int qnt_materias;                      // quantidade de materias
vector<int> adj[100];                  // lista de adjacencia com a dag
int peso[100];                         // peso das materias
int grau_incidencia[100];              // grau de incidencia das materias
vector< pair<int, string> > disciplinas; // lista de materias
bool visitado[100];

int caminho_critico(int x, pair<int, int>* maiorCaminho){
	if(maiorCaminho[x].first != -1) return maiorCaminho[x].first;

	int maiorAdj = 0, maiorVert = 0;
	for(int i = 0; i < adj[x].size(); i++){
		int caminho = caminho_critico(adj[x][i], maiorCaminho);
		if(caminho > maiorAdj){
			maiorAdj = caminho;
			maiorVert = adj[x][i];
		}
	}

	maiorCaminho[x] = make_pair(maiorAdj + peso[x], maiorVert);
	return maiorAdj + peso[x];
}

// Procura o maior caminho na dag
void achaCaminhoCritico () {
	printf("\n\nCaminho Critico no Grafo:\n\n");

	pair<int,int> maiorCaminho[100]; 
	memset(maiorCaminho, -1, sizeof maiorCaminho);

	int inicioCritico, caminhoCritico = 0;
	for(int i = 1; i <= qnt_materias; i++){
		if(grau_incidencia[i] == 0){
			int novoCaminho = caminho_critico(i, maiorCaminho);
			if(novoCaminho > caminhoCritico){
				caminhoCritico = novoCaminho;
				inicioCritico = i;
			}
		}
	}

	printf("Peso: %d\n\n", caminhoCritico);

	while(inicioCritico) {
		printf("%-.-2d %s\n", inicioCritico, disciplinas[inicioCritico-1].second.c_str());
		inicioCritico = maiorCaminho[inicioCritico].second;
	}
}

// Simples dfs que coloca em um vetor o no que terminou de executar
void dfs (int x, vector<int>& ordemTopologica){
	if(visitado[x]) return;
	visitado[x] = true;
	
	for(int i = 0; i < adj[x].size(); i++) {
		dfs(adj[x][i], ordemTopologica);
	}
	ordemTopologica.push_back(x);
}

// A partir da lista de adjacencia acha o grafo
void achaOrdemTopologica () {
	printf("\n\nOrdem Topologica:\n\n");

	vector<int> ordemTopologica;

	for(int i = 1; i <= qnt_materias; i++) {
		if(grau_incidencia[i] == 0) {
			dfs(i, ordemTopologica);
		}
	}

	reverse(ordemTopologica.begin(), ordemTopologica.end());

	for(int i = 0; i < ordemTopologica.size(); i++){
		printf("%0.-2d %s\n",ordemTopologica[i], disciplinas[ordemTopologica[i]-1].second.c_str());
	}
}

// Entra no arquivo fluxoCIC.txt para pegar as informacoes
void fillGraph () {
	freopen("fluxoCIC.txt","r",stdin);

	scanf("%d", &qnt_materias);
	
	int id_materia; 
	while(scanf("%d", &id_materia) != EOF){
		int codigo, creditos, dificuldade;
		char nome[100];
		scanf("%d %d %d %[^\n]", &codigo, &creditos, &dificuldade, nome);

		disciplinas.push_back(make_pair(codigo, nome)); 
		peso[id_materia] = creditos * dificuldade; // coloca o peso da arestas que saem de id_materia

		int dep;
		scanf("%d", &dep);
		while(dep != 0){
			adj[id_materia].push_back(dep);
			grau_incidencia[dep]++;
			scanf("%d",&dep);
		}
	}
}

// Limpa a tela do terminal e coloca o assunto desse programa
void iniciate () {
	system("clear || cls");
	printf("Disciplinas Obrigatorias de Ciencia da Computacao\n");
}

int main(){
	iniciate();
	fillGraph();
	achaOrdemTopologica();
	achaCaminhoCritico();
	return 0;
}
