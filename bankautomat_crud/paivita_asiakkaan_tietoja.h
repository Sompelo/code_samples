#ifndef PAIVITA_ASIAKKAAN_TIETOJA_H
#define PAIVITA_ASIAKKAAN_TIETOJA_H

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
class Paivita_Asiakkaan_Tietoja;
}

class Paivita_Asiakkaan_Tietoja : public QDialog
{
    Q_OBJECT

public:
    explicit Paivita_Asiakkaan_Tietoja(QWidget *parent = 0);
    ~Paivita_Asiakkaan_Tietoja();

    void haeTiedot();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnPaivita_clicked();

    void PaivitaSlot(QNetworkReply *reply);
    void asiakasTiedotSlot(QNetworkReply *reply2);

private:
    Ui::Paivita_Asiakkaan_Tietoja *ui;
    QNetworkAccessManager *paivitaManager;
    QNetworkAccessManager *asiakasTiedotManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;


    QString id;
    QString nimi;
    QString osoite;
    QString puhelinnro;
};

#endif // PAIVITA_ASIAKKAAN_TIETOJA_H
