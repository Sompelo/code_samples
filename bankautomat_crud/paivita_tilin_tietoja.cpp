#include "paivita_tilin_tietoja.h"
#include "ui_paivita_tilin_tietoja.h"

Paivita_Tilin_Tietoja::Paivita_Tilin_Tietoja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paivita_Tilin_Tietoja)
{
    ui->setupUi(this);
}

Paivita_Tilin_Tietoja::~Paivita_Tilin_Tietoja()
{
    delete ui;
}

void Paivita_Tilin_Tietoja::on_btnTakaisin_clicked()
{
    this->close();
}

void Paivita_Tilin_Tietoja::on_btnPaivita_clicked()
{
    QJsonObject json;

    QString id = ui->leTilinumero->text();
    QString saldo2 = ui->leSaldo->text();
    QString creditSaldo2 = ui->leLuotto->text();
    QString luottoRaja2 = ui->leLuottoRaja->text();

    QString site_url = "http://localhost:3000/pankkitili/";
    QString credentials = "root:root";
    QNetworkRequest request((site_url + id));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    Paivita_Tilin_Tietoja objHae;
    objHae.haeTiedot();


    if(saldo2 == "")
        json.insert("saldo", QString::number(saldo.toInt()));
    else
    {
        json.insert("saldo", QString::number(saldo2.toInt()));
    }

    if(creditSaldo2 == "")
        json.insert("creditsaldo", QString::number(creditSaldo.toInt()));
    else
    {
        json.insert("creditsaldo", QString::number(creditSaldo2.toInt()));
    }

    if(luottoRaja2 == "")
        json.insert("luottoraja", QString::number(luottoRaja.toInt()));
    else
    {
        json.insert("luottoraja", QString::number(luottoRaja2.toInt()));
    }

    paivitaManager = new QNetworkAccessManager(this);
    connect(paivitaManager, SIGNAL(finished (QNetworkReply*)),
            this, SLOT(PaivitaSlot(QNetworkReply*)));
    reply = paivitaManager->put(request, QJsonDocument(json).toJson());
}

void Paivita_Tilin_Tietoja::PaivitaSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    qDebug() << response_data;
    if(response_data == "1")
    {
        ui->leSaldo->setText("");
        ui->leLuotto->setText("");
        ui->leTilinumero->setText("");
        ui->leLuottoRaja->setText("");

        qDebug() << "Tilin tiedot päivitetty";
        ui->labelInfo->setText("Tilin tiedot päivitetty");
    }
    else
    {
        ui->leSaldo->setText("");
        ui->leLuotto->setText("");
        ui->leTilinumero->setText("");
        ui->leLuottoRaja->setText("");

        qDebug() << "Tilitietojen päivittäminen epäonnistui";
        ui->labelInfo->setText("Tilitietojen päivittäminen epäonnistui");
    }
}

void Paivita_Tilin_Tietoja::haeTiedot()
{
    QString site_url = "http://localhost:3000/pankkitili/";
    QString credentials = "root:root";
    QString tiliId = ui->leTilinumero->text();
    QNetworkRequest request((site_url + tiliId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    tiliTiedotManager = new QNetworkAccessManager(this);
    connect(tiliTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(tilinTiedotSlot(QNetworkReply*)));
    reply2 = tiliTiedotManager->get(request);
}

void Paivita_Tilin_Tietoja::tilinTiedotSlot(QNetworkReply *reply2)
{
    QByteArray response_data = reply2->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

        QJsonObject json_obj = value.toObject();
//        korttinumero = QString::number(json_obj["korttinumero"].toInt());
        saldo = QString::number(json_obj["saldo"].toDouble());
        creditSaldo = QString::number(json_obj["creditsaldo"].toDouble());
        luottoRaja = QString::number(json_obj["luottoraja"].toInt());
    }
}

void Paivita_Tilin_Tietoja::on_btnYhdista_clicked()
{
    objYhdistaminen = new PankkitilinYhdistaminenAsiakastiliin;
    objYhdistaminen->show();
    objYhdistaminen->pankkitilinHaku();
    objYhdistaminen->asiakastilinHaku();
}
