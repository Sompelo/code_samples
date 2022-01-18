#ifndef TUNNUSKYSELY_H
#define TUNNUSKYSELY_H

#include <QDialog>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

namespace Ui {
class Tunnuskysely;
}

class Tunnuskysely : public QDialog
{
    Q_OBJECT

public:
    explicit Tunnuskysely(QWidget *parent = 0);
    ~Tunnuskysely();

    void closeEvent(QCloseEvent *event);

private slots:
    void loginSlot(QNetworkReply *reply);
    void on_pushButton_clicked();

private:
    Ui::Tunnuskysely *ui;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;

signals:
    void close();
    void haeAsiakkaanTiedot();
};

#endif // TUNNUSKYSELY_H
