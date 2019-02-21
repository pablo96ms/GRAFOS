#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <Windows.h>


#define SIZE_OF_LINE 250
#define FILENAME		"mygraph.txt"		//"brock200_1.clq"

typedef struct {
	float x;
	float y;
}punto_t;
void free_dimacs(int** graph, int n) {//funcion para liberar memoria de la matriz
	int i;
	if (graph != NULL) {
		for (i = 0; i < n; i++)
			free(graph[i]);
		free(graph);
		graph = NULL;
	}
}
int is_edge(int** mat, int n, int m) {//Funcion booleana que indica si hay aristas entre dos extremos. En realidad devuelve el numero de aristas
	int res = 0;
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n; j++) {
			if (mat[i][j] == 1)
				res++;

		}

	}
	return res;
}
void print_matrix(int** mat, int n) {//FUNCION PARA IMPRIMIR LA MATRIZ
	int i, j;
	for (i = 0; i < n; i++) {
		printf("/n");
		for (j = 0; j < n; j++)
			printf("%d ", mat[i][j]);
	}
	printf("/n");
}

int** allocate_matrix(int n) {//reserva dinamica de memoria a la matriz de adyacencia
	int i, j;
	int** mat;
	mat = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		mat[i] = (int*)malloc(n * sizeof(int));
	}
	//reset values
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			mat[i][j] = 0;
	return mat;
}


int** read_matrix(const char *graph, int* n, int* m) {
	int i, j;
	int **mat = NULL;//MATRIZ INICIALIZADA EN 0
	int e = 0, v = 0;// n:nodos, m:aristas
	char line[SIZE_OF_LINE];//tamaño de las filas de la matriz de adyacencia
	char token;//caracter para seleccionar en el menu
	char word[25];
	FILE *f = fopen("brock200_1.txt", "r");
	if (f == NULL) {
		perror("Error al abrir el archivo");
		return 0;
	}
	//parse linea a linea
	while (!feof(f)) {
		fgets(line, SIZE_OF_LINE, f);
		if (ferror(f)) {
			puts("ERROR DE LECTURA");
			break;
		}
		sscanf(line, "%c", &token);//exactamente no sé para que sirve esta instrucción, o si es absolutamente necesaria
		switch (token) {
		case 'c':
			break;
		case 'e':
			//arista
			if (2 != sscanf(line, "%*c%d %d", &i, &j)) {
				puts("Error al leer una arista 'e'\n");
				puts("terminando lectura\n");

				//***liberar memoria
				if (mat)
					free_dimacs(**mat, n);
				return 0;
				//un free dentro de un for
			}
			//escribo la arista en la matriz de adyacencia. Matriz simetrica
			//en C++ los indices empiezan en 0
			mat[i - 1][j - 1] = 1;
			mat[j - 1][i - 1] = 1;
			break;
		case 'p':
			if (4 != sscanf("%c %s %d %d", &token, word, &n, &m)) {
				puts("Error al leer la cabecera 'p'\n");
				puts("Terminando lectura...\n");
				return;
			}
			//reserva de memoria matriz grafo(adyacencia)
			mat = (int**)malloc(e * sizeof(int*));
			for (i = 0; i < e; i++) {
				mat[i] = (int*)malloc(v * sizeof(int));
			}
			//dar valores iniciales
			for (i = 0; i < n; i++)
				for (j = 0; j < m; j++)
					mat[i][j] = 0;
			break;
		default:
			puts("error");
		}

	}

}

void main() {
	int** mat = NULL;
	int n=0;
	print_matrix(mat, n);
}
