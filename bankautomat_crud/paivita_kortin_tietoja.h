#ifndef PAIVITA_KORTIN_TIETOJA_H
#define PAIVITA_KORTIN_TIETOJA_H

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
class Paivita_Kortin_Tietoja;
}

class Paivita_Kortin_Tietoja : public QDialog
{
    Q_OBJECT

public:
    explicit Paivita_Kortin_Tietoja(QWidget *parent = 0);
    ~Paivita_Kortin_Tietoja();

    void haeTiedot();


private slots:
    void on_btnTakaisin_clicked();
    void on_btnPaivita_clicked();

    void PaivitaSlot(QNetworkReply *reply);
    void kortinTiedotSlot(QNetworkReply *reply2);

private:
    Ui::Paivita_Kortin_Tietoja *ui;
    QNetworkAccessManager *paivitaManager;
    QNetworkAccessManager *korttiTiedotManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;

    QString korttiId;
    QString pin;
    QString luottoTila;
    QString tilinumero;
    QString pinVaarin;
    QString idAsiakas;
};
#endif // PAIVITA_KORTIN_TIETOJA_H
