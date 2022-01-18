#include "asiakas_pankkitili_yhteys.h"
#include "ui_asiakas_pankkitili_yhteys.h"

Asiakas_Pankkitili_Yhteys::Asiakas_Pankkitili_Yhteys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Asiakas_Pankkitili_Yhteys)
{
    ui->setupUi(this);
}

Asiakas_Pankkitili_Yhteys::~Asiakas_Pankkitili_Yhteys()
{
    delete ui;
}

void Asiakas_Pankkitili_Yhteys::on_btnTakaisin_clicked()
{
    this->close();
}

void Asiakas_Pankkitili_Yhteys::on_btnHae_clicked()
{
    QString site_url = "http://localhost:3000/asiakas_pankkitili/";
    QString credentials = "root:root";
    QString asiakasId = ui->leAsiakasId->text();
    QString tilinumero = ui->leTilinumero->text();
    QNetworkRequest request((site_url + asiakasId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    yhteysManager = new QNetworkAccessManager(this);
    connect(yhteysManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(yhteysSlot(QNetworkReply*)));
    reply = yhteysManager->get(request);
}

void Asiakas_Pankkitili_Yhteys::yhteysSlot(QNetworkReply *reply)
{
    ui->tbYhteysInfo->setText("");
    ui->labelInfo->setText("");
    QByteArray response_data = reply->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

       QJsonObject json_obj = value.toObject();
       QString idasiakas = QString::number(json_obj["idasiakas"].toInt());
       QString tilinumero = QString::number(json_obj["tilinumero"].toInt());
       tulostus += "Asiakas id: " + idasiakas + "\nTilinumero: " + tilinumero + "\n\n";
       ui->tbYhteysInfo->setText(tulostus);
    }
}
