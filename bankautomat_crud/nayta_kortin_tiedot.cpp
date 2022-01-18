#include "nayta_kortin_tiedot.h"
#include "ui_nayta_kortin_tiedot.h"

Nayta_Kortin_Tiedot::Nayta_Kortin_Tiedot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nayta_Kortin_Tiedot)
{
    ui->setupUi(this);
}

Nayta_Kortin_Tiedot::~Nayta_Kortin_Tiedot()
{
    delete ui;
}

void Nayta_Kortin_Tiedot::on_btnTakaisin_clicked()
{
    this->close();
}

void Nayta_Kortin_Tiedot::on_btnHae_clicked()
{
    QString site_url = "http://localhost:3000/pankkikortti/";
    QString credentials = "root:root";
    QString korttiId = ui->leKorttiId->text();
    QNetworkRequest request((site_url + korttiId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    korttiTiedotManager = new QNetworkAccessManager(this);
    connect(korttiTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(kortinTiedotSlot(QNetworkReply*)));
    reply = korttiTiedotManager->get(request);
}

void Nayta_Kortin_Tiedot::on_btnHaeKaikki_clicked()
{
    QString site_url = "http://localhost:3000/pankkikortti/";
    QString credentials = "root:root";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    korttiTiedotManager = new QNetworkAccessManager(this);
    connect(korttiTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(kortinTiedotSlot(QNetworkReply*)));
    reply = korttiTiedotManager->get(request);
}

void Nayta_Kortin_Tiedot::kortinTiedotSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

        QJsonObject json_obj = value.toObject();
        korttinumero = QString::number(json_obj["korttinumero"].toInt());
        tilinumero = QString::number(json_obj["tilinumero"].toInt());
        QString asiakasId = QString::number(json_obj["idasiakas"].toInt());
        credit = QString::number(json_obj["credit"].toInt());
        pin = json_obj["pin"].toString();
        pinVaarin = QString::number(json_obj["pinVaarin"].toInt());

        tulostus += "Korttinumero: " + korttinumero + "\nTilinumero: " + tilinumero + "\nAsiakkaan Id: " + asiakasId + "\nOnko Luottoa (1/0): " + credit + "\nKortin pin: " + pin + "\nPin annettu väärin " + pinVaarin + " kertaa\n\n";
        ui->tbKorttiInfo->setText(tulostus);
    }
}

/*void Nayta_Kortin_Tiedot::kaikkiTiedotSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

       QJsonObject json_obj = value.toObject();
       idKortti = json_obj["idKortti"].toString();
       idAsiakas = json_obj["asiakas_idAsiakas"].toString();
       idTili = json_obj["tili_idTili"].toString();
       pin = json_obj["pin"].toString();

       tulostus += "Kortin id: " + idKortti + "\nAsiakkaan id: " + idAsiakas + "\nTilin id: " + idTili + "\nkortin pin: " + pin + "\n\n";
       ui->tbKorttiInfo->setText(tulostus);
    }
}*/
