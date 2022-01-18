#ifndef POISTA_KORTTI_H
#define POISTA_KORTTI_H

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
class Poista_Kortti;
}

class Poista_Kortti : public QDialog
{
    Q_OBJECT

public:
    explicit Poista_Kortti(QWidget *parent = 0);
    ~Poista_Kortti();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnPoista_clicked();

    void poistaSlot(QNetworkReply *reply);

private:
    Ui::Poista_Kortti *ui;
    QNetworkAccessManager *PoistaTiedotManager;
    QNetworkReply *reply;
};

#endif // POISTA_KORTTI_H
