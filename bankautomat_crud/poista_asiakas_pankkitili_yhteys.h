#ifndef POISTA_ASIAKAS_PANKKITILI_YHTEYS_H
#define POISTA_ASIAKAS_PANKKITILI_YHTEYS_H

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
class Poista_Asiakas_Pankkitili_Yhteys;
}

class Poista_Asiakas_Pankkitili_Yhteys : public QDialog
{
    Q_OBJECT

public:
    explicit Poista_Asiakas_Pankkitili_Yhteys(QWidget *parent = 0);
    ~Poista_Asiakas_Pankkitili_Yhteys();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnPoista_clicked();
    
    void poistaSlot(QNetworkReply *reply);
    
private:
    Ui::Poista_Asiakas_Pankkitili_Yhteys *ui;
    QNetworkAccessManager *PoistaTiedotManager;
    QNetworkReply *reply;
};

#endif // POISTA_ASIAKAS_PANKKITILI_YHTEYS_H
