#pragma once

#include<vector>
using namespace std;

class Matrix {
public:
	Matrix(int row, int column) {
		this->row = row;
		this->column = column;
		init();
	}

	Matrix(vector<int> new_mat, int row, int column) {
		this->mat = new_mat;
		this->row = row;
		this->column = column;
	}

	vector<int> get_mat() {
		return this->mat;
	}

	int get_row() {
		return this->row;
	}

	int get_column() {
		return this->column;
	}

	void init(); //initializes the matrix with values
	bool is_digit(int value); //checks if the input is all digits
	int dimension();
	void add(Matrix to_add);
	void sub(Matrix to_sub);
	Matrix mul(Matrix to_mult);
	Matrix scalar_mult(int scalar);
	vector<int> get_row(int i);
	vector<int> get_column(int i);
	void replace_row(int row_to_replace);
	void replace_column(int col_to_replace);
     void echleon();
	void print_mat();

private:
	vector<int> mat;
	int row, column;
};