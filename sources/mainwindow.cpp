#include "../include/mainwindow.h"
#include "../sources/exceptions.cpp"
#include <QLabel>
#include <QMessageBox>
#include <QTableWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <iostream>
#include <fstream>
string* handleText();
string *constTexts=handleText();
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    QFont defaultFont(QString::fromStdString(constTexts[0]),10,QFont::StyleNormal);
    QFont boltFont(QString::fromStdString(constTexts[0]),30,QFont::StyleOblique);


    headerMatrixA=new QLabel(this);
    headerMatrixA->setGeometry(20,0,250,40);
    headerMatrixA->setFont(defaultFont);
    headerMatrixA->setText(QString::fromStdString(constTexts[1]));

    headerMatrixB=new QLabel(this);
    headerMatrixB->setGeometry(410,0,250,40);
    headerMatrixB->setFont(defaultFont);
    headerMatrixB->setText(QString::fromStdString(constTexts[2]));

    headerMatrixResult=new QLabel(this);
    headerMatrixResult->setGeometry(810,0,250,40);
    headerMatrixResult->setFont(defaultFont);
    headerMatrixResult->setText(QString::fromStdString(constTexts[3]));

    operationOne=new QLabel(this);
    operationOne->setGeometry(335,100,250,40);
    operationOne->setFont(boltFont);
    operationOne->setStyleSheet(QString::fromStdString(constTexts[4]));

    operationTwo=new QLabel(this);
    operationTwo->setGeometry(735,100,250,40);
    operationTwo->setFont(boltFont);
    operationTwo->setStyleSheet(QString::fromStdString(constTexts[4]));

    matrixA= new QTableWidget(2,2,this);
    matrixA->setEditTriggers(QAbstractItemView::CurrentChanged);
    matrixA->setSelectionBehavior(QAbstractItemView::SelectItems);
    matrixA->setSelectionMode(QAbstractItemView::SingleSelection);
    matrixA->setShowGrid(true);
    reshapeTable(20,matrixA);
    connect(matrixA,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(checkArgFun(QTableWidgetItem *)));

    matrixB = new QTableWidget(2,2,this);
    matrixB->setEditTriggers(QAbstractItemView::CurrentChanged);
    matrixB->setSelectionBehavior(QAbstractItemView::SelectItems);
    matrixB->setSelectionMode(QAbstractItemView::SingleSelection);
    matrixB->setShowGrid(true);
    reshapeTable(410,matrixB);
    connect(matrixB,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(checkArgFun(QTableWidgetItem *)));

    for(int i=0;i<matrixA->rowCount();i++)
    {
        for(int j=0;j<matrixA->columnCount();j++)
        {
            matrixA->setItem(i,j,new QTableWidgetItem(QString::fromStdString(constTexts[5])));
            matrixB->setItem(i,j,new QTableWidgetItem(QString::fromStdString(constTexts[5])));
        }
    }

    matrixResult = new QTableWidget(2,2,this);
    matrixResult->setGeometry(810,30,120,92);
    matrixResult->setEditTriggers(QAbstractItemView::CurrentChanged);
    matrixResult->setSelectionBehavior(QAbstractItemView::SelectItems);
    matrixResult->setSelectionMode(QAbstractItemView::SingleSelection);
    matrixResult->setShowGrid(true);
    reshapeTable(810,matrixResult);

    determinantResult = new QLabel(" ",this);
    determinantResult->setFrameStyle(QFrame::Box);
    determinantResult->setTextInteractionFlags(Qt::TextSelectableByMouse);
    determinantResult->setStyleSheet(QString::fromStdString(constTexts[6]));
    determinantResult->setGeometry(1080,360,55,35);

    symmetricResult = new QLabel(" ",this);
    symmetricResult->setFrameStyle(QFrame::Box);
    symmetricResult->setStyleSheet(QString::fromStdString(constTexts[6]));
    symmetricResult->setGeometry(690,430,40,40);

    setMatrixes=new QPushButton(QString::fromStdString(constTexts[7]),this);
    setMatrixes->setGeometry(920,430,150,70);
    connect(setMatrixes, SIGNAL(clicked()), this, SLOT(setMatrixesFun()));

    addColumnA=new QPushButton(QString::fromStdString(constTexts[8]),this);
    addColumnA->setGeometry(20,220,100,50);
    connect(addColumnA, SIGNAL(clicked()), this, SLOT(addColFunA()));

    addRowA=new QPushButton(QString::fromStdString(constTexts[9]),this);
    addRowA->setGeometry(120,220,100,50);
    connect(addRowA, SIGNAL(clicked()), this, SLOT(addRowFunA()));

    removeColumnA=new QPushButton(QString::fromStdString(constTexts[10]),this);
    removeColumnA->setGeometry(20,270,100,50);
    connect(removeColumnA, SIGNAL(clicked()), this, SLOT(removeColFunA()));

    removeRowA=new QPushButton(QString::fromStdString(constTexts[11]),this);
    removeRowA->setGeometry(120,270,100,50);
    connect(removeRowA, SIGNAL(clicked()), this, SLOT(removeRowFunA()));

    addDegreeA=new QPushButton(QString::fromStdString(constTexts[12]),this);
    addDegreeA->setGeometry(220,220,100,50);
    connect(addDegreeA,SIGNAL(clicked()),this,SLOT(addDegreeFunA()));

    removeDegreeA=new QPushButton(QString::fromStdString(constTexts[13]),this);
    removeDegreeA->setGeometry(220,270,100,50);
    connect(removeDegreeA,SIGNAL(clicked()),this,SLOT(removeDegreeFunA()));

    addColumnB=new QPushButton(QString::fromStdString(constTexts[8]),this);
    addColumnB->setGeometry(410,220,100,50);
    connect(addColumnB, SIGNAL(clicked()), this, SLOT(addColFunB()));

    addRowB=new QPushButton(QString::fromStdString(constTexts[9]),this);
    addRowB->setGeometry(510,220,100,50);
    connect(addRowB, SIGNAL(clicked()), this, SLOT(addRowFunB()));

    removeColumnB=new QPushButton(QString::fromStdString(constTexts[10]),this);
    removeColumnB->setGeometry(410,270,100,50);
    connect(removeColumnB, SIGNAL(clicked()), this, SLOT(removeColFunB()));

    removeRowB=new QPushButton(QString::fromStdString(constTexts[11]),this);
    removeRowB->setGeometry(510,270,100,50);
    connect(removeRowB, SIGNAL(clicked()), this, SLOT(removeRowFunB()));

    addDegreeB=new QPushButton(QString::fromStdString(constTexts[12]),this);
    addDegreeB->setGeometry(610,220,100,50);
    connect(addDegreeB,SIGNAL(clicked()),this,SLOT(addDegreeFunB()));

    removeDegreeB=new QPushButton(QString::fromStdString(constTexts[13]),this);
    removeDegreeB->setGeometry(610,270,100,50);
    connect(removeDegreeB,SIGNAL(clicked()),this,SLOT(removeDegreeFunB()));

    addMatrix=new QPushButton(QString::fromStdString(constTexts[14]),this);
    addMatrix->setGeometry(20,350,150,70);
    connect(addMatrix, SIGNAL(clicked()), this, SLOT(addMatrixFun()));

    subtractMatrix=new QPushButton(QString::fromStdString(constTexts[15]),this);
    subtractMatrix->setGeometry(190,350,150,70);
    connect(subtractMatrix, SIGNAL(clicked()), this, SLOT(subtractMatrixFun()));

    multiplyMatrix=new QPushButton(QString::fromStdString(constTexts[16]),this);
    multiplyMatrix->setGeometry(360,350,150,70);
    connect(multiplyMatrix, SIGNAL(clicked()), this, SLOT(multiplyMatrixFun()));

    multiplyByNumber=new QPushButton(QString::fromStdString(constTexts[17]+"\n"+constTexts[18]),this);
    multiplyByNumber->setGeometry(530,350,150,70);
    connect(multiplyByNumber, SIGNAL(clicked()), this, SLOT(multiplyByNumberFun()));

    chooseMatrix=new QSlider(this);
    chooseMatrix->setOrientation(Qt::Horizontal);
    chooseMatrix->setGeometry(810,290,200,30);
    chooseMatrix->setRange(1,3);
    chooseMatrix->setTickInterval(1);
    chooseMatrix->singleStep();

    letters=new QLabel(this);
    letters->setGeometry(810,258,250,40);
    letters->setFont(defaultFont);
    letters->setText(QString::fromStdString(constTexts[19]+"\t"+constTexts[20]+"\t\t"+constTexts[21]));

    instruction=new QLabel(this);
    instruction->setGeometry(810,220,250,40);
    instruction->setFont(defaultFont);
    instruction->setText(QString::fromStdString(constTexts[22]+"\n"+constTexts[23]));

    chooseNumber=new QSpinBox(this);
    chooseNumber->setGeometry(690,350,50,30);
    chooseNumber->setRange(-100,100);

    transposeMatrix=new QPushButton(QString::fromStdString(constTexts[24]),this);
    transposeMatrix->setGeometry(760,350,150,70);
    connect(transposeMatrix, SIGNAL(clicked()), this, SLOT(transposeMatrixFun()));

    determinant=new QPushButton(QString::fromStdString(constTexts[25]),this);
    determinant->setGeometry(920,350,150,70);
    connect(determinant,SIGNAL(clicked()),this,SLOT(determinantFun()));

    cofactor=new QPushButton(QString::fromStdString(constTexts[26]+"\n"+constTexts[27]),this);
    cofactor->setGeometry(20,430,150,70);
    connect(cofactor,SIGNAL(clicked()),this,SLOT(cofactorFun()));

    inverse=new QPushButton(QString::fromStdString(constTexts[26]+"\n"+constTexts[28]),this);
    inverse->setGeometry(190,430,150,70);
    connect(inverse,SIGNAL(clicked()),this,SLOT(inverseFun()));

    LuDecomposition=new QPushButton(QString::fromStdString(constTexts[29]+"\n"+constTexts[30]),this);
    LuDecomposition->setGeometry(360,430,150,70);
    connect(LuDecomposition,SIGNAL(clicked()),this,SLOT(LuDecompositionFun()));

    CholeskyDecomposition=new QPushButton(QString::fromStdString(constTexts[31]),this);
    CholeskyDecomposition->setGeometry(760,430,150,70);
    connect(CholeskyDecomposition,SIGNAL(clicked()),this,SLOT(CholeskyDecompositionFun()));

    isSymmetric=new QPushButton(QString::fromStdString(constTexts[32]+"\n"+constTexts[33]),this);
    isSymmetric->setGeometry(530,430,150,70);
    connect(isSymmetric,SIGNAL(clicked()),this,SLOT(isSymmetricFun()));

}

MainWindow::~MainWindow()= default;


void MainWindow::checkArgFun(QTableWidgetItem* item){

    try {
        bool check=false;
        item->text().toDouble(&check);
        if(!check)
        {
            item->setText(QString::fromStdString(constTexts[5]));
            ErrorNotNumber error;
            throw error;
        }
    }
    catch(exception &e){
        QMessageBox::critical(this,QString::fromStdString(constTexts[34]),e.what());
    }
}

void MainWindow::addColFunA()
{
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrixA->setColumnCount(matrixA->columnCount()+1);
    reshapeTable(20,matrixA);
    for(int i=0;i<matrixA->rowCount();i++)
    {
        matrixA->setItem(i,matrixA->columnCount()-1,new QTableWidgetItem(QString::fromStdString(constTexts[5])));
    }
}

void MainWindow::addRowFunA()
{
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrixA->setRowCount(matrixA->rowCount()+1);
    reshapeTable(20,matrixA);
    for(int i=0;i<matrixA->columnCount();i++)
    {
        matrixA->setItem(matrixA->rowCount()-1,i,new QTableWidgetItem(QString::fromStdString(constTexts[5])));
    }
}

void MainWindow::removeColFunA()
{
    if(matrixA->columnCount()==1)
    {
        return;
    }
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrixA->setColumnCount(matrixA->columnCount()-1);
    reshapeTable(20,matrixA);
}

void MainWindow::removeRowFunA()
{
    if(matrixA->rowCount()==1)
    {
        return;
    }
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrixA->setRowCount(matrixA->rowCount()-1);
    reshapeTable(20,matrixA);
}

void MainWindow::addDegreeFunA()
{
    addColFunA();
    addRowFunA();
}

void MainWindow::removeDegreeFunA()
{
    removeColFunA();
    removeRowFunA();
}

void MainWindow::addColFunB()
{
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrixB->setColumnCount(matrixB->columnCount()+1);
    reshapeTable(410,matrixB);
    for(int i=0;i<matrixB->rowCount();i++)
    {
        matrixB->setItem(i,matrixB->columnCount()-1,new QTableWidgetItem(QString::fromStdString(constTexts[5])));
    }
}

void MainWindow::addRowFunB()
{
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrixB->setRowCount(matrixB->rowCount()+1);
    reshapeTable(410,matrixB);
    for(int i=0;i<matrixB->columnCount();i++)
    {
        matrixB->setItem(matrixB->rowCount()-1,i,new QTableWidgetItem(QString::fromStdString(constTexts[5])));
    }
}

void MainWindow::addDegreeFunB()
{
    addColFunB();
    addRowFunB();
}

void MainWindow::removeDegreeFunB()
{
    removeColFunB();
    removeRowFunB();
}

void MainWindow::removeColFunB()
{
    if(matrixB->columnCount()==1)
    {
        return;
    }
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrixB->setColumnCount(matrixB->columnCount()-1);
    reshapeTable(410,matrixB);
}

void MainWindow::removeRowFunB() {
    if (matrixB->rowCount() == 1)
    {
        return;
    }
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrixB->setRowCount(matrixB->rowCount() - 1);
    reshapeTable(410,matrixB);
}

void MainWindow::addMatrixFun()
{
    try
    {
        matrix *matrixATemp=new matrix(matrixA->rowCount(), matrixA->columnCount());
        matrix *matrixBTemp=new matrix(matrixB->rowCount(), matrixB->columnCount());
        fillTempMatrix(matrixA,matrixATemp);
        fillTempMatrix(matrixB,matrixBTemp);
        matrix *matrixCTemp;
        matrixCTemp=*matrixATemp+*matrixBTemp;
        changeLabels(constTexts[1],constTexts[2],constTexts[36],constTexts[37],constTexts[38]);
        matrixResult->setRowCount(matrixA->rowCount());
        matrixResult->setColumnCount(matrixA->columnCount());
        reshapeTable(810, matrixResult);
        fillResultTable(matrixResult,matrixCTemp);
    }
    catch(exception &e)
    {
        QMessageBox::critical(this,QString::fromStdString(constTexts[39]),e.what());
    }
}

void MainWindow::subtractMatrixFun()
{
    try
    {
        matrix *matrixATemp=new matrix(matrixA->rowCount(), matrixA->columnCount());
        matrix *matrixBTemp=new matrix(matrixB->rowCount(), matrixB->columnCount());
        fillTempMatrix(matrixA,matrixATemp);
        fillTempMatrix(matrixB,matrixBTemp);
        matrix *matrixCTemp;
        matrixCTemp=*matrixATemp-*matrixBTemp;
        changeLabels(constTexts[1],constTexts[2],constTexts[40],constTexts[41],constTexts[38]);
        matrixResult->setRowCount(matrixA->rowCount());
        matrixResult->setColumnCount(matrixA->columnCount());
        reshapeTable(810, matrixResult);
        fillResultTable(matrixResult,matrixCTemp);
    }
    catch(exception &e)
    {
        QMessageBox::critical(this,QString::fromStdString(constTexts[42]),e.what());
    }
}

void MainWindow::setMatrixesFun(){
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    matrix *tempMatrixA=new matrix(matrixA->rowCount(),matrixA->columnCount());
    matrix *tempMatrixB=new matrix(matrixB->rowCount(),matrixB->columnCount());
    tempMatrixA->fillRandom();
    fillResultTable(matrixA,tempMatrixA);
    tempMatrixB->fillRandom();
    fillResultTable(matrixB,tempMatrixB);
}

void MainWindow::multiplyMatrixFun(){
    try {
        matrix *matrixATemp = new matrix(matrixA->rowCount(), matrixA->columnCount());
        matrix *matrixBTemp = new matrix(matrixB->rowCount(), matrixB->columnCount());
        fillTempMatrix(matrixA, matrixATemp);
        fillTempMatrix(matrixB, matrixBTemp);
        matrix *matrixCTemp;
        matrixCTemp = *matrixATemp * *matrixBTemp;
        matrixResult->setRowCount(matrixA->rowCount());
        matrixResult->setColumnCount(matrixB->columnCount());
        reshapeTable(810, matrixResult);
        changeLabels(constTexts[1],constTexts[2],constTexts[43],constTexts[44],constTexts[38]);
        fillResultTable(matrixResult, matrixCTemp);
    }
    catch(exception &e)
    {
        QMessageBox::critical(this,QString::fromStdString(constTexts[45]),e.what());
    }
}

void MainWindow::multiplyChosenMatrix(QTableWidget * NewMatrix)
{
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    int factor=chooseNumber->value();
    matrix *tempMatrixA=new matrix(NewMatrix->rowCount(),NewMatrix->columnCount());
    fillTempMatrix(NewMatrix,tempMatrixA);
    tempMatrixA->multiplyByNumber(factor);
    fillResultTable(NewMatrix,tempMatrixA);
}

void MainWindow::multiplyByNumberFun(){
    int ChooseOfMatrix=chooseMatrix->value();
    if(ChooseOfMatrix==1)
    {
        multiplyChosenMatrix(matrixA);
    }
    if(ChooseOfMatrix==2)
    {
        multiplyChosenMatrix(matrixB);
    }
    if(ChooseOfMatrix==3)
    {
        multiplyChosenMatrix(matrixResult);
    }
}

void MainWindow::transposeMatrixFun(){
    int ChooseOfMatrix=chooseMatrix->value();
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    if(ChooseOfMatrix==1)
    {
        transposeChosenMatrix(matrixA);
        reshapeTable(20,matrixA);
    }
    if(ChooseOfMatrix==2)
    {
        transposeChosenMatrix(matrixB);
        reshapeTable(410,matrixB);
    }
    if(ChooseOfMatrix==3)
    {
        transposeChosenMatrix(matrixResult);
        reshapeTable(810,matrixResult);
    }
}

void MainWindow::transposeChosenMatrix(QTableWidget *NewMatrix)
{
    matrix *tempMatrix=new matrix(NewMatrix->rowCount(), NewMatrix->columnCount());
    matrix*tempTransposeMatrix;
    fillTempMatrix(NewMatrix,tempMatrix);
    tempTransposeMatrix=tempMatrix->transposeMatrix();
    NewMatrix->setColumnCount(tempTransposeMatrix->getCols());
    NewMatrix->setRowCount(tempTransposeMatrix->getRows());
    fillResultTable(NewMatrix,tempTransposeMatrix);
}

void MainWindow::reshapeTable(const int x,QTableWidget *newMatrix)
{
    if(newMatrix->rowCount()>5 && newMatrix->columnCount()>5)
    {
        newMatrix->setGeometry(x, 30, 270, 182);
    }
    else if(newMatrix->columnCount()<=5 && newMatrix->rowCount()<=5)
    {
        newMatrix->setGeometry(x, 30, 20+newMatrix->columnCount()*50, 32+newMatrix->rowCount()*30);
    }
    else if(newMatrix->columnCount()>5 && newMatrix->rowCount()<=5)
    {
        newMatrix->setGeometry(x, 30, 270, 32+newMatrix->rowCount()*30);
    }
    else{
        newMatrix->setGeometry(x,30,20+newMatrix->columnCount()*50,182);
    }
    for(int i=0;i<newMatrix->columnCount();i++)
    {
        newMatrix->setColumnWidth(i,10);
    }
    for(int j=0;j<newMatrix->rowCount();j++)
    {
        newMatrix->setRowHeight(j,10);
    }
}

void MainWindow::determinantFun()
{
    try {
        changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
        QTableWidget *tempTable = checkWhich();
        double det;
        matrix *tempA = new matrix(tempTable->rowCount(), tempTable->columnCount());
        fillTempMatrix(tempTable, tempA);
        det = tempA->findDeterminate();
        QString detString = QString::number(det);
        determinantResult->setText(detString);
    }
    catch(exception &e)
    {
        QMessageBox::critical(this,QString::fromStdString(constTexts[46]),e.what());
    }

}

void MainWindow::cofactorFun()
{
    try {
        changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
        QTableWidget *tempTable = checkWhich();
        matrix *tempA = new matrix(tempTable->rowCount(), tempTable->columnCount());
        fillTempMatrix(tempTable, tempA);
        matrix *resultMatrix;
        resultMatrix = tempA->findCofactor();
        fillResultTable(tempTable, resultMatrix);
    }
    catch(exception &e)
    {
        QMessageBox::critical(this,QString::fromStdString(constTexts[47]),e.what());
    }

}

void MainWindow::inverseFun()
{
    try {
        QTableWidget *tempTable = checkWhich();
        matrix *tempMatrix = new matrix(tempTable->rowCount(), tempTable->columnCount());
        fillTempMatrix(tempTable, tempMatrix);
        double determinantTemp = tempMatrix->findDeterminate();
        if (determinantTemp == 0) {
            detEqualZero error;
            throw error;
        }
        determinantTemp = 1 / determinantTemp;
        if (tempMatrix->getRows() == 1) {
            tempMatrix->set(0, 0, determinantTemp);
            fillResultTable(tempTable, tempMatrix);
            return;
        }
        matrix *coFactorTempMatrix;
        coFactorTempMatrix = tempMatrix->findCofactor();
        matrix *transposeTempMatrix;
        transposeTempMatrix = coFactorTempMatrix->transposeMatrix();
        transposeTempMatrix->multiplyByNumber(determinantTemp);
        fillResultTable(tempTable, transposeTempMatrix);
    }
    catch(exception &e)
    {
        QMessageBox::critical(this,QString::fromStdString(constTexts[51]),e.what());
    }

}

void MainWindow::LuDecompositionFun()
{
    try {
        QTableWidget *tempTable = checkWhich();
        if (!tempTable) {
            return;
        }
        matrix *matrixDefault = new matrix(tempTable->rowCount(), tempTable->columnCount());
        fillTempMatrix(tempTable, matrixDefault);
        fillResultTable(matrixA, matrixDefault);
        matrix *matrixL = new matrix(tempTable->rowCount(), tempTable->columnCount());
        matrix *matrixU = new matrix(tempTable->rowCount(), tempTable->columnCount());
        matrixDefault->findLuDecomposition(matrixL, matrixU);
        matrixA->setColumnCount(matrixDefault->getCols());
        matrixA->setRowCount(matrixDefault->getRows());
        matrixB->setColumnCount(matrixDefault->getCols());
        matrixB->setRowCount(matrixDefault->getRows());
        matrixResult->setColumnCount(matrixDefault->getCols());
        matrixResult->setRowCount(matrixDefault->getRows());
        reshapeTable(20, matrixA);
        reshapeTable(410, matrixB);
        reshapeTable(810, matrixResult);
        fillResultTable(matrixB, matrixL);
        fillResultTable(matrixResult, matrixU);
        changeLabels(constTexts[53],constTexts[54],constTexts[55],constTexts[38],constTexts[44]);

    }
    catch(exception &e)
    {
        QMessageBox::critical(this,QString::fromStdString(constTexts[56]),e.what());
    }
}

void MainWindow::isSymmetricFun()
{
    changeLabels(constTexts[1],constTexts[2],constTexts[3],constTexts[35],constTexts[35]);
    QTableWidget *tempTable=checkWhich();
    if(!tempTable){
        return;
    }
    matrix *checkMatrix=new matrix(tempTable->rowCount(), tempTable->columnCount());
    fillTempMatrix(tempTable,checkMatrix);
    bool ifTrue=checkMatrix->checkSymmetry();
    if(ifTrue)
    {
        symmetricResult->setText(QString::fromStdString(constTexts[57]));
        symmetricResult->setAlignment(Qt::AlignCenter);
    }
    else{
        symmetricResult->setText(QString::fromStdString(constTexts[58]));
        symmetricResult->setAlignment(Qt::AlignCenter);
    }

}

void MainWindow::CholeskyDecompositionFun()
{
    try {
        QTableWidget *tempTable = checkWhich();
        matrix *tempMatrix = new matrix(tempTable->rowCount(), tempTable->columnCount());
        matrix *tempL;
        matrix *checkForDefinitenessMatrix = new matrix(tempTable->rowCount(), tempTable->columnCount());
        fillTempMatrix(tempTable, checkForDefinitenessMatrix);
        fillTempMatrix(tempTable, tempMatrix);
        if (tempMatrix->checkSymmetry()) {
            if (checkForDefinitenessMatrix->checkForPositiveDefiniteness()) {
                matrixA->setColumnCount(tempMatrix->getCols());
                matrixA->setRowCount(tempMatrix->getCols());
                matrixB->setColumnCount(tempMatrix->getCols());
                matrixB->setRowCount(tempMatrix->getCols());
                matrixResult->setColumnCount(tempMatrix->getCols());
                matrixResult->setRowCount(tempMatrix->getCols());
                reshapeTable(20, matrixA);
                reshapeTable(410, matrixB);
                reshapeTable(810, matrixResult);
                tempL = tempMatrix->findCholeskyDecomposition();
                fillResultTable(matrixA, tempMatrix);
                fillResultTable(matrixB, tempL);
                fillResultTable(matrixResult, tempL);
                transposeChosenMatrix(matrixResult);
                changeLabels(constTexts[53],constTexts[54],constTexts[54]+"<sup>"+constTexts[59]+"</sup>",constTexts[38],constTexts[44]);

            } else {
                ErrorNotPositiveDefined error;
                throw error;
            }
        } else {
            ErrorNotSymmetric error1;
            throw error1;
        }
    }
    catch(exception &e)
    {
        QMessageBox::critical(this,QString::fromStdString(constTexts[56]),e.what());
    }

}

void MainWindow::fillTempMatrix(QTableWidget *NewMatrix, matrix *temp)
{
    for(int i=0;i<temp->getRows();i++)
    {
        for(int j=0;j<temp->getCols();j++)
        {
            QString tempString=NewMatrix->item(i,j)->text();
            double tempNumber=tempString.toDouble();
            temp->set(i,j,tempNumber);
        }
    }
}

QTableWidget * MainWindow::checkWhich()
{
    int ChooseOfMatrix=chooseMatrix->value();
    switch(ChooseOfMatrix)
    {
        case 1:
            return matrixA;
        case 2:
            return matrixB;
        case 3:
            return matrixResult;
    }
    return nullptr;
}

void MainWindow::changeLabels(std::string const &firstHeader,std::string const &secondHeader,std::string const &thirdHeader,std::string const &firstOp,std::string const &secondOp){
    headerMatrixA->setText(QString::fromStdString(firstHeader));
    headerMatrixB->setText(QString::fromStdString(secondHeader));
    headerMatrixResult->setText(QString::fromStdString(thirdHeader));
    operationOne->setText(QString::fromStdString(firstOp));
    operationTwo->setText(QString::fromStdString(secondOp));
    if(matrixA->columnCount()>5 && matrixA->rowCount()>5)
    {
        operationOne->setGeometry((410+20+5*50)/2,(32+5*30)/2,50,50);
        if(matrixB->columnCount()>5)
        {
            operationTwo->setGeometry((810+410+5*50)/2,(32+5*30)/2,50,50);
        }
        else {
            operationTwo->setGeometry((810+410+matrixB->columnCount()*50)/2, (32+5*30)/2,50,50);
        }
    }
    else if(matrixA->columnCount()>5 && matrixA->rowCount()<=5)
    {
        operationOne->setGeometry((410+20+5*50)/2,(32+matrixA->rowCount()*30)/2,50,50);
        if(matrixB->columnCount()>5)
        {
            operationTwo->setGeometry((810+410+5*50)/2,(32+5*30)/2,50,50);
        }
        else {
            operationTwo->setGeometry((810+410+matrixB->columnCount()*50)/2, (32+5*30)/2,50,50);
        }
    }
    else if(matrixA->columnCount()<=5 && matrixA->rowCount()>5)
    {
        operationOne->setGeometry((410+20+matrixA->columnCount()*50)/2,(32+5*30)/2,50,50);
        if(matrixB->columnCount()>5)
        {
            operationTwo->setGeometry((810+410+5*50)/2,(32+5*30)/2,50,50);
        }
        else {
            operationTwo->setGeometry((810+410+matrixB->columnCount()*50)/2, (32+5*30)/2,50,50);
        }
    }
    else{
        operationOne->setGeometry((410+20+matrixA->columnCount()*50)/2,(32+matrixA->rowCount()*30)/2,50,50);
        if(matrixB->columnCount()>5)
        {
            operationTwo->setGeometry((810+410+5*50)/2,(32+5*30)/2,50,50);
        }
        else {
            operationTwo->setGeometry((810+410+matrixB->columnCount()*50)/2, (32+5*30)/2,50,50);
        }
    }
}

void MainWindow::fillResultTable(QTableWidget* tab,matrix * temp){
    for(int i=0;i<tab->rowCount();i++)
    {
        for(int j=0;j<tab->columnCount();j++)
        {
            tab->setItem(i,j,new QTableWidgetItem(QString::number(temp->get(i,j))));
        }
    }
}

string* handleText(){
    ifstream file;
    file.open("../resources/TextsFile.txt");
        if(!file.good())
    {

    }
    string temp;
    string *table;
    table=new string[65];
    int index=0;
    while(getline(file,temp))
    {
        table[index]=temp;
        index++;
    }
    return table;
}