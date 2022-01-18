#include "nayta_tilin_tiedot.h"
#include "ui_nayta_tilin_tiedot.h"

nayta_tilin_tiedot::nayta_tilin_tiedot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nayta_tilin_tiedot)
{
    ui->setupUi(this);
}

nayta_tilin_tiedot::~nayta_tilin_tiedot()
{
    delete ui;
}

void nayta_tilin_tiedot::on_btnTakaisin_clicked()
{
    this->close();
}

void nayta_tilin_tiedot::on_btnHaeTiedot_clicked()
{
    QString site_url = "http://localhost:3000/pankkitili/";
    QString credentials = "root:root";
    QString tiliId = ui->leTilinId->text();
    QNetworkRequest request((site_url + tiliId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    tilinTiedotManager = new QNetworkAccessManager(this);
    connect(tilinTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(tilinTiedotSlot(QNetworkReply*)));
    reply = tilinTiedotManager->get(request);// post(request, QJsonDocument(json).toJson());
}

void nayta_tilin_tiedot::on_btnHaeKaikki_clicked()
{
    QString site_url = "http://localhost:3000/pankkitili/";
    QString credentials = "root:root";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    tilinTiedotManager = new QNetworkAccessManager(this);
    connect(tilinTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(tilinTiedotSlot(QNetworkReply*)));
    reply = tilinTiedotManager->get(request);// post(request, QJsonDocument(json).toJson());
}

void nayta_tilin_tiedot::tilinTiedotSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

       QJsonObject json_obj = value.toObject();
       tilinumero = QString::number(json_obj["tilinumero"].toInt());
       saldo = QString::number(json_obj["saldo"].toDouble());
       creditsaldo = QString::number(json_obj["creditsaldo"].toDouble());
//       credit_ja_saldo = QString::number(json_obj["credit_saldo"].toInt());

       tulostus +=  "tilinumero: " + tilinumero + "\nSaldo: " + saldo + "\nLuotto " + creditsaldo + "\n\n";
       ui->tbTiliInfo->setText(tulostus);
    }
}



/*void nayta_tilin_tiedot::kaikkiTiedotSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

       QJsonObject json_obj = value.toObject();
       idTili = json_obj["idTili"].toString();
       tyyppi = QString::number(json_obj["tyyppi"].toInt());
       saldo = QString::number(json_obj["saldo"].toDouble());
       credit = QString::number(json_obj["credit"].toDouble());
       credit_saldo = QString::number(json_obj["credit_saldo"].toInt());

       tulostus += "Tilin id: " + idTili + "\nTilityyppi: " + tyyppi + "\nSaldo: " + saldo + "\nLuotto " + credit_saldo + "\n\n";
       ui->tbTiliInfo->setText(tulostus);
    }
}*/
