#ifndef NAYTA_KORTIN_TIEDOT_H
#define NAYTA_KORTIN_TIEDOT_H

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
class Nayta_Kortin_Tiedot;
}

class Nayta_Kortin_Tiedot : public QDialog
{
    Q_OBJECT

public:
    explicit Nayta_Kortin_Tiedot(QWidget *parent = 0);
    ~Nayta_Kortin_Tiedot();

private slots:
    void on_btnHae_clicked();
    void on_btnHaeKaikki_clicked();
    void on_btnTakaisin_clicked();

    void kortinTiedotSlot(QNetworkReply *reply);
//    void kaikkiTiedotSlot(QNetworkReply *reply);

private:
    Ui::Nayta_Kortin_Tiedot *ui;

    QNetworkAccessManager *korttiTiedotManager;
    QNetworkReply *reply;

    QString uname;
    QString korttinumero;
    QString tilinumero;
    QString credit;
    QString pin;
    QString pinVaarin;

};

#endif // NAYTA_KORTIN_TIEDOT_H
