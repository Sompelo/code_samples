#ifndef PAIVITA_TILIN_TIETOJA_H
#define PAIVITA_TILIN_TIETOJA_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QString>
#include "pankkitilinyhdistaminenasiakastiliin.h"

namespace Ui {
class Paivita_Tilin_Tietoja;
}

class Paivita_Tilin_Tietoja : public QDialog
{
    Q_OBJECT

public:
    explicit Paivita_Tilin_Tietoja(QWidget *parent = 0);
    ~Paivita_Tilin_Tietoja();

    void haeTiedot();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnPaivita_clicked();

    void PaivitaSlot(QNetworkReply *reply);
    void tilinTiedotSlot(QNetworkReply *reply2);

    void on_btnYhdista_clicked();

private:
    Ui::Paivita_Tilin_Tietoja *ui;
    QNetworkAccessManager *paivitaManager;
    QNetworkAccessManager *tiliTiedotManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;

    QString tilinumero;
    QString saldo;
    QString creditSaldo;
    QString luottoRaja;

    PankkitilinYhdistaminenAsiakastiliin *objYhdistaminen;
};
#endif // PAIVITA_TILIN_TIETOJA_H
