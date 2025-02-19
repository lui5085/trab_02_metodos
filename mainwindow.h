#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QRadioButton;
class QSpinBox;
class QTableWidget;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRadioToggled(bool checked);
    void onUpdateTables();
    void onCalculate();
    void fillTableBase();
    void onExportCSV();

private:
    QRadioButton *radioBase;
    QRadioButton *radioPers;
    QSpinBox     *spinN;
    QPushButton  *btnUpdate;
    QPushButton  *btnExport;

    QTableWidget *tblA;
    QTableWidget *tblF;
    QTableWidget *tblResults;
};

#endif // MAINWINDOW_H
