#include "lisaa_uusi_asiakas.h"
#include "ui_lisaa_uusi_asiakas.h"

Lisaa_Uusi_Asiakas::Lisaa_Uusi_Asiakas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lisaa_Uusi_Asiakas)
{
    ui->setupUi(this);
}

Lisaa_Uusi_Asiakas::~Lisaa_Uusi_Asiakas()
{
    delete ui;
}

void Lisaa_Uusi_Asiakas::on_btnTakaisin_clicked()
{
    this->close();
}

void Lisaa_Uusi_Asiakas::on_btnLisaa_clicked()
{
    QJsonObject json;
    QString nimi = ui->leNimi->text();
    QString osoite = ui->leOsoite->text();
    QString puhelin = ui->lePuh->text();

    if(nimi == "")
        ui->labelInfo->setText("Nimi-kentästä puuttuu tieto");

    else if(osoite == "")
        ui->labelInfo->setText("Osoite-kentästä puuttuu tieto");

    else if(puhelin == "")
        ui->labelInfo->setText("Puhelinnumero-kentästä puuttuu tieto");

    else
    {
        json.insert("nimi", nimi);
        json.insert("osoite", osoite);
        json.insert("puhelinnro", puhelin);

        QString site_url = "http://localhost:3000/asiakas";
        QString credentials = "root:root";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray data = credentials.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        request.setRawHeader("Authorization", headerData.toLocal8Bit());
        lisaaAsiakasManager = new QNetworkAccessManager(this);
        connect(lisaaAsiakasManager, SIGNAL(finished (QNetworkReply*)),
                this, SLOT(lisaaAsiakasSlot(QNetworkReply*)));
        reply = lisaaAsiakasManager->post(request, QJsonDocument(json).toJson());
    }
}

void Lisaa_Uusi_Asiakas::lisaaAsiakasSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    qDebug() << response_data;
    if(response_data == "1")
    {
        ui->leNimi->setText("");
        ui->leOsoite->setText("");
        ui->lePuh->setText("");
        qDebug() << "Asiakas lisätty";
        ui->labelInfo->setText("Asiakas lisätty!");
    }
    else
    {
        ui->leNimi->setText("");
        ui->leOsoite->setText("");
        ui->lePuh->setText("");
        qDebug() << "Asiakkaan lisääminen epäonnistui";
        ui->labelInfo->setText("Asiakkaan lisääminen epäonnistui");
    }
}
