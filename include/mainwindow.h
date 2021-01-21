#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../include/matrix.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include <QTableWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QObject>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addColFunA();
    void addRowFunA();
    void removeColFunA();
    void removeRowFunA();
    void addDegreeFunA();
    void removeDegreeFunA();
    void addColFunB();
    void addRowFunB();
    void removeColFunB();
    void removeRowFunB();
    void addDegreeFunB();
    void removeDegreeFunB();
    void addMatrixFun();
    void subtractMatrixFun();
    void setMatrixesFun();
    void multiplyMatrixFun();
    void multiplyByNumberFun();
    void transposeMatrixFun();
    void determinantFun();
    void cofactorFun();
    void inverseFun();
    void LuDecompositionFun();
    void isSymmetricFun();
    void CholeskyDecompositionFun();
    void checkArgFun(QTableWidgetItem *);


private:
    void static reshapeTable(int,QTableWidget *);
    void multiplyChosenMatrix(QTableWidget *);
    void static transposeChosenMatrix(QTableWidget *);
    void static fillTempMatrix(QTableWidget *, matrix *);
    void changeLabels(std::string const&,std::string const&,std::string const&,std::string const&,std::string const&);
    void static fillResultTable(QTableWidget *,matrix *);
    QTableWidget * checkWhich();
    QTableWidget *matrixA;
    QTableWidget *matrixB;
    QTableWidget *matrixResult;
    QLabel *determinantResult;
    QLabel *symmetricResult;
    QPushButton *addColumnA;
    QPushButton *addRowA;
    QPushButton *removeColumnA;
    QPushButton *removeRowA;
    QPushButton *addDegreeA;
    QPushButton *removeDegreeA;
    QPushButton *addColumnB;
    QPushButton *addRowB;
    QPushButton *removeColumnB;
    QPushButton *removeRowB;
    QPushButton *addDegreeB;
    QPushButton *removeDegreeB;
    QPushButton *addMatrix;
    QPushButton *subtractMatrix;
    QPushButton *setMatrixes;
    QPushButton *multiplyMatrix;
    QPushButton *multiplyByNumber;
    QSlider *chooseMatrix;
    QLabel *instruction;
    QLabel *letters;
    QLabel *headerMatrixA;
    QLabel *headerMatrixB;
    QLabel *headerMatrixResult;
    QLabel *operationOne;
    QLabel *operationTwo;
    QSpinBox *chooseNumber;
    QPushButton *transposeMatrix;
    QPushButton *determinant;
    QPushButton *cofactor;
    QPushButton *inverse;
    QPushButton *LuDecomposition;
    QPushButton *isSymmetric;
    QPushButton *CholeskyDecomposition;

};
#endif // MAINWINDOW_H
