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

using namespace std;
 
int conta_cidades, n_cidades;			// controle do numero cidades
map<string,int> cidade_id;			  // mapamento do nome da cidade para o no
map<int,string> id_cidade;			  // mapeamento do no para o nome da cidade
vector<int> pais, distancia, linha_reta;	// vetores auxiliares para armazenar informações da busca

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

/*
	Procedimento para Debug do Grafo
*/
void print_model(vector<aresta> modelo[]) {
	for(int i = 0;i < n_cidades;i++){
		cout << id_cidade[i] << "->";
		for(int j = 0;j < modelo[i].size();j++){
			cout << id_cidade[modelo[i][j].indice] << "-" << modelo[i][j].peso << " ";
		}cout << endl;
	}cout << endl;
}

/*
	Procedimento que recebe uma cidade de origem e destino e cria uma nova identificação numérica
*/
void cria_cidade(string origem,string destino){
	if(cidade_id.find(origem) == cidade_id.end()) {
		cidade_id[origem] = conta_cidades;
		id_cidade[conta_cidades] = origem;
		conta_cidades++;
	}
	if(cidade_id.find(destino) == cidade_id.end()) {
		cidade_id[destino] = conta_cidades;
		id_cidade[conta_cidades] = destino;
		conta_cidades++;
	}
}

/*
	Procedimento responsavel por receber as informações do problema e criar um grafo de busca 
*/
void modelagem(vector<aresta> grafo[]){
	int n_transicoes,peso,conta_cidades;
	string origem,destino;
	cin >> n_transicoes;
	conta_cidades = 0;

	// le e armazena as transições do grafo
	for(int i = 0;i < n_transicoes;i++){
		cin >> origem >> destino >> peso;
		cria_cidade(origem,destino);
		grafo[cidade_id[origem]].push_back(aresta(cidade_id[destino], peso));
		grafo[cidade_id[destino]].push_back(aresta(cidade_id[origem], peso));
	}

	// le e armazena as distancias em linha reta da origem ate o destino, utilizado na heuristica
	for(int i = 0;i < n_cidades;i++){
		cin >> origem >> peso;
		linha_reta[cidade_id[origem]] = peso;
	}
}


/*
	Funçao responsavel por percorrer o grafo e encontrar qual o caminho mínimo entre uma origem e um destino
*/
int busca(vector<aresta> grafo[], int origem, int destino) {
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

		for(int i = 0;i < grafo[u].size();i++) {
			int v = grafo[u][i].indice;			
			if(distancia[v] > distancia[u]+grafo[u][i].peso) {  // Verifica se a distancia atual para esse no e maior do que a nova distancia ate ele, passando pelo no u
				distancia[v] = distancia[u]+grafo[u][i].peso;     // Atualiza a distancia para esse no 
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
void reconstrucao(vector<int> pais, int origem, int destino, vector<int> linha_reta){
	vector<string> aux;
	int filho = destino;
	while(pais[filho] != filho){
		aux.push_back(id_cidade[filho]);
		filho = pais[filho];
	}
	aux.push_back(id_cidade[origem]);
	printf("Cidade      f    g    h\n");
	for(int i = aux.size()-1;i >= 0;i--){
		int atual = cidade_id[aux[i]];
		printf("%10s %4d %3d %3d\n", aux[i].c_str(), distancia[atual]+linha_reta[atual],  distancia[atual], linha_reta[atual]);
	}
	cout << endl;
}

int main() {

  ifstream in("cidades");
  cin.rdbuf(in.rdbuf());

	string origem, destino;	
	int dist;
  
  // Le o numero de cidades do problema
	cin >> n_cidades;

  // Inicializa os tamanhos dos vetores auxiliares com base no numero de cidades
	pais.resize(n_cidades);
	distancia.resize(n_cidades);
	linha_reta.resize(n_cidades);
	vector<aresta> modelo[n_cidades];

  // Faz a modelagem do grafo
	modelagem(modelo);

  // Le as cidades de origem e de destino
	cin >> origem >> destino;

  // Faz a busca
	dist = busca(modelo, cidade_id[origem], cidade_id[destino]);

  // Impressão dos resultados
	cout << endl << "Distância minima: " << dist << endl;
	reconstrucao(pais,cidade_id[origem],cidade_id[destino],linha_reta);

	return 0;
}


