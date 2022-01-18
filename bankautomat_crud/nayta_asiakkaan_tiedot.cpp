#include "nayta_asiakkaan_tiedot.h"
#include "ui_nayta_asiakkaan_tiedot.h"

Nayta_Asiakkaan_Tiedot::Nayta_Asiakkaan_Tiedot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nayta_Asiakkaan_Tiedot)
{
    ui->setupUi(this);
}

Nayta_Asiakkaan_Tiedot::~Nayta_Asiakkaan_Tiedot()
{
    delete ui;
}

void Nayta_Asiakkaan_Tiedot::on_btnTakaisin_clicked()
{
    this->close();
}


void Nayta_Asiakkaan_Tiedot::on_btnHaeTiedot_clicked()
{
    QString site_url = "http://localhost:3000/asiakas/";
    QString credentials = "root:root";
    QString asiakasId = ui->leAsiakasId->text();
    QNetworkRequest request((site_url + asiakasId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    asiakkaanTiedotManager = new QNetworkAccessManager(this);
    connect(asiakkaanTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(asiakkaanTiedotSlot(QNetworkReply*)));
    reply = asiakkaanTiedotManager->get(request);
}

void Nayta_Asiakkaan_Tiedot::on_btnHaeKaikki_clicked()
{
    QString site_url = "http://localhost:3000/asiakas/";
    QString credentials = "root:root";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    kaikkiTiedotManager = new QNetworkAccessManager(this);
    connect(kaikkiTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(kaikkiTiedotSlot(QNetworkReply*)));
    reply = kaikkiTiedotManager->get(request);
}

void Nayta_Asiakkaan_Tiedot::asiakkaanTiedotSlot(QNetworkReply *reply)
{
    ui->tbAsiakasInfo->setText("");
    ui->labelAsiakasInfo->setText("");
    QByteArray response_data = reply->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

       QJsonObject json_obj = value.toObject();
       idasiakas = QString::number(json_obj["idasiakas"].toInt());
       nimi = json_obj["nimi"].toString();
       osoite = json_obj["osoite"].toString();
       puhelinnro = json_obj["puhelinnro"].toString();
       tulostus += "Asiakas id: " + idasiakas + "\nNimi: " + nimi + "\nOsoite: " + osoite +
               "\nPuhelin: " + puhelinnro + "\n\n";
       ui->tbAsiakasInfo->setText(tulostus);
    }
}

void Nayta_Asiakkaan_Tiedot::kaikkiTiedotSlot(QNetworkReply *reply2)
{
    ui->tbAsiakasInfo->setText("");
    ui->labelAsiakasInfo->setText("");
    QByteArray response_data = reply2->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

       QJsonObject json_obj = value.toObject();
       idasiakas = QString::number(json_obj["idasiakas"].toInt());
       nimi = json_obj["nimi"].toString();
       osoite = json_obj["osoite"].toString();
       puhelinnro = json_obj["puhelinnro"].toString();

       tulostus +="Asiakkaan id: " + idasiakas + "\nNimi: " + nimi + "\nOsoite: " + osoite + "\nPuhelinnumero: " + puhelinnro + "\n\n";
       ui->tbAsiakasInfo->setText(tulostus);
    }
}

