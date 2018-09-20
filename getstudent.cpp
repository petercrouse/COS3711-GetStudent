#include "getstudent.h"
#include "ui_getstudent.h"
#include <QTextStream>
#include <QMessageBox>

QRegExp GetStudent::s_StudentNumberFormat(R"---(^[0-9]{4}$)---");
QRegExp GetStudent::s_CourseCodeFormat(R"---(^[A-Z]{3}[1-3]\d\d[0-9A-Z]$)---");
QRegExp GetStudent::s_MarkFormat(R"---(^\d\d0?$)---");

GetStudent::GetStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetStudent)
{
    ui->setupUi(this);

    ui->mark->setMaximum(100);
    ui->mark->setMinimum(0);

    QRegExpValidator* studentValidator = new QRegExpValidator(s_StudentNumberFormat, this);
    QRegExpValidator* moduleValidator = new QRegExpValidator(s_CourseCodeFormat, this);
    ui->studentNumber->setValidator(studentValidator);
    ui->moduleCode->setValidator(moduleValidator);

    ui->studentNumber->setInputMask("9999");
    ui->moduleCode->setInputMask(">AAA999N");
    ui->studentNumber->setCursorPosition(0);
    ui->moduleCode->setCursorPosition(0);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(outputStudent()));
}

GetStudent::~GetStudent()
{
    delete ui;
}

void GetStudent::outputStudent()
{
    if(!s_StudentNumberFormat.exactMatch(ui->studentNumber->text()))
    {
        QMessageBox::information(this, "Invalid input", "The studnet number is invalid");
        ui->studentNumber->setFocus();
        return;
    }

    if (!s_CourseCodeFormat.exactMatch(ui->moduleCode->text()))
    {
        QMessageBox::information(this, "Invalid input", "The module code is invalid");
        ui->moduleCode->setFocus();
        return;
    }

    if(!s_MarkFormat.exactMatch(QString("%1").arg(ui->mark->value())))
    {
        QMessageBox::information(this, "Invalid input", "The mark must be between 0 - 100");
        ui->mark->setFocus();
        return;
    }

    QTextStream stream(stdout);
    stream << QString("Number: %1\n"
                      "Module: %2\n"
                      "Mark: %3\n").arg(ui->studentNumber->text())
                                   .arg(ui->moduleCode->text())
                                   .arg(ui->mark->value());

    ui->moduleCode->clear();
    ui->moduleCode->setText(QString());
    ui->moduleCode->setCursorPosition(0);
    ui->moduleCode->setFocus();
    emit ui->moduleCode->textEdited(QString());
    ui->mark->setValue(0);
}
