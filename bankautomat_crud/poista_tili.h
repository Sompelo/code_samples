#ifndef POISTA_TILI_H
#define POISTA_TILI_H

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
class Poista_Tili;
}

class Poista_Tili : public QDialog
{
    Q_OBJECT

public:
    explicit Poista_Tili(QWidget *parent = 0);
    ~Poista_Tili();

private slots:
    void on_btnTakaisin_clicked();
    void on_btnPoista_clicked();

    void poistaSlot(QNetworkReply *reply);

private:
    Ui::Poista_Tili *ui;
    QNetworkAccessManager *PoistaTiedotManager;
    QNetworkReply *reply;
};

#endif // POISTA_TILI_H
