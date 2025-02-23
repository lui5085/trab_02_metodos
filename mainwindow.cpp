#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>

// Suas funcoes de fatoracao
#include "metodos.h"

#include <cmath>
#include <iostream>

// Construtor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Grupo p/ escolher base/personalizada
    QGroupBox *grpChoice = new QGroupBox("Selecione o tipo de matriz:", this);
    QHBoxLayout *choiceLayout = new QHBoxLayout(grpChoice);
    radioBase = new QRadioButton("Matriz Base (enunciado)", grpChoice);
    radioPers = new QRadioButton("Matriz Personalizada", grpChoice);
    radioBase->setChecked(true);
    choiceLayout->addWidget(radioBase);
    choiceLayout->addWidget(radioPers);
    grpChoice->setLayout(choiceLayout);
    mainLayout->addWidget(grpChoice);

    connect(radioBase, &QRadioButton::toggled, this, &MainWindow::onRadioToggled);

    // SpinN + Botao "Atualizar Tabelas"
    QHBoxLayout *nLayout = new QHBoxLayout;
    QLabel *lblN = new QLabel("Quantidade (n):", this);
    spinN = new QSpinBox(this);
    spinN->setRange(1,50);
    spinN->setValue(3);

    btnUpdate = new QPushButton("Atualizar Tabelas", this);
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateTables);

    nLayout->addWidget(lblN);
    nLayout->addWidget(spinN);
    nLayout->addWidget(btnUpdate);
    mainLayout->addLayout(nLayout);

    // Tabelas p/ A e f
    QHBoxLayout *tableLayout = new QHBoxLayout;

    tblA = new QTableWidget(3,3,this);
    tblA->setHorizontalHeaderLabels(QStringList()<<"C0"<<"C1"<<"C2");
    tblA->setVerticalHeaderLabels(QStringList()<<"L0"<<"L1"<<"L2");

    tblF = new QTableWidget(3,1,this);
    tblF->setHorizontalHeaderLabels(QStringList()<<"f");
    tblF->setVerticalHeaderLabels(QStringList()<<"F0"<<"F1"<<"F2");

    tableLayout->addWidget(tblA);
    tableLayout->addWidget(tblF);
    mainLayout->addLayout(tableLayout);

    fillTableBase(); // Preenche base(3x3)

    // Botao Calcular
    QPushButton *btnCalc = new QPushButton("Calcular", this);
    connect(btnCalc, &QPushButton::clicked, this, &MainWindow::onCalculate);
    mainLayout->addWidget(btnCalc);

    // Tabela de resultados (2 linhas, mas colunas definidas dinamicamente)
    tblResults = new QTableWidget(this);
    tblResults->setRowCount(2);
    tblResults->setColumnCount(2); // So pra comecar
    QStringList vertLabels;
    vertLabels << "d(LU)" << "d(LDP)";
    tblResults->setVerticalHeaderLabels(vertLabels);
    mainLayout->addWidget(tblResults);

    // Botao "Exportar CSV"
    btnExport = new QPushButton("Exportar CSV", this);
    connect(btnExport, &QPushButton::clicked, this, &MainWindow::onExportCSV);
    mainLayout->addWidget(btnExport);

    central->setLayout(mainLayout);
    setCentralWidget(central);

    onRadioToggled(radioBase->isChecked());
}

MainWindow::~MainWindow()
{
}

void MainWindow::onRadioToggled(bool checked)
{
    Q_UNUSED(checked);
    bool isBase = radioBase->isChecked();
    spinN->setEnabled(!isBase);
    btnUpdate->setEnabled(!isBase);
    tblA->setEnabled(!isBase);
    tblF->setEnabled(!isBase);
}

// Botao "Atualizar Tabelas"
void MainWindow::onUpdateTables()
{
    int n = spinN->value();
    tblA->setRowCount(n);
    tblA->setColumnCount(n);

    QStringList hA, vA;
    for(int j=0;j<n;j++){
        hA<<QString("C%1").arg(j);
    }
    for(int i=0;i<n;i++){
        vA<<QString("L%1").arg(i);
    }
    tblA->setHorizontalHeaderLabels(hA);
    tblA->setVerticalHeaderLabels(vA);

    tblF->setRowCount(n);
    tblF->setColumnCount(1);
    QStringList hF; hF<<"f";
    QStringList vF;
    for(int i=0;i<n;i++){
        vF<<QString("F%1").arg(i);
    }
    tblF->setHorizontalHeaderLabels(hF);
    tblF->setVerticalHeaderLabels(vF);
}

void MainWindow::fillTableBase()
{
    double baseA[3][3] = {
        {3, -2, 1},
        {1, -3, 4},
        {9,  4, -5}
    };
    double baseF[3] = {8,6,11};

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tblA->setItem(i,j, new QTableWidgetItem(QString::number(baseA[i][j])));
        }
    }
    for(int i=0;i<3;i++){
        tblF->setItem(i,0, new QTableWidgetItem(QString::number(baseF[i])));
    }
}

void MainWindow::onCalculate()
{
    // Monta A e f
    int n;
    std::vector<std::vector<double>> A;
    std::vector<double> f;

    if(radioBase->isChecked()){
        n=3;
        A.resize(n, std::vector<double>(n,0.0));
        A[0][0]=3; A[0][1]=-2; A[0][2]=1;
        A[1][0]=1; A[1][1]=-3; A[1][2]=4;
        A[2][0]=9; A[2][1]=4;  A[2][2]=-5;
        f.resize(n);
        f[0]=8; f[1]=6; f[2]=11;
    } else {
        n= spinN->value();
        A.resize(n, std::vector<double>(n,0.0));
        f.resize(n,0.0);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                auto item=tblA->item(i,j);
                double val = item?item->text().toDouble():0.0;
                A[i][j] = val;
            }
        }
        for(int i=0;i<n;i++){
            auto item=tblF->item(i,0);
            double val = item?item->text().toDouble():0.0;
            f[i]=val;
        }
    }

    // Fator LU
    auto A_lu = A;
    bool okLU = Metodos::factorLU(A_lu,n);
    if(!okLU){
        QMessageBox::warning(this,"Erro","Fatoracao LU falhou (pivô zero?).");
        return;
    }
    auto dLU = Metodos::solveLU(A_lu,f,n);

    // LDP
    auto A_ldp = A_lu;
    std::vector<double> D(n,0.0);
    Metodos::computeLDPFromLU(A_ldp,n,D);
    auto dLDP = Metodos::solveLDP(A_ldp,D,f,n);

    // Preenche a tblResults
    // 2n colunas => para j=0..n-1 => col(2j)= d_j, col(2j+1)= d_j_explode
    int colCount = 2*n;
    tblResults->clear();
    tblResults->setRowCount(2);
    tblResults->setColumnCount(colCount);

    // Nome das linhas
    QStringList rowLabels;
    rowLabels << "d(LU)" << "d(LDP)";
    tblResults->setVerticalHeaderLabels(rowLabels);

    // Nome das colunas
    QStringList colLabels;
    for(int j=0;j<n;j++){
        colLabels << QString("d%1").arg(j);
        colLabels << QString("d%1_explode").arg(j);
    }
    tblResults->setHorizontalHeaderLabels(colLabels);

    // row=0 => LU
    for(int j=0;j<n;j++){
        double val = dLU[j];
        bool exp = (fabs(val)>2.0);
        // col(2j) => valor, col(2j+1) => True/False
        tblResults->setItem(0,2*j,
                            new QTableWidgetItem(QString::number(val,'f',5)));
        tblResults->setItem(0,2*j+1,
                            new QTableWidgetItem(exp ? "True" : "False"));
    }

    // row=1 => LDP
    for(int j=0;j<n;j++){
        double val = dLDP[j];
        bool exp = (fabs(val)>2.0);
        tblResults->setItem(1,2*j,
                            new QTableWidgetItem(QString::number(val,'f',5)));
        tblResults->setItem(1,2*j+1,
                            new QTableWidgetItem(exp ? "True" : "False"));
    }
}

void MainWindow::onExportCSV()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Salvar CSV"),
        "resultado.csv",
        tr("CSV Files (*.csv)")
        );
    if(fileName.isEmpty()) return;

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Erro","Não foi possível abrir arquivo para escrita.");
        return;
    }

    QTextStream out(&file);
    // No Qt6: sem setCodec

    int rows = tblResults->rowCount();
    int cols = tblResults->columnCount();

    // Cabecalho
    QStringList header;
    for(int c=0;c<cols;c++){
        auto item = tblResults->horizontalHeaderItem(c);
        QString colName = item?item->text():QString("Col%1").arg(c);
        header << colName;
    }
    out << header.join(";") << "\n";

    // Linhas
    for(int r=0;r<rows;r++){
        QStringList rowData;
        for(int c=0;c<cols;c++){
            auto item = tblResults->item(r,c);
            QString val = item? item->text() : "";
            rowData << val;
        }
        out << rowData.join(";") << "\n";
    }

    file.close();
    QMessageBox::information(this,"Salvo","Arquivo CSV gerado com sucesso!");
}
