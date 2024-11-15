#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hygiene.h"
#include "connection.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QInputDialog>
#include <QFileDialog>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Connection conn;
    if (conn.createconnect()) {
        QMessageBox::information(this, "Connexion", "Connexion réussie à la base de données.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la connexion à la base de données.");
    }

    ui->tableView25->setModel(Etmp.afficher());
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}

MainWindow::~MainWindow()
{
    delete ui;
    m_selectedId = "";
}

void MainWindow::on_pushButton_92_clicked() {
    QString id_produith = ui->lineEdit_id->text();
    QString quantiteminimalh = ui->lineEdit_qua_mini->text();
    QString quantiteapresajouth = ui->lineEdit_apres_ajou->text();
    QString quantiteenstockh = ui->lineEdit_qua_stock->text();
    QString typeproduith = ui->lineEdit_type_produit->text();

    // Validation for the form fields
    if (quantiteminimalh.isEmpty() || quantiteapresajouth.isEmpty() ||
        quantiteenstockh.isEmpty() || typeproduith.isEmpty() || typeproduith.length() <= 2) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires, "
                                             "et assurez-vous que le type de produit contient plus de 2 caractères.");
        return;
    }

    hygiene h(id_produith, quantiteminimalh, quantiteapresajouth, quantiteenstockh, typeproduith);
    bool success = h.ajouter();

    if (success) {
        QMessageBox::information(this, "Succès", "Ajout effectué avec succès.");
        ui->tableView25->setModel(h.afficher());  // Refresh the table view with the updated data
    } else {
        QMessageBox::critical(this, "Erreur", "Ajout non effectué.");
    }
}




void MainWindow::on_tableView25_clicked(const QModelIndex &index)
{
    // Get the ID of the selected row (assuming the ID is in the first column)
    m_selectedId = index.sibling(index.row(), 3).data().toString();  // Adjust column index for ID_PRODUITH

    // Get other fields from the selected row (adjust the column indexes based on your table structure)
    QString quantiteminimalh = index.sibling(index.row(), 0).data().toString();
    QString quantiteapresajouth = index.sibling(index.row(), 1).data().toString();
    QString quantiteenstockh = index.sibling(index.row(), 2).data().toString();
    QString typeproduith = index.sibling(index.row(), 4).data().toString();

    // Set the data to the respective QLineEdits
    ui->lineEdit_id->setText(m_selectedId);  // Use m_selectedId here
    ui->lineEdit_qua_mini->setText(quantiteminimalh);
    ui->lineEdit_apres_ajou->setText(quantiteapresajouth);
    ui->lineEdit_qua_stock->setText(quantiteenstockh);
    ui->lineEdit_type_produit->setText(typeproduith);
}


void MainWindow::on_pushButton_94_clicked() {
    if (m_selectedId.isEmpty()) {
        QMessageBox::warning(this, "Select hygiene", "Please select a hygiene to delete.");
        return;
    }

    // Confirm deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete this hygiene?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        hygiene hygiene;
        if (hygiene.supprimer(m_selectedId)) {
            QMessageBox::information(this, "Success", "Hygiene deleted successfully!");
            ui->tableView25->setModel(Etmp.afficher());  // Refresh after deletion
        } else {
            QMessageBox::warning(this, "Failure", "Failed to delete hygiene.");
        }
    }
}

void MainWindow::on_pushButton_93_clicked() {
    // Capture updated data from line edits
    QString id_produith = ui->lineEdit_id->text();
    QString quantiteminimalh = ui->lineEdit_qua_mini->text();
    QString quantiteapresajouth = ui->lineEdit_apres_ajou->text();
    QString quantiteenstockh = ui->lineEdit_qua_stock->text();
    QString typeproduith = ui->lineEdit_type_produit->text();

    hygiene h(id_produith, quantiteminimalh, quantiteapresajouth, quantiteenstockh, typeproduith);

    bool success = h.modifier();

    if (success) {
        QMessageBox::information(this, "Succès", "Les données ont été mises à jour avec succès.");
        ui->tableView25->setModel(h.afficher());  // Refresh table view after modification
    } else {
        QMessageBox::critical(this, "Erreur", "La mise à jour a échoué.");
    }
}



