#ifndef GETSTUDENTAPP_H
#define GETSTUDENTAPP_H

#include <QDialog>

namespace Ui {
class GetStudent;
}

class GetStudent : public QDialog
{
    Q_OBJECT

public:
    explicit GetStudent(QWidget *parent = 0);
    ~GetStudent();
public slots:
    void outputStudent();
private:
    Ui::GetStudent *ui;
    static QRegExp s_StudentNumberFormat;
    static QRegExp s_CourseCodeFormat;
    static QRegExp s_MarkFormat;
};

#endif // GETSTUDENTAPP_H

