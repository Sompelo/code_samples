#ifndef ASIAKAS_PANKKITILI_YHTEYS_H
#define ASIAKAS_PANKKITILI_YHTEYS_H

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
class Asiakas_Pankkitili_Yhteys;
}

class Asiakas_Pankkitili_Yhteys : public QDialog
{
    Q_OBJECT

public:
    explicit Asiakas_Pankkitili_Yhteys(QWidget *parent = 0);
    ~Asiakas_Pankkitili_Yhteys();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnHae_clicked();

    void yhteysSlot(QNetworkReply *reply);

private:
    Ui::Asiakas_Pankkitili_Yhteys *ui;

    QNetworkAccessManager *yhteysManager;
    QNetworkReply *reply;
};

#endif // ASIAKAS_PANKKITILI_YHTEYS_H
