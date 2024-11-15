#ifndef HYGIENE_H
#define HYGIENE_H
#include <QSqlQueryModel>
#include <QString>

class hygiene {
    QString id_produith;  // Change from int to QString
    QString quantiteminimalh;
    QString quantiteapresajouth;
    QString quantiteenstockh;
    QString typeproduith;

public:
    hygiene() {}
    hygiene(QString id_produith, QString quantiteminimalh, QString quantiteapresajouth, QString quantiteenstockh, QString typeproduith);

    QString getquantiteminimalh() { return quantiteminimalh; }
    QString getquantiteapresajouth() { return quantiteapresajouth; }
    QString getquantiteenstockh() { return quantiteenstockh; }
    QString gettypeproduith() { return typeproduith; }
    QString getid_produith() { return id_produith; }

    void setquantiteminimalh(QString quantiteminimalh) { this->quantiteminimalh = quantiteminimalh; }
    void setquantiteapresajouth(QString quantiteapresajouth) { this->quantiteapresajouth = quantiteapresajouth; }
    void setquantiteenstockh(QString quantiteenstockh) { this->quantiteenstockh = quantiteenstockh; }
    void settypeproduith(QString typeproduith) { this->typeproduith = typeproduith; }
    void setid_produith(QString id_produith) { this->id_produith = id_produith; }

    bool ajouter();
    bool supprimer(const QString &id);
    QSqlQueryModel* afficher();
    bool modifier();
};

#endif // HYGIENE_H
