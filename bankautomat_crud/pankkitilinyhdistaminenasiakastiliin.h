#ifndef PANKKITILINYHDISTAMINENASIAKASTILIIN_H
#define PANKKITILINYHDISTAMINENASIAKASTILIIN_H

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
class PankkitilinYhdistaminenAsiakastiliin;
}

class PankkitilinYhdistaminenAsiakastiliin : public QDialog
{
    Q_OBJECT

public:
    explicit PankkitilinYhdistaminenAsiakastiliin(QWidget *parent = 0);
    ~PankkitilinYhdistaminenAsiakastiliin();

    void pankkitilinHaku();
    void asiakastilinHaku();

private slots:
    void on_btnTakaisin_clicked();

    void yhdistaTiliAsiakkaaseenSlot(QNetworkReply *reply2);
    void on_btnYhdista_clicked();

    void tilinTiedotSlot(QNetworkReply *reply);
    void asiakasTiedotSlot(QNetworkReply *reply3);

private:
    Ui::PankkitilinYhdistaminenAsiakastiliin *ui;
    QNetworkAccessManager *yhdistaTiliAsiakkaaseenManager;
    QNetworkAccessManager *tilinTiedotManager;
    QNetworkAccessManager *asiakasTiedotManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QNetworkReply *reply3;

    QString asiakasId;
    QString tilinumero;
    QString saldo;
    QString creditsaldo;
};

#endif // PANKKITILINYHDISTAMINENASIAKASTILIIN_H
