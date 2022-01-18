#ifndef LISAA_UUSI_KORTTI_H
#define LISAA_UUSI_KORTTI_H

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
class Lisaa_Uusi_Kortti;
}

class Lisaa_Uusi_Kortti : public QDialog
{
    Q_OBJECT

public:
    explicit Lisaa_Uusi_Kortti(QWidget *parent = 0);
    ~Lisaa_Uusi_Kortti();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnLisaaKortti_clicked();

    void lisaaKorttiSlot(QNetworkReply *reply);

private:
    Ui::Lisaa_Uusi_Kortti *ui;
    QNetworkAccessManager *lisaaKorttiManager;
    QNetworkReply *reply;
};

#endif // LISAA_UUSI_KORTTI_H
