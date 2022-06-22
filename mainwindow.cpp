#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_doubleValidator(-10000000, 10000000, 15, this)
{
    ui->setupUi(this);

    m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_x->setValidator(&m_doubleValidator);
    ui->lineEdit_x_begin->setValidator(&m_doubleValidator);
    ui->lineEdit_x_end->setValidator(&m_doubleValidator);
    ui->lineEdit_y_begin->setValidator(&m_doubleValidator);
    ui->lineEdit_y_end->setValidator(&m_doubleValidator);

    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-10, 10);

    // Кнопки 1-9
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_open_br, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_close_br, SIGNAL(clicked()), this, SLOT(digits()));

    // Кнопки операций
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_exp, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));

    // Кнопки функций
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Обработка кнопок 1-9
void MainWindow::digits() {
    QPushButton *button = (QPushButton *) sender();

    if (ui->lineEdit_exp->text().endsWith("0") && ui->lineEdit_exp->text().size() == 1) {
        ui->lineEdit_exp->setText(button->text());
    } else {
        if (ui->lineEdit_exp->text().endsWith("x") != 1 || button->text() != "x") {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + button->text());
        }
    }
}

// Обработка точки '.'
void MainWindow::on_pushButton_dot_clicked() {
    if (ui->lineEdit_exp->text().endsWith(".") != 1) {
        ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + ".");
    }
}

// Обработка операций
void MainWindow::operations() {
    QPushButton *button = (QPushButton *) sender();

    int operator_exist = 1;

    if (ui->lineEdit_exp->text().endsWith("+") ||
        ui->lineEdit_exp->text().endsWith("-") ||
        ui->lineEdit_exp->text().endsWith("*") ||
        ui->lineEdit_exp->text().endsWith("/") ||
        ui->lineEdit_exp->text().endsWith("^") ||
        ui->lineEdit_exp->text().endsWith("mod")) {
        operator_exist = 0;
    }

    if (button->text() == "+" && operator_exist) {
        ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "+");
    } else if (button->text() == "-" && operator_exist) {
        ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "-");
    } else if (button->text() == "*" && operator_exist) {
        ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "*");
    } else if (button->text() == "/" && operator_exist) {
        ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "/");
    } else if (button->text() == "^" && operator_exist) {
        ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "^");
    } else if (button->text() == "mod" && operator_exist) {
        ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "mod");
    }
}

// Обработка функций
void MainWindow::functions() {
    QPushButton *button = (QPushButton *) sender();

    int operator_exist = 1;

    if (ui->lineEdit_exp->text().endsWith("sin") ||
        ui->lineEdit_exp->text().endsWith("cos") ||
        ui->lineEdit_exp->text().endsWith("tan") ||
        ui->lineEdit_exp->text().endsWith("asin") ||
        ui->lineEdit_exp->text().endsWith("acos") ||
        ui->lineEdit_exp->text().endsWith("atan") ||
        ui->lineEdit_exp->text().endsWith("sqrt") ||
        ui->lineEdit_exp->text().endsWith("ln") ||
        ui->lineEdit_exp->text().endsWith("log")) {
        operator_exist = 0;
    }

    if (ui->lineEdit_exp->text().endsWith("0") && ui->lineEdit_exp->text().size() == 1) {
        if (button->text() == "sin") {
            ui->lineEdit_exp->setText("sin");
        } else if (button->text() == "cos") {
            ui->lineEdit_exp->setText("cos");
        } else if (button->text() == "tan") {
            ui->lineEdit_exp->setText("tan");
        } else if (button->text() == "asin") {
            ui->lineEdit_exp->setText("asin");
        } else if (button->text() == "acos") {
            ui->lineEdit_exp->setText("acos");
        } else if (button->text() == "atan") {
            ui->lineEdit_exp->setText("atan");
        } else if (button->text() == "sqrt") {
            ui->lineEdit_exp->setText("sqrt");
        } else if (button->text() == "ln") {
            ui->lineEdit_exp->setText("ln");
        } else if (button->text() == "log") {
            ui->lineEdit_exp->setText("log");
        }
    } else {
        if (button->text() == "sin" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "sin");
        } else if (button->text() == "cos" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "cos");
        } else if (button->text() == "tan" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "tan");
        } else if (button->text() == "asin" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "asin");
        } else if (button->text() == "acos" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "acos");
        } else if (button->text() == "atan" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "atan");
        } else if (button->text() == "sqrt" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "sqrt");
        } else if (button->text() == "ln" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "ln");
        } else if (button->text() == "log" && operator_exist) {
            ui->lineEdit_exp->setText(ui->lineEdit_exp->text() + "log");
        }
    }
}

// Обработка сброса
void MainWindow::on_pushButton_reset_clicked() {
    ui->lineEdit_x->setText("");
    ui->lineEdit_exp->setText("");
}

// Обработка знака равно
void MainWindow::on_pushButton_equal_clicked() {
    char* str = new char(ui->lineEdit_exp->text().length());
    QByteArray barr = ui->lineEdit_exp->text().toLatin1();
    strlcpy(str, barr, ui->lineEdit_exp->text().length() + 1);

    int exec;
    double res = 0.0;
    double value_of_x = 0.0;

    if (ui->lineEdit_x->text() != "Значение Х") {
        value_of_x = ui->lineEdit_x->text().toDouble();
    }

    if (ui->lineEdit_exp->text().contains("x")) {
        exec = main_c(str, value_of_x, &res);
    } else {
        exec = main_c(str, value_of_x, &res);
    }

    if (exec == 1) {
        QMessageBox::about(this, "Invalid expression", "Invalid expression");
    } else {
        QString valueAsString = QString::number(res, 'g', 15);
        ui->lineEdit_exp->setText(valueAsString);
    }

}

void MainWindow::on_pushButton_graph_clicked() {
    ui->widget->clearGraphs();

    char* str = new char(ui->lineEdit_exp->text().length());
    QByteArray barr = ui->lineEdit_exp->text().toLatin1();
    strlcpy(str, barr, ui->lineEdit_exp->text().length() + 1);

    double x_begin = ui->lineEdit_x_begin->text().toDouble();
    double x_end = ui->lineEdit_x_end->text().toDouble();
    double y_begin = ui->lineEdit_y_begin->text().toDouble();
    double y_end = ui->lineEdit_y_end->text().toDouble();

    ui->widget->xAxis->setRange(x_begin, x_end);
    ui->widget->yAxis->setRange(y_begin, y_end);

    h = 0.1;
    xBegin =x_begin;
    xEnd = x_end;

    N = (xBegin - xEnd)/h + 2;

    int exec = 0;

    for (X = xBegin; X < xEnd && exec == 0; X += h) {
        x.push_back(X);
        double res = 0.0;
        exec = main_c(str, X, &res);
        y.push_back(res);
    }

    if (exec == 1) {
        QMessageBox::about(this, "Invalid expression", "Invalid input");
    } else {
        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x,y);

        ui->widget->replot();
    }

        x.clear();
        y.clear();
}
