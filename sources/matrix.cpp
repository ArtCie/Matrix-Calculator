#include "../include/matrix.h"
#include "exceptions.cpp"
#include <QRandomGenerator>
#include <iostream>
matrix::matrix(int wwiersze, int kkolumny)
{
    rows=wwiersze;
    cols=kkolumny;
    tab=new double*[rows+1];
    for(int i=0;i<rows;i++)
    {
        tab[i]=new double[cols+1];
        for(int j=0;j<cols;j++)
        {
            tab[i][j]=0;
        }
    }
}

matrix::~matrix(){
    for(int i=0;i<this->rows;i++)
    {
        delete [] this->tab[i];
    }
    delete [] this->tab;
    delete this;
}

void matrix::set(int n, int m, double val)
{
    tab[n][m]=val;
}

double matrix::get(int n, int m)
{
    return tab[n][m];
}

int matrix::getCols()
{
    return cols;
}

int matrix::getRows()
{
    return rows;
}

matrix* matrix::operator+(matrix &tempSecondMatrix)
{
    if(this->cols != tempSecondMatrix.cols || this->rows != tempSecondMatrix.rows)
    {
        ErrorWrongSize errorSize;
        throw errorSize;
    }
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            this->tab[i][j]=this->tab[i][j]+tempSecondMatrix.tab[i][j];
        }
    }
    return this;
}

matrix* matrix::operator-(matrix &tempSecondMatrix)
{
    if(this->cols != tempSecondMatrix.cols || this->rows != tempSecondMatrix.rows)
    {
        ErrorWrongSize errorSize;
        throw errorSize;
    }
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            this->tab[i][j]=this->tab[i][j]-tempSecondMatrix.tab[i][j];
        }
    }
    return this;
}

matrix* matrix::operator*(matrix &tempSecondMatrix)
{
    if(tempSecondMatrix.rows!=this->cols)
    {
        ErrorWrongMultiplication error;
        throw error;
    }
    matrix *tempM=new matrix(this->rows,tempSecondMatrix.cols);
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<tempSecondMatrix.cols;j++)
        {
            double wyn=0;
            for(int k=0;k<this->cols;k++)
            {
                wyn=wyn+this->tab[i][k]*tempSecondMatrix.tab[k][j];
            }
            tempM->tab[i][j]=wyn;
        }
    }
    return tempM;
}

void matrix::fillRandom()
{
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<this->cols;j++)
        {
            double x=QRandomGenerator::global()->generate()%10;
            double y=QRandomGenerator::global()->generate()%10;
            x=x+(y/10);
            this->set(i,j,x);
        }
    }
}

void matrix::multiplyByNumber(double num) {
    double valNumber;
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<this->cols;j++)
        {
            valNumber=this->tab[i][j]*num;
            this->tab[i][j]=valNumber;
        }
    }
}

matrix* matrix::transposeMatrix() {
    matrix *tempM=new matrix(this->cols,this->rows);
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<this->cols;j++)
        {
            tempM->tab[j][i]=this->tab[i][j];
        }
    }
    return tempM;
}

double matrix::findDeterminate()
{
    int tempRows=this->rows;
    int tempCols=this->cols;
    if(tempRows!=tempCols)
    {
        ErrorNotSquared error;
        throw error;
    }
    if(tempRows>8)
    {
        detTooBig error;
        throw error;
    }
    double det=0;
    if(tempRows==1)
    {
        return this->tab[0][0];
    }
    if(tempRows==2)
    {
        double smallDet=this->tab[0][0]*this->tab[1][1]-this->tab[0][1]*this->tab[1][0];
        det=det+smallDet;
        return det;
    }
    for(int i=0;i<tempCols;i++)
    {
        int x=tempCols-1;
        int y=tempRows-1;
        matrix *minorMatrix=new matrix(x,y);
        findMinor(this,minorMatrix,0,i);
        if(i%2==0)
        {
            det=det+this->tab[i][0]*minorMatrix->findDeterminate();
        }
        else
        {
            det=det-this->tab[i][0]*minorMatrix->findDeterminate();
        }
    }
    return det;
}

void matrix::findMinor(matrix *NewMatrix, matrix *minor, int removeX, int removeY){
    int tempRows=NewMatrix->getRows();
    int tempCols=NewMatrix->getCols();
    int tempI=0,tempJ=0;
    for(int i=0;i<tempRows;i++)
    {
        for(int j=0;j<tempCols;j++)
        {

            if(i==removeX && i+1<tempCols)
            {
                i++;
            }
            if(j==removeY && j+1<tempRows)
            {
                j++;
            }

            double num=NewMatrix->get(j,i);
            QString x=QString::number(tempI);
            QString y=QString::number(tempJ);
            minor->set(tempI,tempJ,num);
            tempJ++;
            if(tempJ==(tempCols-1))
            {
                break;
            }
        }
        tempJ=0;
        tempI++;
        if(tempI==(tempRows-1))
        {
            return;
        }
    }
}

matrix* matrix::findCofactor()
{
    matrix *wyn=new matrix(this->rows,this->cols);
    if(this->rows!=this->cols)
    {
        ErrorNotSquared error;
        throw error;
    }
    if(this->rows==2)
    {
        double swap1=this->tab[0][0];
        double swap2=this->tab[0][1];
        this->tab[0][0]=this->tab[1][1];
        this->tab[1][1]=swap1;
        this->tab[0][1]=this->tab[1][0];
        this->tab[1][0]=swap2;
        return this;
    }
    else{

        for(int i=0;i<this->rows;i++)
        {
            for(int j=0;j<this->cols;j++) {
                matrix *tempMatrix;
                tempMatrix = this->transposeMatrix();
                matrix *minor = new matrix(this->rows - 1, this->cols - 1);
                findMinor(tempMatrix, minor, i, j);
                double result = minor->findDeterminate();
                wyn->tab[i][j] = result;
            }
        }
    }
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<this->cols;j++)
        {
            if((i+j)%2!=0)
            {
                wyn->tab[i][j]=wyn->tab[i][j]*(-1);

            }
        }
    }
    return wyn;
}

void matrix::findLuDecomposition(matrix *L,matrix *U){
    if(this->rows!=this->cols)
    {
        ErrorNotSquared error;
        throw error;
    }
    for(int i=0;i<this->cols;i++)
    {
        for(int j=0;j<this->rows;j++)
        {
            U->tab[i][j]=0;
            L->tab[i][j]=0;
        }
    }
    for(int i=0;i<this->cols;i++)
    {
        U->tab[0][i]=this->tab[0][i];
    }
    for(int i=0;i<this->cols;i++)
    {
        L->tab[i][i]=1;
    }
    for(int i=1;i<this->cols;i++)
    {
        for(int j=i-1;j<this->rows-1;j++)
        {
            if(this->tab[i-1][i-1]==0)
            {
                ErrorLU error1;
                throw error1;
            }
            double factor=this->tab[j+1][i-1]/this->tab[i-1][i-1];
            L->tab[j+1][i-1]=factor;
            for(int k=0;k<this->cols;k++)
            {
                this->tab[j+1][k]=this->tab[j+1][k]-factor*this->tab[i-1][k];
                if(j+1<=k)
                {
                    U->tab[j+1][k]=this->tab[j+1][k];
                }
            }
        }
    }
}

bool matrix::checkSymmetry() {
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(this->tab[i][j]!=this->tab[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

bool matrix::checkForPositiveDefiniteness(){
    bool exit=false;
    if(this->cols==1)
    {
        if(this->tab[0][0]>0)
        {
            return true;
        }
    }
    double wyn=this->findDeterminate();
    if(wyn>0)
    {
        matrix *newMatrix=new matrix(this->cols - 1, this->rows - 1);
        for(int i=0;i<newMatrix->rows;i++)
        {
            for(int j=0;j<newMatrix->rows;j++)
            {
                newMatrix->tab[i][j]=this->tab[i][j];
            }
        }
        exit=newMatrix->checkForPositiveDefiniteness();
    }
    return exit;

}

matrix* matrix::findCholeskyDecomposition(){
    matrix *tempL=new matrix(this->rows,this->cols);
    matrix *tempLResult=new matrix(this->rows,this->cols);
    for(int i=0;i<this->rows;i++)
    {
        for(int j=0;j<=i;j++)
        {
            double wyn=this->tab[i][j];
            if(i==j)
            {
                for(int k=0;k<i;k++)
                {
                    wyn=wyn-(tempL->get(i,k)*tempL->get(i,k));
                }
                wyn=sqrt(wyn);
                tempL->set(i,j,wyn);
            }
            else
            {
                for(int k=0;k<=j;k++)
                {
                    wyn=wyn-(tempL->get(i,k)*tempL->get(j,k));
                }
                wyn=wyn/tempL->get(j,j);
                tempL->set(i,j,wyn);
            }
            tempLResult->tab[i][j]=wyn;
        }
    }
    for(int i=0;i<this->rows;i++)
    {
        for(int j=i+1;j<this->rows;j++)
        {
            tempLResult->tab[i][j]=0;
        }
    }
    return tempLResult;

}