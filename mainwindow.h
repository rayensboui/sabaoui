#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "hygiene.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_92_clicked();  // Ensure this is declared here
    void on_pushButton_94_clicked();

    //void afficherTousLesHygienes();

    //void on_pushButton_95_clicked();
    void on_tableView25_clicked(const QModelIndex &index);

    void on_pushButton_93_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    hygiene Etmp;
    QString m_selectedId;
};

#endif // MAINWINDOW_H
