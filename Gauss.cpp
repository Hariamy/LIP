#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

void substituicoes_sucessivas(int n, double **A, double *b, double *x);
void substituicoes_retroativas(int n, double **A, double *b, double *x);

void eliminacao_gauss(int n, double **A, double *b);
void eliminacao_gauss_com_pivotacao(int n, double **A, double *b);

void fatoracao_LU(double n, double **A, double **L, double **U);
void fatoracao_LU_com_pivotacao(double n, double **A, double **L, double **U, double **P);

void aloca_matriz(int n, double **M);
void deleta_matriz(int n, double **M);

double determinante(int n, double **A);
void eliminacao_gauss_jordan(int n, double **A, double **I);

void imprimir_vetor(int n, double *x, char nome);
void imprimir_matriz(int n, double **M, char nome);

void produto(int n, double **M, double *V, double *resp);

int main(int argc, char const *argv[]){

	int n = 3;
	double **L = new double*[n];
	for (int i = 0; i < n; i++)
		L[i] = new double[n];

	double **U = new double*[n];
	for (int i = 0; i < n; i++)
		U[i] = new double[n];
	
	double **A = new double*[n];
	for (int i = 0; i < n; i++)
		A[i] = new double[n];

	double **P = new double*[n];
	for (int i = 0; i < n; i++)
		P[i] = new double[n];
	
	A[0][0] = 20; A[0][1] = 7 ; A[0][2] = 9;
	A[1][0] = 7 ; A[1][1] = 30; A[1][2] = 8;
	A[2][0] = 9 ; A[2][1] = 8 ; A[2][2] = 30;
	imprimir_matriz(n, A, 'A');

	double A2[n][n] = {
		{20, 7, 9},
		{7, 30, 8},
		{9, 8, 30}
	};

	eliminacao_gauss_jordan(n, A, P);
	imprimir_matriz(n, P, 'I');
	imprimir_matriz(n, A, 'A');

	/*
	cout << determinante(n, A) << endl;
	double b[n] = {16, 38, 38};
	double x[n], y[n];
	fatoracao_LU_com_pivotacao(n, A, L, U, P);
	imprimir_matriz(n, L, 'L');
	imprimir_matriz(n, U, 'U');
	produto(n, P, b, b);
	substituicoes_sucessivas(n, L, b, y);
	imprimir_vetor(n, y, 'Y');
	substituicoes_retroativas(n, U, y, x);
	imprimir_vetor(n, x, 'X');

	eliminacao_gauss(n, A, b);
	substituicoes_retroativas(n, A, b, x);
	imprimir_vetor(n, x, 'X');
	eliminacao_gauss_com_pivotacao(n, A, b);
	imprimir_vetor(n, x, 'X');
*/
	deleta_matriz(n, L);
	deleta_matriz(n, U);
	deleta_matriz(n, P);

}

void eliminacao_gauss_jordan(int n, double **A, double **I){
	double m;
	for (int i = 0; i < n; i++) //Matriz identidade
		I[i][i] = 1;
	
	// Percorre as linhas
	for (int l = 0; l < n; l++){

		//Dividir a coluna do pivor pelo pivor
		m = A[l][l];
		for (int c = 0; c < n; c++){
			if (A[l][l] != 0) {
				A[l][c] = A[l][c]/m;
				I[l][c] = I[l][c]/m;
			}
		}

		for (int l2 = 0; l2 < n; l2++) { //Percorre as linhas
			if (l2 != l) {			  //Para toda linha diferente da linha linha
				m = A[l2][l]; 
				for (int c = 0; c < n; c++) {
					A[l2][c] = A[l2][c] - m * A[l][c];
				}
					
				for (int c = 0; c < n; c++) 
					I[l2][c] = I[l2][c] - m * I[l][c];
				
				A[l2][l] = 0;
			}
		}
	}
}

double determinante(int n, double **A){
	double m, det = 1;

	for (int k = 0; k < n-1; k++){
		for (int i = k+1; i < n; i++){
			if (A[k][k] != 0) m = A[i][k]/A[k][k];
			
			A[i][k] = 0;

			for (int j = k+1; j < n; j++) A[i][j] = A[i][j] - m*A[k][j];
		}
		det *= A[k][k];
	}
	det *= A[n-1][n-1];
	return det;
}


void fatoracao_LU(double n, double **A, double **L, double **U){
	double m;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
			U[i][j] = A[i][j];

	for (int i = 0; i < n; i++)
		L[i][i] = 1;
		
	for (int k = 0; k < n-1; k++){
		for (int i = k+1; i < n; i++){
			if (U[k][k] != 0) m = U[i][k]/U[k][k];
			
			L[i][k] = m;
			U[i][k] = 0;

			for (int j = k+1; j < n; j++) U[i][j] = U[i][j] - m*U[k][j];
			
		}
	}
}


void fatoracao_LU_com_pivotacao(double n, double **A, double **L, double **U, double **P){
	double aux, m, maior;
	int linha;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
			U[i][j] = A[i][j];

	for (int i = 0; i < n; i++)
		L[i][i] = P[i][i] = 1;
	
	for (int k = 0; k < n-1; k++){
		maior = -numeric_limits<double>::max();

		for (int l = k; l < n; l++){
			if(abs(A[l][k]) > maior){
				maior = abs(A[l][k]);
				linha = l;
			}
		}

		if (linha != k){
			for (int t = k; t < n; t++){
				aux = A[linha][t];
				A[linha][t] = A[k][t];
				A[k][t] = aux;

				aux = P[linha][t];
				P[linha][t] = P[k][t];
				P[k][t] = aux;
			}
		}
		
		for (int i = k+1; i < n; i++){
			if (U[k][k] != 0) m = U[i][k]/U[k][k];
			
			L[i][k] = m;
			U[i][k] = 0;

			for (int j = k+1; j < n; j++) U[i][j] = U[i][j] - m*U[k][j];
			
		}
	}
}


void eliminacao_gauss(int n, double **A, double *b){
	double m;

	for (int k = 0; k < n-1; k++){
		for (int i = k+1; i < n; i++){
			if (A[k][k] != 0) m = A[i][k]/A[k][k];
			
			A[i][k] = 0;

			for (int j = k+1; j < n; j++) A[i][j] = A[i][j] - m*A[k][j];
			
			b[i] = b[i] - m*b[k];
		}
	}
}

void eliminacao_gauss_com_pivotacao(int n, double **A, double *b){
	double aux, m, maior;
	int linha;
	for (int k = 0; k < n-1; k++){
		maior = -numeric_limits<double>::max();

		for (int l = k; l < n; l++){
			if(abs(A[l][k]) > maior){
				maior = abs(A[l][k]);
				linha = l;
			}
		}

		if (linha != k){
			for (int t = k; t < n; t++){
				aux = A[linha][t];
				A[linha][t] = A[k][t];
				A[k][t] = aux;
			}

			aux = b[linha];
			b[linha] = b[k];
			b[k] = aux;
		}

		
		for (int i = k+1; i < n; i++){
			if (A[k][k] != 0) m = A[i][k]/A[k][k];

			A[i][k] = 0;

			for (int j = k+1; j < n; j++) A[i][j] = A[i][j] - m*A[k][j];

			b[i] = b[i] - m*b[k];
		}
	}

}


void substituicoes_retroativas(int n, double **A, double *b, double *x) {
	double soma;
	n--;
	if (A[n][n] != 0) x[n] = b[n]/A[n][n];

	for (int i = n - 1; i >= 0; i--){
		soma = 0;

		for (int j = i + 1; j <= n; j++) soma = soma + A[i][j] * x[j];
		
		x[i] = (b[i] - soma) / A[i][i];
	}
}


void substituicoes_sucessivas(int n, double **A, double *b, double *x) {
	double soma;

	if (A[0][0] != 0) x[0] = b[0]/A[0][0];


	for (int i = 1; i < n; i++){
		soma = 0;

		for (int j = 0; j <= i - 1; j++) soma += A[i][j] * x[j];
		
		x[i] = (b[i] - soma) / A[i][i];
	}
}

void deleta_matriz(int n, double **M){
	for (int i = 0; i < n; i++)
    	delete [] M[i];
	
	delete [] M;
}

void imprimir_vetor(int n, double *x, char nome) {
	cout << "     ╭            ╮\n" << fixed;
	for (int i = 0; i < n; ++i) i != 1 ? cout << "     │" << setprecision(4) << setw(11) << x[i] << " │" << endl : cout << " " << nome << " = │" << setprecision(4) << setw(11) << x[i] << " │" << endl;
	cout << "     ╰            ╯\n";
}

void imprimir_matriz(int n, double **M, char nome) {
	cout << "     ╭                                    ╮\n";
	for (int i = 0; i < n; ++i){
		i != 1 ? cout << "     │" : cout << " " << nome << " = │";
		for (int j = 0; j < n; ++j)
			 cout << setprecision(4) << setw(11) << M[i][j] << " ";
		cout << "│" << endl;
	}
	cout << "     ╰                                    ╯\n";
}

void produto(int n, double **M, double *V, double *resp){
	double soma = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			soma += M[i][j] * V[j];
		}
		resp[i] = soma;
		soma = 0;
	}

}