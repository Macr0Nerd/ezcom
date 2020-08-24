#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <libeztp/libeztp.hpp>
#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QImageReader>
#include <QImageWriter>
#include <QTableWidget>

#include "ezmaker/dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newc();
    void open();
    void refresh();
    void remove();
    void reset();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
