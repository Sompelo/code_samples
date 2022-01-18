#include "lisaa_uusi_kortti.h"
#include "ui_lisaa_uusi_kortti.h"

Lisaa_Uusi_Kortti::Lisaa_Uusi_Kortti(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lisaa_Uusi_Kortti)
{
    ui->setupUi(this);
}

Lisaa_Uusi_Kortti::~Lisaa_Uusi_Kortti()
{
    delete ui;
}

void Lisaa_Uusi_Kortti::on_btnTakaisin_clicked()
{
    this->close();
}

void Lisaa_Uusi_Kortti::on_btnLisaaKortti_clicked()
{
    QJsonObject json;
    QString credit = ui->leCredit->text();
    QString tilinumero = ui->leTilinumero->text();
    QString pin = ui->lePin->text();
    QString idasiakas = ui->leIdAsiakas->text();

    if(credit == "")
        ui->labelInfo->setText("Luotto-kentästä puuttuu tieto");

    else if(tilinumero == "")
        ui->labelInfo->setText("Tilinumero-kentästä puuttuu tieto");

    else if(pin == "")
        ui->labelInfo->setText("Pin-kentästä puuttuu tieto");

    else
    {
        json.insert("credit", credit);
        json.insert("tilinumero", tilinumero);
        json.insert("pin", pin);
        json.insert("idasiakas", idasiakas);

        QString site_url = "http://localhost:3000/pankkikortti";
        QString credentials = "root:root";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray data = credentials.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        request.setRawHeader("Authorization", headerData.toLocal8Bit());
        lisaaKorttiManager = new QNetworkAccessManager(this);
        connect(lisaaKorttiManager, SIGNAL(finished (QNetworkReply*)),
                this, SLOT(lisaaKorttiSlot(QNetworkReply*)));
        reply = lisaaKorttiManager->post(request, QJsonDocument(json).toJson());
    }
}

void Lisaa_Uusi_Kortti::lisaaKorttiSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    qDebug() << response_data;
    if(response_data == "1")
    {
        ui->leCredit->setText("");
        ui->leTilinumero->setText("");
        ui->lePin->setText("");
        ui->leIdAsiakas->setText("");
        qDebug() << "Kortti lisätty";
        ui->labelInfo->setText("Kortti lisätty!");
    }
    else
    {
        ui->leCredit->setText("");
        ui->leTilinumero->setText("");
        ui->lePin->setText("");
        ui->leIdAsiakas->setText("");
        qDebug() << "Kortin lisääminen epäonnistui";
        ui->labelInfo->setText("Kortin lisääminen epäonnistui");
    }
}
