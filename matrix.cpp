#include<iostream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include"matrix.h"
using namespace std;

void Matrix::init() 
{
     char choice;

     cout << "do you want to fill the matrix (y/n): ";
     cin >> choice;
     while (!(choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')) {
          cout << "enter a valid input!\n: ";
          cin >> choice;
     }

     int temp;
     if (choice == 'Y' || choice == 'y') {
          cout << "\nenter the matrix with the rows being changed with a new line and the columns separated with a space\n"
               << "for example (two rows and three columns): \n\ta b c\n\td e f\n\n";
          for (int i = 0; i < (row * column); i++) {
               cin >> temp;
               if (is_digit(temp) == true)
                    mat.push_back(temp);
               else {
                    cout << "error. try again\n";
                    i--;
               }
          }
     }
     else if (choice == 'N' || choice == 'n') {
          for (int i = 0; i < (row * column); i++)
                    mat.push_back(0);
     }
}

bool Matrix::is_digit(int value)
{
     if (cin.fail()) return false;
     return true;
}

int Matrix::dimension()
{
     return column;
}

void Matrix::add(Matrix to_add)
{
     if (!(column == to_add.get_column() && row == to_add.get_row())) {
          cout << "cannot add with different rows and/or column\n";
          return;
     }
     vector<int> temp = to_add.get_mat();
     for (int i = 0; i < (row * column); i++)
          mat[i] = mat[i] + temp[i];
}

void Matrix::sub(Matrix to_sub)
{
     if (!(column == to_sub.get_column() && row == to_sub.get_row())) {
          cout << "cannot subtract with different rows and/or column\n";
          return;
     }
     vector<int> temp = to_sub.get_mat();
     for (int i = 0; i < (row * column); i++)
          mat[i] = mat[i] - temp[i];
}

Matrix Matrix::mul(Matrix to_mult)
{
	vector<int> temp;
	if (this->column != to_mult.get_row()) {
		for (int i = 0; i < (this->row * to_mult.get_column()); i++)
			temp.push_back(-1);
		cout << "multiplication not defined. returned matrix with elements as -1.\n";

	}
	else {
		int value, i, j, k;
		vector<int> other = to_mult.get_mat();

		for (i = 0; i < this->row; i++) {
			for (j = 0; j < to_mult.get_column(); j++) {
			  value = 0;
				for (k = 0; k < this->column; k++) {
				  value += this->mat[(i*column) + k] * other[k * to_mult.get_column() + j];
				}
				temp.push_back(value);
			}
		}
	}
	return Matrix(temp, this->row, to_mult.get_column());
}

Matrix Matrix::scalar_mult(int scalar)
{
	vector<int> temp = get_mat();
	for (int i = 0; i < (row * column); i++) 
		temp[i] *= scalar;

	return Matrix(temp, get_row(), get_column());
}

vector<int> Matrix::get_row(int i)
{
     i -= 1;
     vector<int> temp(this->mat.begin() + (row * i), this->mat.begin() + row * (i + 1));
     return temp;
}

vector<int> Matrix::get_column(int i)
{
     i -= 1;
     vector<int> temp;
     for (int j = i; j < row * column; j += column)
          temp.push_back(mat[j]);
     return temp;
}

void Matrix::replace_row(int row_to_replace)
{
     cout << "enter " << column << " new values for the row " << row_to_replace << " in a sequence: ";
     row_to_replace -= 1;
     int temp;
     for (int i = row_to_replace * column; i < (row_to_replace * column) + column; i++) {
          cin >> temp;
          if (is_digit(temp) == true)
               mat[i] = temp;
          else {
               cout << "error. try again\n";
               i--;
          }
     }
}

void Matrix::replace_column(int col_to_replace)
{
     cout << "enter " << row << " new values for the column " << col_to_replace << " in a sequence: ";
     col_to_replace -= 1;
     int temp;
     for (int i = col_to_replace; i < row * column; i += column) {
          cin >> temp;
          if (is_digit(temp) == true)
               mat[i] = temp;
          else {
               cout << "error. try again\n";
               i--;
          }
     }
}

void Matrix::echleon()
{
     const int nrows = this->row;
     const int ncols = this->column; // number of columns
     vector<double> A(mat.begin(), mat.end());//access the vector of the matrix

                                              /*exception when first element is 0 */
     if (int(A[0]) == 0) {
          cout << "cannot handle as the element at [0,0] is 0...\n";
          return;
     }

     double *temp = new double[ncols];
     int levelRow, lead = 0, count = 0;
     while (count < nrows) {
          double d, m;
          levelRow = 0;
          for (int r = 0; r < nrows; r++) { // for each row ...
                                            // calculate divisor and multiplier
               d = A[lead];
               m = A[count + r*column] / d;
               for (int c = 0; c < ncols; c++) { // for each column ...
                    if (r == count) {
                         temp[c] = A[ncols*levelRow + c];
                         temp[c] /= d; // make pivot = 1
                    }
                    else A[ncols*levelRow + c] -= A[count*ncols + c] * m;  // make other = 0
               }
               if (r == count) {
                    for (int c = 0; c < ncols; c++) {
                         A[ncols*levelRow + c] = temp[c];
                    }
               }
               levelRow++;
          }
          lead += ncols + 1;
          count++;
          cout << "\nPrinting the changes in the process: \n";
          for (int i = 0; i < ncols*nrows; i++) {
               if (i % ncols == 0)
                    cout << endl;
               cout << A[i] << "   ";
          }
          cout << endl;
     }

     for (int i = 0; i < A.size(); i++)
          mat[i] = int(ceil(A[i]));
     cout << endl;
}

void Matrix::print_mat()
{
     for (int i = 0; i < (row * column); i++) {
          cout << setw(6) << left << mat[i] << "  ";
          if ((i + 1) % this->column == 0)
               cout << endl;
     }
}
