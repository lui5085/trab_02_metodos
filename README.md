# Factorization LU e Resolução de Sistemas Lineares

Este repositório implementa a fatorização LU de matrizes e a resolução de sistemas lineares associados. O código fornece funções para decomposição LU, resolução de sistemas LU e fatorização LDP, permitindo a resolução eficiente de sistemas lineares.

## Funcionalidades

- **Fatorização LU**: Decomposição de uma matriz A em uma matriz triangular inferior L e uma matriz triangular superior U.
- **Resolução de sistemas LU**: Utiliza a decomposição LU para resolver um sistema linear Ax = f.
- **Cálculo de LDP a partir de LU**: Extração das matrizes L e P e do vetor D a partir da decomposição LU.
- **Resolução de sistemas LDP**: Utiliza a fatorização LDP para resolver um sistema linear.

## Estrutura do Código

O código está estruturado em um arquivo de cabeçalho `metodos.h` e uma implementação em C++ contendo os seguintes métodos:

- `bool Metodos::factorLU(std::vector<std::vector<double>> &A, int n)`: Realiza a fatorização LU da matriz A.
- `std::vector<double> Metodos::solveLU(const std::vector<std::vector<double>> &A, const std::vector<double> &f, int n)`: Resolve um sistema linear utilizando a fatorização LU.
- `void Metodos::computeLDPFromLU(std::vector<std::vector<double>> &A, int n, std::vector<double> &D)`: Calcula a fatorização LDP a partir de LU.
- `std::vector<double> Metodos::solveLDP(const std::vector<std::vector<double>> &A, const std::vector<double> &D, const std::vector<double> &f, int n)`: Resolve um sistema linear utilizando a fatorização LDP.

## Requisitos

- Compilador C++ compatível com o padrão C++11 ou superior.
- Biblioteca padrão do C++ (`iostream`, `vector`, `cmath`).

## Como Compilar e Executar

1. Compile o código utilizando um compilador C++:
   ```sh
   g++ -o programa main.cpp metodos.cpp
   ```
2. Execute o programa:
   ```sh
   ./programa
   ```

## Observação

- O método `factorLU` verifica se há pivôs nulos e retorna `false` caso seja encontrada uma singularidade.
- Pequenos valores próximos de zero (abaixo de `1e-14`) podem indicar uma matriz singular, interrompendo o processo.

## Licença

Este projeto é distribuído sob a licença MIT. Sinta-se livre para usar e modificar conforme necessário.

