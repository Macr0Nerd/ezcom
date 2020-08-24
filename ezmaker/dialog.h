#ifndef DIALOG_H
#define DIALOG_H

#include <libeztp/libeztp.hpp>
#include <string>
#include <QDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void save();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
