#ifndef METODOS_H
#define METODOS_H

#include <vector>

// Aqui criamos uma classe com métodos *estáticos* para fatoração LU/LDP.
class Metodos
{
public:
    // Fatoracao LU (in-place). A => L e U
    // Retorna true se ok, false se encontrar pivô zero
    static bool factorLU(std::vector<std::vector<double>> &A, int n);

    // Resolve A*x=f, onde A contém L e U
    static std::vector<double> solveLU(const std::vector<std::vector<double>> &A,
                                       const std::vector<double> &f,
                                       int n);

    // Extrai LDP a partir da LU que já está em A
    static void computeLDPFromLU(std::vector<std::vector<double>> &A,
                                 int n,
                                 std::vector<double> &D);

    // Resolve o sistema usando LDP
    static std::vector<double> solveLDP(const std::vector<std::vector<double>> &A,
                                        const std::vector<double> &D,
                                        const std::vector<double> &f,
                                        int n);
};

#endif // METODOS_H
