#ifndef MACIERZE_H
#define MACIERZE_H
#include <QTableWidget>
class matrix{
private:
    int rows;
    int cols;
    double **tab;
public:
    matrix(int , int );
    ~matrix();
    void set(int ,int ,double );
    double get(int ,int );
    int getCols();
    int getRows();
    void fillRandom();
    void multiplyByNumber(double);
    double findDeterminate();
    void findMinor(matrix *, matrix *, int , int);
    matrix* findCholeskyDecomposition();
    void findLuDecomposition(matrix *,matrix *);
    bool checkSymmetry();
    bool checkForPositiveDefiniteness();
    matrix* findCofactor();
    matrix* transposeMatrix();
    matrix* operator+(matrix &);
    matrix* operator-(matrix &);
    matrix* operator*(matrix &);
};

#endif // MACIERZE_H
