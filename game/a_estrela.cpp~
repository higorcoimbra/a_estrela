/*
==========================================================
| Centro Federal de Educação Tecnológica de Minas Gerais | 
|  Laboratório de Inteligência Artificial - Prática 3    |
|               Implementação do Algoritmo A*		         |
|            Alunos: Higor Amorim - Matheus Rosa         |
==========================================================
*/

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <climits>
#include <cstdio>
#include <fstream>
#include <unistd.h>
#define maxn 400000 

using namespace std;

/*
	Estrutura que representa uma aresta do grafo de busca
*/
struct aresta{
	int indice;
	int peso;

	aresta() { }
	aresta(int indice,int peso) : indice(indice), peso(peso) {}
	bool operator <(const aresta &outro) const{
		return peso > outro.peso;
	}
};

struct estado {
	vector<int> tab;
	int pos;
	bool operator < (const estado &outro) const {
		return tab < outro.tab;
	}
};

int conta_estados, n_cidades;			// controle do numero cidades
map<estado,int> tab_id;			  // mapamento do nome da cidade para o no
map<int,estado> id_tab;			  // mapeamento do no para o nome da cidade

vector<aresta> g[maxn];
vector<int> pais, distancia, linha_reta;	// vetores auxiliares para armazenar informações da busca
int mov_x[4] = {1, 0, -1, 0};
int mov_y[4] = {0, 1, 0, -1};

const int size = 3;


/*
	Procedimento para Debug do Grafo
*/

void print_model() {
	for(int i = 0;i < 5;i++){
		cout << i << "->";
		for(int j = 0;j < g[i].size();j++){
			cout << g[i][j].indice << "-" << g[i][j].peso << " ";
		}cout << endl;
	}cout << endl;
}

void printEstado(estado E) {
	puts("");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%2d ", E.tab[size*i+j]);
		}puts("");
	}puts("");
}

/*
	Procedimento que recebe uma cidade de origem e destino e cria uma nova identificação numérica
*/
void cria_estado(estado atual, estado novo){
	if(tab_id.find(novo) == tab_id.end()) {
		tab_id.insert(make_pair(novo, conta_estados));
		id_tab.insert(make_pair(conta_estados, novo));
		conta_estados++;
		g[tab_id[atual]].push_back(aresta(tab_id[novo], 1));
		g[tab_id[novo]].push_back(aresta(tab_id[atual], 1));
		//puts("Filin");
		//printEstado(novo);
	}
}

bool pode(int i, int j) {
	return i >= 0 && i < size && j >= 0 && j < size;
}

/*
	Procedimento responsavel por receber as informações do problema e criar um grafo de busca 
*/
void modelagem() {
	for (int i = 0; i < id_tab.size(); i++) {
		estado atual = id_tab[i];
		int pos = atual.pos;
		//printEstado(atual);
		int ii = pos/3, jj = pos%3;		
		for (int j = 0; j < 4; j++) {
			if (pode(mov_y[j] + ii, mov_x[j] + jj)) {
				estado novo = atual;
				int l = mov_y[j] + ii, c = mov_x[j] + jj;
				int npos = l*3 + c;
				swap(novo.tab[pos], novo.tab[npos]);
				novo.pos = npos;
				cria_estado(atual, novo);
			}
		}
		sleep(5);
	}
}


/*
	Funçao responsavel por percorrer o grafo e encontrar qual o caminho mínimo entre uma origem e um destino
*/
int busca(int origem, int destino) {
	priority_queue<aresta> pq;					                    // Armazena as bordas
	fill(distancia.begin(),distancia.end(),INT_MAX);        // Inicializa as distancias para todos os nos como infinito
	fill(pais.begin(),pais.end(),-1);                       // Inicializa o pai de todos os nós com -1
	
  pq.push(aresta(origem,0+linha_reta[origem]));           // Coloca a origem na fila
  distancia[origem] = 0;                                  // Inicializa a distancia para a origem com 0
	pais[origem] = origem;                                  // O pai da origem fica sendo ela mesma, para ser usado como criterio de parada da impressao do caminho minimo

	while(!pq.empty()){		
		aresta pai = pq.top(); pq.pop();                      // Retira o no aberto que tem a menor distancia
		int u = pai.indice;
		if(u == destino) return distancia[u];                 // Se o no restirado é o destino, a busca para, e retorna-se a distancia ate o destino

		for(int i = 0;i < g[u].size();i++) {
			int v = g[u][i].indice;			
			if(distancia[v] > distancia[u]+g[u][i].peso) {  // Verifica se a distancia atual para esse no e maior do que a nova distancia ate ele, passando pelo no u
				distancia[v] = distancia[u]+g[u][i].peso;     					// Atualiza a distancia para esse no 
				pais[v] = u;                                      // Atualiza o pai desse no
				pq.push(aresta(v,distancia[v]+linha_reta[v]));    // Coloca o no na fila, com f = g + h
			}
		}
	}

	return INT_MAX;
}

/*
  Procedimento responsável por imprimir qual o caminho minimo percorrido pela busca
*/
/*
void reconstrucao(vector<int> pais, int origem, int destino, vector<int> linha_reta){
	vector<string> aux;
	int filho = destino;
	while(pais[filho] != filho){
		aux.push_back(id_tab[filho]);
		filho = pais[filho];
	}
	aux.push_back(id_tab[origem]);
	printf("Cidade      f    g    h\n");
	for(int i = aux.size()-1;i >= 0;i--){
		int atual = tab_id[aux[i]];
		printf("%10s %4d %3d %3d\n", aux[i].c_str(), distancia[atual]+linha_reta[atual],  distancia[atual], linha_reta[atual]);
	}
	cout << endl;
}*/

int main() {

	estado origem, destino;
	origem.tab.resize(size*size);
	destino.tab.resize(size*size);

	for (int i = 0; i < destino.tab.size(); i++) {
		cin >> origem.tab[i];
		destino.tab[i] = i;
	}
	
	origem.pos = 1;
	tab_id.insert(make_pair(origem, conta_estados));
	id_tab.insert(make_pair(conta_estados, origem));
	conta_estados++;
	modelagem();

	linha_reta.resize(conta_estados);
	pais.resize(conta_estados);
	distancia.resize(conta_estados);
	fill(linha_reta.begin(), linha_reta.end(), 0);

	cout << tab_id[origem] << ' ' << tab_id[destino] << endl;

	printEstado(origem);
	printEstado(destino);

	print_model();

	printf("%d\n", busca(tab_id[origem], tab_id[destino]));

	return 0;
}


