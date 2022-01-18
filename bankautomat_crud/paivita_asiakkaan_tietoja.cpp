#include "paivita_asiakkaan_tietoja.h"
#include "ui_paivita_asiakkaan_tietoja.h"

Paivita_Asiakkaan_Tietoja::Paivita_Asiakkaan_Tietoja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paivita_Asiakkaan_Tietoja)
{
    ui->setupUi(this);
}

Paivita_Asiakkaan_Tietoja::~Paivita_Asiakkaan_Tietoja()
{
    delete ui;
}

void Paivita_Asiakkaan_Tietoja::on_btnTakaisin_clicked()
{
    this->close();
}

void Paivita_Asiakkaan_Tietoja::on_btnPaivita_clicked()
{
    QJsonObject json;
    id = ui->leAsiakasId->text();

    QString nimi2 = ui->leNimi->text();
    QString osoite2 = ui->leOsoite->text();
    QString puhelinnro2 = ui->lePuhelinnumero->text();

    QString site_url = "http://localhost:3000/asiakas/";
    QString credentials = "root:root";
    QNetworkRequest request((site_url + id));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    this->haeTiedot();

    qDebug() << nimi << osoite << puhelinnro;

    if(nimi2 == "")
        json.insert("nimi", nimi);
    else
    {
        json.insert("nimi", nimi2);
    }

    if(osoite2 == "")
        json.insert("osoite", osoite);
    else
    {
        json.insert("osoite", osoite2);
    }

    if(puhelinnro2 == "")
        json.insert("puhelinnro", puhelinnro);
    else
    {
        json.insert("puhelinnro", puhelinnro2);
    }

    paivitaManager = new QNetworkAccessManager(this);
    connect(paivitaManager, SIGNAL(finished (QNetworkReply*)),
            this, SLOT(PaivitaSlot(QNetworkReply*)));
    reply = paivitaManager->put(request, QJsonDocument(json).toJson());
}

void Paivita_Asiakkaan_Tietoja::PaivitaSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
//    qDebug() << response_data;
    if(response_data == "1")
    {
        ui->leNimi->setText("");
        ui->leOsoite->setText("");
        ui->lePuhelinnumero->setText("");
        qDebug() << "Asiakastiedot päivitetty";
        ui->labelInfo->setText("Asiakastiedot päivitetty");
    }
    else
    {
        ui->leNimi->setText("");
        ui->leOsoite->setText("");
        ui->lePuhelinnumero->setText("");
        qDebug() << "Asiakastietojen päivittäminen epäonnistui";
        ui->labelInfo->setText("Asiakastietojen päivittäminen epäonnistui");
    }
}

void Paivita_Asiakkaan_Tietoja::haeTiedot()
{
//    qDebug() << "Kukkuu";
    QString site_url = "http://localhost:3000/asiakas/";
    QString credentials = "root:root";
    qDebug() << "Asiakas id: " << id;
    QNetworkRequest request((site_url + id));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    asiakasTiedotManager = new QNetworkAccessManager(this);
    connect(asiakasTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(asiakasTiedotSlot(QNetworkReply*)));
    reply2 = asiakasTiedotManager->get(request);
//    qDebug() << "Kukkuu";
}

void Paivita_Asiakkaan_Tietoja::asiakasTiedotSlot(QNetworkReply *reply2)
{
//    qDebug() << "Kukkuu";
    QByteArray response_data = reply2->readAll();
//    qDebug() << response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
//    qDebug() << json_array;
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        nimi = json_obj["nimi"].toString();
        osoite = json_obj["osoite"].toString();
        puhelinnro = json_obj["puhelinnro"].toString();
//        qDebug() << nimi << osoite << puhelinnro;
    }
}
