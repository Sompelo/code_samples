#ifndef NAYTA_ASIAKKAAN_TIEDOT_H
#define NAYTA_ASIAKKAAN_TIEDOT_H

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
class Nayta_Asiakkaan_Tiedot;
}

class Nayta_Asiakkaan_Tiedot : public QDialog
{
    Q_OBJECT

public:
    explicit Nayta_Asiakkaan_Tiedot(QWidget *parent = 0);
    ~Nayta_Asiakkaan_Tiedot();

private slots:
    void on_btnHaeTiedot_clicked();
    void on_btnHaeKaikki_clicked();
    void on_btnTakaisin_clicked();

    void asiakkaanTiedotSlot(QNetworkReply *reply);
    void kaikkiTiedotSlot(QNetworkReply *reply);

private:
    Ui::Nayta_Asiakkaan_Tiedot *ui;

    QNetworkAccessManager *asiakkaanTiedotManager;
    QNetworkAccessManager *kaikkiTiedotManager;
    QNetworkReply *reply;

    QString uname;
    QString idasiakas;
    QString nimi;
    QString osoite;
    QString puhelinnro;

};

#endif // NAYTATIEDOT_H
