#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef __cplusplus
extern "C" {
#endif
#include "./smartcalc.h"
#ifdef __cplusplus
}
#endif

#include <QMainWindow>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double xBegin, xEnd, h, X;
    int N;
    char temp_str[255];
    QString text_str;
    QVector<double> x, y;
    QDoubleValidator m_doubleValidator;

private slots:
    void digits();
    void on_pushButton_dot_clicked();
    void operations();
    void functions();
    void on_pushButton_reset_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_graph_clicked();
};
#endif // MAINWINDOW_H
