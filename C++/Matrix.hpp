//  Matrix.hpp
//  Matrix
//
//  Created by Joshua Smith on 12/22/15.
//  Copyright © 2015 Joshua Smith. All rights reserved.

#ifndef Matrix_h
#define Matrix_h

#include <cstring>
#include <cassert>
#include <iomanip>
#include <vector>

enum Type {Identity};

template<typename T>
class Matrix {
private:
    int numRows;
    int numCols;
    
    void setContents(std::vector<std::vector<T>> const & initial){
        contents.resize(initial.size());
        
        for(int i=0;i<contents.size();++i){
            contents[i].resize(initial[i].size());
        }
        
        for(int i=0;i<contents.size();++i){
            for(int j=0;j<contents[i].size();++j){
                contents[i][j] = initial[i][j];
            }
        }
    }

//Helper Functions for finding the determinant--------------------------------------------------------------------
    std::vector<std::vector<T> > subContent(std::vector<std::vector<T> > original,int rowDel,int colDel){
        for(int i=0;i<original.size();++i){
            for(int j=colDel-1;j<original[i].size()-1;++j){
                original[i][j] = original[i][j+1];
            }
            original[i].pop_back();
        }
        
        for(int i=0;i<original[0].size();++i){
            for(int j=rowDel-1;j<original.size()-1;++j){
                original[j][i] = original[j+1][i];
            }
        }
        original.pop_back();
        return original;
    }

    T det(std::vector<std::vector<T> > matrix,int m,int n){
        if(n==1) return matrix[0][0];
        if(n==2) return (matrix[0][0]*matrix[1][1])-(matrix[1][0]*matrix[0][1]);
        
        T determinant=0;
        int sign = 1;
        for(int i=n-1;i>=0;--i){
            if((i+m-1)%2) sign = -1;
            else sign = 1;
            determinant += sign*matrix[m-1][i]*det(subContent(matrix,m,i+1),m-1,n-1);
        }
        return determinant;
    }
//----------------------------------------------------------------------------------------------------------------
public:
    std::vector<std::vector<T>> contents;
    
    //Constructors-----------------------------------------------------
    Matrix(){
        this->numRows=0;
        this->numCols=0;
    }
    
    Matrix(std::vector<std::vector<T>> const & initial){
        this->setContents(initial);
        this->numRows = int(initial.size());
        this->numCols = int(initial[0].size());
    }
    
    Matrix(Matrix const & initial){
        this->contents = initial.contents;
        this->numRows = initial.getNumRows();
        this->numCols = initial.getNumCols();
    }
    
    Matrix(Type type,int dim){
        switch(type){
            case Identity:
                contents.resize(dim);
                this->numRows = dim;
                this->numCols = dim;
                for(int i=0;i<dim;++i){
                    contents[i].resize(dim);
                    contents[i][i] = 1;
                }
                break;
        }
    }
    //----------------------------------------------------------------
    
//Overloaded operators for matrices--------------------------------------------------
    Matrix & operator=(Matrix const & rhs){
        this->setContents(rhs.contents);
        this->numRows = rhs.getNumRows();
        this->numCols = rhs.getNumCols();
        return *this;
    }
    
    Matrix & operator*=(Matrix & rhs){
        int m1,n1,m2,n2;
        m1 = this->getNumRows();
        n1 = this->getNumCols();
        m2 = rhs.getNumRows();
        n2 = rhs.getNumCols();
        assert(n1==m2);
        std::vector<std::vector<T> > resContent;
        resContent.resize(m1);
        for(int i=0;i<m1;++i) resContent[i].resize(n2);
        
        T sum = 0;
        for(int i=0;i<m1;++i){
            for(int j=0;j<n2;j++){
                sum = 0;
                for(int k=0;k<n1;++k){
                    sum+=(this->contents[i][k]*rhs(k,j));
                }
                resContent[i][j] = sum;
            }
        }
        
        this->setContents(resContent);
        return *this;
    }
    
    //Reference a single value in a matrix by row and column
    T & operator()(int x, int y){
        return this->contents[x-1][y-1];
    }
//-----------------------------------------------------------------------------------
    
    //Return the determinant of the matrix
    T det(){
        int m = this->numRows;
        int n = this->numCols;
        assert(m==n);
        return det(this->contents,m,n);
    }
    
    int getNumRows() const{
        return this->numRows;
    }
    
    int getNumCols() const{
        return this->numCols;
    }
    
//Add a row or a column of zeros to a matrix-----------------------------------------
    void addRow(int num){
        std::vector<T> dummy;
        for(int i=0;i<num;++i){
            this->contents.push_back(dummy);
            this->contents.back().resize(this->contents[0].size());
        }
        numRows+=num;
    }
    
    void addRow(){
        std::vector<T> dummy;
        this->contents.push_back(dummy);
        this->contents.back().resize(this->contents[0].size());
        numRows++;
    }
    
    void addCol(int num){
        T dummy = NULL;
        for(int i=0;i<this->contents.size();++i){
            for(int j=0;j<num;++j){
                this->contents[i].push_back(dummy);
            }
        }
        numCols+=num;
    }
    
    void addCol(){
        T dummy = NULL;
        for(int i=0;i<this->contents.size();++i){
            this->contents[i].push_back(dummy);
        }
        numCols++;
    }
//------------------------------------------------------------------------------------

};

//std::cout a matrix--------------------------------------------------------
template<typename H>
std::ostream & operator<<(std::ostream & os, Matrix<H> const & matrix){
    int buffer = 5;
    for(int i=0;i<matrix.contents.size();++i){
        os << "|";
        for(int j=0;j<matrix.contents[i].size();++j){
            os << std::setw(buffer) << matrix.contents[i][j];
        }
        os << std::setw(buffer) << "|" << std::endl;
    }
    
    return os;
}

//Matrix Multiplication------------------------------------------------------
template <typename T>
Matrix<T> operator*(Matrix<T> & first, Matrix<T> & second){
    int m1,n1,m2,n2;
    m1 = first.getNumRows();
    n1 = first.getNumCols();
    m2 = second.getNumRows();
    n2 = second.getNumCols();
    assert(n1==m2);
    std::vector<std::vector<T> > resContent;
    resContent.resize(m1);
    for(int i=0;i<m1;++i) resContent[i].resize(n2);
    
    T sum = 0;
    for(int i=0;i<m1;++i){
        for(int j=0;j<n2;j++){
            sum = 0;
            for(int k=0;k<n1;++k){
                sum+=(first(i,k)*second(k,j));
            }
            resContent[i][j] = sum;
        }
    }
    Matrix<T> result(resContent);
    return result;
}

//Multiply a matrix by a scalar------------------------------------------------
template <typename T>                                                       //-
Matrix<T> operator*(T scalar,Matrix<T> & matrix){                           //-
    int m2 = matrix.getNumRows();                                           //-
    int n2 = matrix.getNumCols();                                           //-
    std::vector<std::vector<T> > resContent;                                //-
    resContent.resize(m2);                                                  //-
                                                                            //-
    for(int i=0;i<m2;++i){                                                  //-
        resContent[i].resize(n2);                                           //-
        for(int j=0;j<n2;++j){                                              //-
            resContent[i][j] = scalar*matrix(i,j);                          //-
        }                                                                   //-
    }                                                                       //-
    Matrix<T> result(resContent);                                           //-
    return result;                                                          //-
}                                                                           //-
                                                                            //-
template <typename T>                                                       //-
Matrix<T> operator*(Matrix<T> & matrix,T scalar){                           //-
    int m2 = matrix.getNumRows();                                           //-
    int n2 = matrix.getNumCols();                                           //-
    std::vector<std::vector<T> > resContent;                                //-
    resContent.resize(m2);                                                  //-
                                                                            //-
    for(int i=0;i<m2;++i){                                                  //-
        resContent[i].resize(n2);                                           //-
        for(int j=0;j<n2;++j){                                              //-
            resContent[i][j] = scalar*matrix(i,j);                          //-
        }                                                                   //-
    }                                                                       //-
    Matrix<T> result(resContent);                                           //-
    return result;                                                          //-
}                                                                           //-
//-----------------------------------------------------------------------------

//Return a submatrix of "matrix" without row # rowDel and col # colDel---------
template <typename T>
Matrix<T> subMatrix(Matrix<T> matrix,int rowDel,int colDel){
    assert(rowDel<=matrix.contents.size() && rowDel>0);
    assert(colDel<=matrix.contents[0].size() && colDel>0);
    
    for(int i=0;i<matrix.contents.size();++i){
        for(int j=colDel-1;j<matrix.contents[i].size()-1;++j){
            matrix.contents[i][j] = matrix.contents[i][j+1];
        }
        matrix.contents[i].pop_back();
    }
    
    for(int i=0;i<matrix.contents[0].size();++i){
        for(int j=rowDel-1;j<matrix.contents.size()-1;++j){
            matrix.contents[j][i] = matrix.contents[j+1][i];
        }
    }
    matrix.contents.pop_back();
    Matrix<T> resultant(matrix.contents);
    return resultant;
}
//-----------------------------------------------------------------------------
#endif /* Matrix_h */
