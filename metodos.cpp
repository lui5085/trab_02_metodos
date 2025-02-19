#include "metodos.h"
#include <cmath>
#include <iostream>

bool Metodos::factorLU(std::vector<std::vector<double>> &A, int n)
{
    for (int k=0; k<n; k++){
        double pivot = A[k][k];
        if (std::fabs(pivot) < 1e-14) {
            std::cerr << "factorLU: pivô nulo na linha " << k << "\n";
            return false;
        }
        for (int i=k+1; i<n; i++){
            double m = A[i][k] / pivot;
            A[i][k] = m;
            for (int j=k+1; j<n; j++){
                A[i][j] -= m * A[k][j];
            }
        }
    }
    return true;
}

std::vector<double> Metodos::solveLU(const std::vector<std::vector<double>> &A,
                                     const std::vector<double> &f,
                                     int n)
{
    std::vector<double> y(n), x(n);

    // L y = f
    for (int i=0; i<n; i++){
        double sum = f[i];
        for (int j=0; j<i; j++){
            sum -= A[i][j]*y[j];
        }
        y[i] = sum;
    }

    // U x = y
    for (int i=n-1; i>=0; i--){
        double sum = y[i];
        for (int j=i+1; j<n; j++){
            sum -= A[i][j]*x[j];
        }
        x[i] = sum / A[i][i];
    }

    return x;
}

void Metodos::computeLDPFromLU(std::vector<std::vector<double>> &A,
                               int n,
                               std::vector<double> &D)
{
    for (int k=0; k<n; k++){
        double diag = A[k][k];  // U[k][k]
        D[k] = diag;
        // Normaliza para obter P
        for (int j=k; j<n; j++){
            A[k][j] /= diag;
        }
    }
}

std::vector<double> Metodos::solveLDP(const std::vector<std::vector<double>> &A,
                                      const std::vector<double> &D,
                                      const std::vector<double> &f,
                                      int n)
{
    // 1) L y1 = f
    std::vector<double> y1(n);
    for (int i=0; i<n; i++){
        double sum = f[i];
        for (int j=0; j<i; j++){
            sum -= A[i][j]*y1[j]; // L(i,j)
        }
        y1[i] = sum;
    }
    // 2) y2 = y1 / D
    std::vector<double> y2(n);
    for (int i=0; i<n; i++){
        y2[i] = y1[i]/D[i];
    }
    // 3) P d = y2
    std::vector<double> d(n,0.0);
    for (int i=n-1; i>=0; i--){
        double sum = y2[i];
        for (int j=i+1; j<n; j++){
            sum -= A[i][j]*d[j];
        }
        d[i] = sum;
    }
    return d;
}
