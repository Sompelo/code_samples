#include "paivita_kortin_tietoja.h"
#include "ui_paivita_kortin_tietoja.h"

Paivita_Kortin_Tietoja::Paivita_Kortin_Tietoja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paivita_Kortin_Tietoja)
{
    ui->setupUi(this);
}

Paivita_Kortin_Tietoja::~Paivita_Kortin_Tietoja()
{
    delete ui;
}



void Paivita_Kortin_Tietoja::on_btnTakaisin_clicked()
{
    this->close();
}

void Paivita_Kortin_Tietoja::on_btnPaivita_clicked()
{
    QJsonObject json;
    QString id = ui->leKortinId->text();
    QString pin2 = ui->lePin->text();
    QString tilinumero2 = ui->leTilinumero->text();
    QString pinVaarin2 = ui->lePinVaarin->text();
    QString luottoTila2 = ui->leLuottotila->text();
    QString idAsiakas2 = ui->leIdAsiakas->text();

    QString site_url = "http://localhost:3000/pankkikortti/";
    QString credentials = "root:root";
    QNetworkRequest request((site_url + id));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    Paivita_Kortin_Tietoja objHae;
    objHae.haeTiedot();


    if(pin2 == "")
        json.insert("pin", pin);
    else
    {
        json.insert("pin", pin2);
    }

    if(tilinumero2 == "")
        json.insert("tilinumero", QString::number(tilinumero.toInt()));
    else
    {
        json.insert("tilinumero", QString::number(tilinumero2.toInt()));
    }

    if(pinVaarin2 == "")
        json.insert("pinVaarin", QString::number(pinVaarin.toInt()));
    else
    {
        json.insert("pinVaarin", QString::number(pinVaarin2.toInt()));
    }

    if(luottoTila2 == "")
        json.insert("credit", QString::number(luottoTila.toInt()));
    else
    {
        json.insert("credit", QString::number(luottoTila2.toInt()));
    }

    if(idAsiakas2 == "")
        json.insert("idasiakas", QString::number(idAsiakas.toInt()));
    else
    {
        json.insert("idasiakas", QString::number(idAsiakas2.toInt()));
    }

    paivitaManager = new QNetworkAccessManager(this);
    connect(paivitaManager, SIGNAL(finished (QNetworkReply*)),
            this, SLOT(PaivitaSlot(QNetworkReply*)));
    reply = paivitaManager->put(request, QJsonDocument(json).toJson());
}

void Paivita_Kortin_Tietoja::PaivitaSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    qDebug() << response_data;
    if(response_data == "1")
    {
        ui->lePin->setText("");
        ui->leTilinumero->setText("");
        ui->lePinVaarin->setText("");
        ui->leLuottotila->setText("");
        ui->leIdAsiakas->setText("");
        ui->leKortinId->setText("");

        qDebug() << "Korttitiedot päivitetty";
        ui->labelInfo->setText("Korttitiedot päivitetty");
    }
    else
    {
        ui->lePin->setText("");
        ui->leTilinumero->setText("");
        ui->lePinVaarin->setText("");
        ui->leLuottotila->setText("");
        ui->leIdAsiakas->setText("");
        ui->leKortinId->setText("");

        qDebug() << "Korttitietojen päivittäminen epäonnistui";
        ui->labelInfo->setText("Korttitietojen päivittäminen epäonnistui");
    }
}

void Paivita_Kortin_Tietoja::haeTiedot()
{
    QString site_url = "http://localhost:3000/pankkikortti/";
    QString credentials = "root:root";
    korttiId = ui->leKortinId->text();
    QNetworkRequest request((site_url + korttiId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    korttiTiedotManager = new QNetworkAccessManager(this);
    connect(korttiTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(kortinTiedotSlot(QNetworkReply*)));
    reply2 = korttiTiedotManager->get(request);
}

void Paivita_Kortin_Tietoja::kortinTiedotSlot(QNetworkReply *reply2)
{
    QByteArray response_data = reply2->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

        QJsonObject json_obj = value.toObject();
        tilinumero = QString::number(json_obj["tilinumero"].toInt());
        luottoTila = QString::number(json_obj["credit"].toInt());
        pin = json_obj["pin"].toString();
        pinVaarin = QString::number(json_obj["pinVaarin"].toInt());
        idAsiakas = QString::number(json_obj["asiakasid"].toInt());
    }
}
