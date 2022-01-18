#ifndef LISAA_UUSI_ASIAKAS_H
#define LISAA_UUSI_ASIAKAS_H

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
class Lisaa_Uusi_Asiakas;
}

class Lisaa_Uusi_Asiakas : public QDialog
{
    Q_OBJECT

public:
    explicit Lisaa_Uusi_Asiakas(QWidget *parent = 0);
    ~Lisaa_Uusi_Asiakas();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnLisaa_clicked();

    void lisaaAsiakasSlot(QNetworkReply *reply);

private:
    Ui::Lisaa_Uusi_Asiakas *ui;
    QNetworkAccessManager *lisaaAsiakasManager;
    QNetworkReply *reply;
};

#endif // LISAA_UUSI_ASIAKAS_H
