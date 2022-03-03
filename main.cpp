#include <iostream>
#include <time.h>
#include "polynomial.hpp"

int main() {
    int opt{1}, input{1};
    clock_t start, end;

    while(opt) {
        long d1{0}, d2{0};
        std::cout << "\nEnter the degree of the first polynomial.\n>> ";
        std::cin >> d1;
        std::cout << "Enter the degree of the second polynomial.\n>> ";
        std::cin >> d2;

        Polynomial A(d1), B(d2);
        Polynomial res_naive, res_daq;

        std::cout << "\nUser input(0) or random input(1): ";
        std::cin >> input;

        if(input == 0) {
            std::cout << "\nEnter the coefficients of the first polynomial.\n>> ";
            A.inputPolynomial();
            std::cout << "Enter the coefficients of the second polynomial.\n>> ";
            B.inputPolynomial();
        } else {
            A.randomPolynomial();
            B.randomPolynomial();
        }

        std::cout << "[A] ";
        A.displayCoeffs();
        std::cout << "[B] ";
        B.displayCoeffs();

        start = clock();
        res_naive = A * B;
        end = clock();
        std::cout << "             Naive solution: " << double(end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;
        // res_naive.displayCoeffs();

        start = clock();
        res_daq = A.karatsuba(B);
        end = clock();
        std::cout << "Divide and conquer solution: " << double(end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;
        // res_daq.displayCoeffs();

        if(!(res_naive == res_daq)) {
            std::cout << "\nProducts are not equal!" << std::endl;
            break;
        }
        std::cout << "\nEnter 0 to quit.\n>> ";
        std::cin >> opt;
    } return 0;
}