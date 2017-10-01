#include<bits/stdc++.h>

using namespace std;

vector<int> adj[100];
int peso[100];
int grauIncid[100];
vector<pair<int,string> > disciplinas;

vector<int> ordemTopologica;

void dfs(int x){
	for(int i = 0; i < adj[x].size(); i++)
		dfs(adj[x][i]);

	ordemTopologica.push_back(x);
}

int main(){
	freopen("fluxoCIC.txt","r",stdin);
	
	int id;
	while(scanf("%d",&id) != EOF){
		int cod, cred, dific;
		char disc[100];
		scanf("%d %d %d %[^\n]",&cod,&cred,&dific,disc);
		disciplinas.push_back(make_pair(cod, disc));
		peso[id] = cred * dific;

		int dep;
		scanf("%d",&dep);
		while(dep != 0){
			adj[id].push_back(dep);
			grauIncid[dep]++;
			scanf("%d",&dep);
		}
	}

	for(int i = 1; i <= id; i++){
		if(grauIncid[i] == 0)
			dfs(i);
	}

	reverse(ordemTopologica.begin(), ordemTopologica.end());

	printf("Ordem Topoligca das Disciplinas Obrigatorias de Ciencia da Computacao:\n\n");
	for(int i = 0; i < ordemTopologica.size(); i++){
		printf("%d %s\n",ordemTopologica[i],disciplinas[ordemTopologica[i]-1].second.c_str());
	}
	return 0;
}