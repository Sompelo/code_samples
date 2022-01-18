#ifndef POISTA_ASIAKAS_H
#define POISTA_ASIAKAS_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QString>

namespace Ui {
class Poista_Asiakas;
}

class Poista_Asiakas : public QDialog
{
    Q_OBJECT

public:
    explicit Poista_Asiakas(QWidget *parent = 0);
    ~Poista_Asiakas();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnPoista_clicked();

    void poistaSlot(QNetworkReply *reply);

private:
    Ui::Poista_Asiakas *ui;
    QNetworkAccessManager *PoistaTiedotManager;
    QNetworkReply *reply;
};

#endif // POISTA_ASIAKAS_H
