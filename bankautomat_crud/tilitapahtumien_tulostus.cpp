#include "tilitapahtumien_tulostus.h"
#include "ui_tilitapahtumien_tulostus.h"

Tilitapahtumien_Tulostus::Tilitapahtumien_Tulostus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tilitapahtumien_Tulostus)
{
    ui->setupUi(this);
}

Tilitapahtumien_Tulostus::~Tilitapahtumien_Tulostus()
{
    delete ui;
}

void Tilitapahtumien_Tulostus::on_btnTakaisin_clicked()
{
    this->close();
}

void Tilitapahtumien_Tulostus::on_btnHae_clicked()
{
    ui->tbTilitapahtumat->setText("");
    QString site_url = "http://localhost:3000/tapahtumat/";
    QString credentials = "root:root";
    QString korttiId = ui->leKorttinumero->text();
    QNetworkRequest request((site_url + korttiId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    tiliTapahtumaManager = new QNetworkAccessManager(this);
    connect(tiliTapahtumaManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(tilitapahtumaSlot(QNetworkReply*)));
    reply = tiliTapahtumaManager->get(request);
}

void Tilitapahtumien_Tulostus::tilitapahtumaSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

       QJsonObject json_obj = value.toObject();
       QString idtilitapahtumat = QString::number(json_obj["idtapahtumat"].toInt());
       QString aikaleima = json_obj["aikaleima"].toString();
       QString tapahtuma = json_obj["tapahtuma"].toString();
       QString summa = QString::number(json_obj["summa"].toDouble());
       QString credit = QString::number(json_obj["credit"].toInt());
       QString tilinumero2 = QString::number(json_obj["tilinumero"].toInt());

       QChar aikaleimaTaulukko[aikaleima.size()];
       QString aikaleima2;
       int j = 0;
       for(int i = 0; i < aikaleima.size(); i++)
       {
           if (aikaleima.at(i) == 'T' || aikaleima.at(i) == 'Z')
               aikaleimaTaulukko[i] = ' ';
           else aikaleimaTaulukko[i] = aikaleima.at(i);
           j = i;
       }

       for(int i = 0; i < j; i++)
       {
           aikaleima2.append(aikaleimaTaulukko[i]);
       }

       tulostus +=  "Tilitapahtuma id: " + idtilitapahtumat + "\nAikaleima: " + aikaleima2 + "\nTapahtuma: "
               + tapahtuma + "\nSumma: " + summa +"\nCredit: " + credit + "\nTilinumero: " + tilinumero2 +
               "\n\n";
       ui->tbTilitapahtumat->setText(tulostus);
    }
}
