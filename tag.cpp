#include <bits/stdc++.h>

using namespace std;

vector<int> adj[50];
vector<string> nomes;
vector<pair<int,int> > ordenado;

vector<vector<int> > cliques;

void bk(vector<int> r, vector<int> p, vector<int> e){
	if(p.empty() && e.empty()) cliques.push_back(r);
	
	bool mark[50], mark2[50];
	memset(mark,0,sizeof mark);
	memset(mark2,0,sizeof mark2);
	for(int i = 0; i < p.size(); i++)
		mark[p[i]] = 1;
	for(int i = 0; i < e.size(); i++)
		mark2[e[i]] = 1;
	
	for(int i = 0; i < p.size(); i++){
		r.push_back(p[i]);
		vector<int> p2, e2;
		for(int j = 0; j < adj[p[i]].size(); j++){
			if(mark[adj[p[i]][j]])
				p2.push_back(adj[p[i]][j]);
			if(mark2[adj[p[i]][j]])
				e2.push_back(adj[p[i]][j]);
		}
		bk(r,p2,e2);
		r.pop_back();
		mark[p[i]] = 0;
		mark2[p[i]] = 1;
	}
}

bool comp(vector<int> a, vector<int> b){
	return b.size() < a.size();
}

int main(){
	int num;
	freopen("input.txt", "r", stdin);
	while(scanf("%d",&num) == 1){
		char nome[100];
		scanf("%[^\n]",nome);
		nomes.push_back(nome);
		int v;
		scanf("%d",&v);
		while(v){
			adj[num].push_back(v);
			adj[v].push_back(num);
			scanf("%d",&v);
		}
	}

	for(int i = 1; i < 50; i++){
		ordenado.push_back(make_pair(adj[i].size(),i));
	}
	sort(ordenado.begin(), ordenado.end());

	printf("Alunos ordenados por grau:\n\n");
	for(int i = ordenado.size()-1; i >= 0; i--){
		printf("Grau: %d\nNumero: %d\nNome: %s\n",ordenado[i].first, ordenado[i].second, nomes[ordenado[i].second - 1].c_str());
		printf("\n");
	}

	printf("------------------------------------------------------------------------\n");

	vector<int> r,p,e;
	for(int i = 1; i < 50; i++)
		p.push_back(i);
	bk(r,p,e);

	sort(cliques.begin(), cliques.end(), comp);

	printf("Clique maximo\n");
	printf("Tamanho: %d\n",cliques[0].size());
	printf("Alunos:\n");
	for(int i = 0; i < cliques[0].size(); i++){
		printf("%d %s\n",cliques[0][i],nomes[cliques[0][i] - 1].c_str());
	}

	printf("------------------------------------------------------------------------\n");
	printf("\n");
	printf("Clique maximal\n");
	printf("Tamanho: %d\n",cliques[1].size());
	printf("Alunos:\n");
	for(int i = 0; i < cliques[1].size(); i++){
		printf("%d %s\n",cliques[1][i],nomes[cliques[1][i] - 1].c_str());
	}
    return 0;
}
