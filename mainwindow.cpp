#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Marks Calculator");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("\\d+"), this);
    ui->lineEdit_M->setValidator(validator);
    ui->lineEdit_TM->setValidator(validator);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    QRegularExpression regex("[0-9]+");
    QString mText = ui->lineEdit_M->text();
    QString tmText = ui->lineEdit_TM->text();

    if (regex.match(mText).hasMatch() && regex.match(tmText).hasMatch()) {
        qDebug() << "lineEdit_M text: " << mText;
        qDebug() << "lineEdit_TM text: " << tmText;
        calculation_work();
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid numbers in both line edits.");
    }
}

void MainWindow::calculation_work() {
    QString marks_text = ui->lineEdit_M->text();
    QString totalmarks_text = ui->lineEdit_TM->text();

    if (!marks_text.isEmpty() && !totalmarks_text.isEmpty()) {
        double marks = marks_text.toDouble();
        double totalmarks = totalmarks_text.toDouble();

        double percentage = (marks / totalmarks) * 100.0;
        QString percentage_string = "Percentage: "+QString::number(percentage, 'f', 2) + "%";
        if (ui->checkBox_MHT->isChecked()) {
            int correctanswers = marks / 2.0;
            int wronganswers = totalmarks / 2.0 - correctanswers;
            QString wronganswers_string = "Wrong Questions: " + QString::number(wronganswers);

            ui->label_display->setText(percentage_string);
            ui->label_WQ->setText(wronganswers_string);
            ui->label_MARKS->setText(QString::number(marks));
        }
        else if (ui->checkBox_COM->isChecked()) {
            int correctanswers = marks / 4.0;
            int wronganswers = totalmarks / 4.0 - correctanswers;
            int negative_marks = wronganswers;

            if (negative_marks < 0) {
                negative_marks = 0;
            }
            QString wronganswers_string = "Wrong Questions: " + QString::number(wronganswers);
            QString marks_obtained_string = "Marks Obtained: " + QString::number(marks - negative_marks);

            double percentage = ((double)(marks - negative_marks) / totalmarks) * 100.0;
            QString percentage_string = "Percentage: " + QString::number(percentage, 'f', 2) + "%";

            ui->label_display->setText(percentage_string);
            ui->label_WQ->setText(wronganswers_string);
            ui->label_MARKS->setText(marks_obtained_string);
        }
        else {
            ui->label_display->setText(percentage_string);
            ui->label_WQ->clear();
            ui->label_MARKS->clear();
        }
    }
}


