#include <iostream>
#include <fstream> 
using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    Matrix(int size = 0) : matrix_size(size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size]();
        }
    }

    Matrix(const Matrix& other) : matrix_size(other.matrix_size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;

        matrix_size = other.matrix_size;

        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }
};

void read_matrices_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: File could not be opened." << endl;
        return;
    }

    int size;
    file >> size;
    matrix_1 = Matrix(size);
    matrix_2 = Matrix(size);

    // Read Matrix 1
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix_1.matrix_data[i][j];
        }
    }

    // Read Matrix 2
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix_2.matrix_data[i][j];
        }
    }

    file.close();
}

void print_matrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.matrix_size; ++i) {
        for (int j = 0; j < matrix.matrix_size; ++j) {
            cout << matrix.matrix_data[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    Matrix result(matrix_1.matrix_size);
    for (int i = 0; i < matrix_1.matrix_size; ++i) {
        for (int j = 0; j < matrix_1.matrix_size; ++j) {
            result.matrix_data[i][j] = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
        }
    }
    return result;
}

Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    Matrix result(matrix_1.matrix_size);
    for (int i = 0; i < matrix_1.matrix_size; ++i) {
        for (int j = 0; j < matrix_2.matrix_size; ++j) {
            result.matrix_data[i][j] = 0;
            for (int k = 0; k < matrix_1.matrix_size; ++k) {
                result.matrix_data[i][j] += matrix_1.matrix_data[i][k] * matrix_2.matrix_data[k][j];
            }
        }
    }
    return result;
}

void get_both_diagonal_sums(const Matrix& matrix) {
    double main_diagonal_sum = 0;
    double secondary_diagonal_sum = 0;

    for (int i = 0; i < matrix.matrix_size; ++i) {
        main_diagonal_sum += matrix.matrix_data[i][i];  // Main diagonal
        secondary_diagonal_sum += matrix.matrix_data[i][matrix.matrix_size - i - 1];  // Secondary diagonal
    }

     // If the matrix has an odd size subtract the middle element once 
    if (matrix.matrix_size % 2 == 1) {
        int middle_index = matrix.matrix_size / 2;
    }

    cout << "Main diagonal sum: " << main_diagonal_sum << endl;
    cout << "Secondary diagonal sum: " << secondary_diagonal_sum << endl;
    cout << "Total Sum: " << main_diagonal_sum + secondary_diagonal_sum << endl;
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    for (int j = 0; j < matrix.matrix_size; ++j) {
        double temp = matrix.matrix_data[row1][j];
        matrix.matrix_data[row1][j] = matrix.matrix_data[row2][j];
        matrix.matrix_data[row2][j] = temp;
    }
}

int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrices_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "Matrix 1:" << endl;
    print_matrix(matrix_1);
    cout << "Matrix 2:" << endl;
    print_matrix(matrix_2);

    // Addition
    cout << "Addition result:" << endl;
    Matrix add_result = add_matrices(matrix_1, matrix_2);
    print_matrix(add_result);

    // Multiplication
    cout << "Multiplication result:" << endl;
    Matrix multiply_result = multiply_matrices(matrix_1, matrix_2);
    print_matrix(multiply_result);

    // Diagonal sum
    get_both_diagonal_sums(matrix_1);

    // Swap rows
    cout << "Swapping rows 0 and 1." << endl;
    swap_matrix_row(matrix_1, 0, 1);
    cout << "Matrix 1 after row swap:" << endl;
    print_matrix(matrix_1);

    return 0;
}
