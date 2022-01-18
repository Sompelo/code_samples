#ifndef LISAA_UUSI_TILI_H
#define LISAA_UUSI_TILI_H

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
class Lisaa_Uusi_Tili;
}

class Lisaa_Uusi_Tili : public QDialog
{
    Q_OBJECT

public:
    explicit Lisaa_Uusi_Tili(QWidget *parent = 0);
    ~Lisaa_Uusi_Tili();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnLisaa_clicked();

    void lisaaTiliSlot(QNetworkReply *reply);


private:
    Ui::Lisaa_Uusi_Tili *ui;
    QNetworkAccessManager *lisaaTiliManager;
    QNetworkReply *reply;
    PankkitilinYhdistaminenAsiakastiliin *objPankkitilinYhdistaminenAsiakastiliin;
};

#endif // LISAA_UUSI_TILI_H
