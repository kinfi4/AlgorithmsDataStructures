//
// Created by kinfi4 on 4/9/21.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>

using namespace std;


class SquareMatrix{
public:
    SquareMatrix(int ndim, double initValue=0){
        this->ndim = ndim;
        for (int i = 0; i < ndim; ++i) {
            auto row = vector<double>(ndim, initValue);
            this->matrix.push_back(row);
        }
    }
    SquareMatrix(vector<vector<double>> matrix){
        if(matrix.size() != matrix[0].size())
            throw invalid_argument("Matrix must be squared");

        this->ndim = matrix.size();
        this->matrix = matrix;
    }
    ~SquareMatrix(){
        this->matrix.clear();
    }

    void print_matrix(){
        for(auto& row : this->matrix){
            for(auto& value : row)
                cout << value << " ";

            cout << endl;
        }
    }

    SquareMatrix get_inverse_matrix(){
        auto inverse_matrix = SquareMatrix(this->ndim);
        for (int i = 0; i < inverse_matrix.ndim; ++i) {
            for (int j = 0; j < inverse_matrix.ndim; ++j) {
                inverse_matrix[j][i] = pow(-1, i + j) * this->_get_det_for_minor(vector<int>{i}, vector<int>{j});
            }
        }

        inverse_matrix / this->get_determinant();

        return inverse_matrix;
    }
    double get_determinant(){
        double res = 0;
        for (int i = 0; i < this->ndim; ++i) {
            res += pow(-1, 0 + i) * this->matrix[0][i] * this->_get_det_for_minor(vector<int>{0}, vector<int>{i});
        }

        return res;
    }

    vector<double>& operator [] (int index){
        return this->matrix[index];
    }
    void operator++(int){
        for(auto& row : this->matrix)
            for(auto& el : row)
                el++;
    }
    void operator--(int){
        for(auto& row : this->matrix)
            for(auto& el : row)
                el--;
    }

    SquareMatrix operator+(SquareMatrix& another){
        if(this->ndim != another.ndim)
            throw invalid_argument("Matrix must have the same dim for summing");

        auto new_matrix = SquareMatrix(this->ndim);
        for (int i = 0; i < this->ndim; ++i) {
            for (int j = 0; j < this->ndim; ++j) {
                new_matrix[i][j] = this->matrix[i][j] + another[i][j];
            }
        }

        return new_matrix;
    }
    SquareMatrix operator-(SquareMatrix& another){
        if(this->ndim != another.ndim)
            throw invalid_argument("Matrix must have the same dim for summing");

        auto new_matrix = SquareMatrix(this->ndim);
        for (int i = 0; i < this->ndim; ++i) {
            for (int j = 0; j < this->ndim; ++j) {
                new_matrix[i][j] = this->matrix[i][j] - another[i][j];
            }
        }

        return new_matrix;
    }
    SquareMatrix operator * (double number){
        auto new_matrix = SquareMatrix(this->ndim);
        for (int i = 0; i < new_matrix.ndim; ++i) {
            for (int j = 0; j < new_matrix.ndim; ++j) {
                new_matrix[i][j] = this->matrix[i][j] * number;
            }
        }

        return new_matrix;
    }
    SquareMatrix operator / (double number){
        auto new_matrix = SquareMatrix(this->ndim);
        for (int i = 0; i < new_matrix.ndim; ++i) {
            for (int j = 0; j < new_matrix.ndim; ++j) {
                new_matrix[i][j] = this->matrix[i][j] / number;
            }
        }

        return new_matrix;
    }

    bool operator == (SquareMatrix& another){
        if(this->ndim != another.ndim)
            return false;

        for (int i = 0; i < this->ndim; ++i) {
            for (int j = 0; j < this->ndim; ++j) {
                if(this->matrix[i][j] != another[i][j])
                    return false;
            }
        }

        return true;
    }
    void operator *= (double number){
        for(auto& row : this->matrix)
            for(auto& value : row)
                value *= number;
    }
    void operator /= (double number){
        for(auto& row : this->matrix)
            for(auto& value : row)
                value /= number;
    }

private:
    int ndim;
    vector<vector<double>> matrix;

    double _get_det_for_minor(vector<int> deleted_rows, vector<int> deleted_cols){
        double res = 0;

        if(deleted_cols.size() == this->ndim - 1)
            return this->_find_intersected_element(deleted_rows, deleted_cols);

        int cur_row = 0;
        for (int i = 0; i < this->ndim; ++i)
            if(not count(deleted_rows.begin(), deleted_rows.end(), i)){
                cur_row = i;
                break;
            }

        deleted_rows.push_back(cur_row);

        int count_column_index = 0;
        for (int i = 0; i < this->ndim; ++i) {
            if(not count(deleted_cols.begin(), deleted_cols.end(), i)){
                auto new_deleted_columns = deleted_cols;
                new_deleted_columns.push_back(i);

                res += pow(-1, 0 + count_column_index) * this->matrix[cur_row][i] * this->_get_det_for_minor(deleted_rows, new_deleted_columns);
                count_column_index++;
            }
        }

        return res;
    }
    double _find_intersected_element(vector<int>& deleted_rows, vector<int>& deleted_cols){
        for (int i = 0; i < this->ndim; ++i) {
            if(not count(deleted_rows.begin(), deleted_rows.end(), i))
                for (int j = 0; j < this->ndim; ++j) {
                    if(not count(deleted_cols.begin(), deleted_cols.end(), j))
                        return this->matrix[i][j];
                }
        }
    }
};

#endif //MATRIX_MATRIX_H
