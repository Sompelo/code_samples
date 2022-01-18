#ifndef NAYTA_TILIN_TIEDOT_H
#define NAYTA_TILIN_TIEDOT_H

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
class nayta_tilin_tiedot;
}

class nayta_tilin_tiedot : public QDialog
{
    Q_OBJECT

public:
    explicit nayta_tilin_tiedot(QWidget *parent = 0);
    ~nayta_tilin_tiedot();

private slots:
    void on_btnHaeTiedot_clicked();
    void on_btnHaeKaikki_clicked();
    void on_btnTakaisin_clicked();

    void tilinTiedotSlot(QNetworkReply *reply);
//    void kaikkiTiedotSlot(QNetworkReply *reply);

private:
    Ui::nayta_tilin_tiedot *ui;

    QNetworkAccessManager *tilinTiedotManager;
    QNetworkReply *reply;

    QString uname;
    QString tilinumero;
    QString saldo;
    QString creditsaldo;
//    QString credit_saldo;

};

#endif // NAYTA_TILIN_TIEDOT_H
