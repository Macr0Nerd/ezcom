#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog) {
    ui->setupUi(this);

    ui->race->setInsertPolicy(QComboBox::InsertAlphabetically);
    for (auto [key, val] : eztp::Race::getRaces()) {
        ui->race->addItem(key.c_str());
    }

    ui->bgs->setInsertPolicy(QComboBox::InsertAlphabetically);
    for (auto [key, val] : eztp::Background::getBgs()) {
        ui->bgs->addItem(key.c_str());
    }
}

Dialog::~Dialog() {
    delete ui;
}

static void initializeFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList jsonLocations = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
        dialog.setDirectory(jsonLocations.isEmpty() ? QDir::currentPath() : jsonLocations.last());
    }

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(QString("Application Files (*.json)"));
    dialog.selectMimeTypeFilter("application/json");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("json");
}

void Dialog::save() {
    std::string name = ui->charName->text().toStdString();
    std::string clas = ui->className->text().toStdString();
    std::string race = ui->race->currentText().toStdString();
    std::string bg = ui->bgs->currentText().toStdString();
    bool npc = ui->npcBox->isChecked();
    unsigned long id = ui->uid->value();
    int level = ui->level->value();
    int str = ui->str->value();
    int dex = ui->dex->value();
    int con = ui->con->value();
    int inte = ui->inte->value();
    int wis = ui->wis->value();
    int cha = ui->cha->value();

    eztp::Character tmp(name, clas, race, bg, level, str, dex, con, inte, wis, cha, npc, id);

    QFileDialog dialog(this, tr("Open File"));
    initializeFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !eztp::Character::save(dialog.selectedFiles().first().toStdString(), tmp)) {}

    this->close();
}
