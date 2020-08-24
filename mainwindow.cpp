#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::newc() {
    Dialog w;

    while (w.exec() == QDialog::Accepted) {}
}

static void initializeFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList jsonLocations = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
        dialog.setDirectory(jsonLocations.isEmpty() ? QDir::currentPath() : jsonLocations.last());
    }

    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(QString("Application Files (*.json)"));
    dialog.selectMimeTypeFilter("application/json");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("json");
}

void MainWindow::open() {
    QFileDialog dialog(this, tr("Open File"));
    initializeFileDialog(dialog, QFileDialog::AcceptOpen);

    eztp::Character tmp;

    while (dialog.exec() == QDialog::Accepted && !eztp::Character::load(dialog.selectedFiles().first().toStdString(), tmp)) {}

    int row = ui->initList->rowCount();
    ui->initList->insertRow(row);
    ui->initList->setItem(row, 1, new QTableWidgetItem(tmp.getName().c_str()));
    QTableWidgetItem *initVal = new QTableWidgetItem;
    initVal->setData(Qt::EditRole, 0);
    ui->initList->setItem(row, 0, initVal);
    ui->initList->sortByColumn(0, Qt::DescendingOrder);
}

void MainWindow::refresh() {
    ui->initList->sortByColumn(0, Qt::DescendingOrder);
}

void MainWindow::remove() {
    int row = ui->initList->row(ui->initList->selectedItems().first());

    ui->initList->removeRow(row);
}

void MainWindow::reset() {
    ui->initList->clearContents();
    ui->initList->setRowCount(0);
}
