#include<iostream>
#include"matrix.h"
using namespace std;

int main() {
     Matrix one(3, 2);

     cout << "the matrix one is :\n";
     one.print_mat();

     Matrix two(2, 3);

     cout << "the matrix two is :\n";
     two.print_mat();

     Matrix three = one.mul(two);

     cout << "the matrix three (one * two) is :\n";
     three.print_mat();

     three.replace_row(1);
     cout << "updated matrix after row replacement :\n";
     three.print_mat();

     three.replace_column(2);
     cout << "updated matrix after column replacement :\n";
     three.print_mat();

     return 0;
}