#ifndef TILITAPAHTUMIEN_TULOSTUS_H
#define TILITAPAHTUMIEN_TULOSTUS_H

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
class Tilitapahtumien_Tulostus;
}

class Tilitapahtumien_Tulostus : public QDialog
{
    Q_OBJECT

public:
    explicit Tilitapahtumien_Tulostus(QWidget *parent = 0);
    ~Tilitapahtumien_Tulostus();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnHae_clicked();

    void tilitapahtumaSlot(QNetworkReply *reply);

private:
    Ui::Tilitapahtumien_Tulostus *ui;

    QNetworkAccessManager *tiliTapahtumaManager;
    QNetworkReply *reply;

    QString tilinumero;
    QString saldo;
    QString creditsaldo;
};

#endif // TILITAPAHTUMIEN_TULOSTUS_H
