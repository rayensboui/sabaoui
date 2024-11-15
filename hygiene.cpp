#include "hygiene.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

hygiene::hygiene(QString id_produith, QString quantiteminimalh, QString quantiteapresajouth, QString quantiteenstockh , QString typeproduith) {
    this->id_produith = id_produith;
    this->quantiteminimalh = quantiteminimalh;
    this->quantiteapresajouth = quantiteapresajouth;
    this->quantiteenstockh = quantiteenstockh;
    this->typeproduith = typeproduith;
}

bool hygiene::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO GS_HYGIENE (TYPEDEPRODUITH, QUANTITEENSTOCKH, QUANTITEMINIMALH, ID_PRODUITH, QUANTITEAPRESAJOUTH) "
                  "VALUES (:TYPEDEPRODUITH, :QUANTITEENSTOCKH, :QUANTITEMINIMALH, :ID_PRODUITH, :QUANTITEAPRESAJOUTH)");

    // Bind values
    query.bindValue(":TYPEDEPRODUITH", typeproduith);
    query.bindValue(":QUANTITEENSTOCKH", quantiteenstockh);
    query.bindValue(":QUANTITEMINIMALH", quantiteminimalh);
    query.bindValue(":ID_PRODUITH", id_produith);
    query.bindValue(":QUANTITEAPRESAJOUTH", quantiteapresajouth);

    if (!query.exec()) {
        qDebug() << "Erreur d'insertion : " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* hygiene::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Use exact column names as defined in SQL schema
    query.prepare("SELECT TYPEDEPRODUITH, QUANTITEENSTOCKH, QUANTITEMINIMALH, ID_PRODUITH, QUANTITEAPRESAJOUTH FROM GS_HYGIENE");
    if (!query.exec()) {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Type de Produit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Quantité en Stock"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité Minimale"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID Produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantité Après Ajout"));

    return model;
}

bool hygiene::supprimer(const QString &id) {
    QString trimmedId = id.trimmed();

    if (trimmedId.isEmpty()) {
        qDebug() << "Invalid ID: Empty string after trimming";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM GS_HYGIENE WHERE ID_PRODUITH = :id");
    query.bindValue(":id", trimmedId);

    qDebug() << "Executing DELETE query: " << query.lastQuery();

    if (query.exec()) {
        qDebug() << "Hygiene entry with ID" << trimmedId << "deleted successfully.";
        return true;
    } else {
        qDebug() << "Deletion failed:" << query.lastError();
        return false;
    }
}

bool hygiene::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE GS_HYGIENE SET QUANTITEMINIMALH = :quantiteminimalh, "
                  "QUANTITEAPRESAJOUTH = :quantiteapresajouth, QUANTITEENSTOCKH = :quantiteenstockh, TYPEDEPRODUITH = :typeproduith "
                  "WHERE ID_PRODUITH = :id_produith");

    // Bind values
    query.bindValue(":id_produith", this->id_produith);
    query.bindValue(":quantiteminimalh", this->quantiteminimalh);
    query.bindValue(":quantiteapresajouth", this->quantiteapresajouth);
    query.bindValue(":quantiteenstockh", this->quantiteenstockh);
    query.bindValue(":typeproduith", this->typeproduith);

    if (!query.exec()) {
        qDebug() << "Échec de la mise à jour :" << query.lastError();
        return false;
    }
    return true;
}
