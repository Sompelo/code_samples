#include "pankkitilinyhdistaminenasiakastiliin.h"
#include "ui_pankkitilinyhdistaminenasiakastiliin.h"

PankkitilinYhdistaminenAsiakastiliin::PankkitilinYhdistaminenAsiakastiliin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PankkitilinYhdistaminenAsiakastiliin)
{
    ui->setupUi(this);

}

PankkitilinYhdistaminenAsiakastiliin::~PankkitilinYhdistaminenAsiakastiliin()
{
    delete ui;
}

void PankkitilinYhdistaminenAsiakastiliin::on_btnTakaisin_clicked()
{
    this->close();
}

void PankkitilinYhdistaminenAsiakastiliin::pankkitilinHaku()
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
    reply = tilinTiedotManager->get(request);
}

void PankkitilinYhdistaminenAsiakastiliin::asiakastilinHaku()
{
    QString site_url = "http://localhost:3000/asiakas/";
    QString credentials = "root:root";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    asiakasTiedotManager = new QNetworkAccessManager(this);
    connect(asiakasTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(asiakasTiedotSlot(QNetworkReply*)));
    reply = asiakasTiedotManager->get(request);
}

void PankkitilinYhdistaminenAsiakastiliin::on_btnYhdista_clicked()
{
    QJsonObject json2;
    asiakasId = ui->leAsiakasId->text();
    tilinumero = ui->leTilinumero->text();

    json2.insert("idasiakas", asiakasId);
    json2.insert("tilinumero", tilinumero);

    QString site_url2 = "http://localhost:3000/asiakas_pankkitili";
    QString credentials2 = "root:root";
    QNetworkRequest request2((site_url2));
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data2 = credentials2.toLocal8Bit().toBase64();
    QString headerData2 = "Basic " + data2;
    request2.setRawHeader("Authorization", headerData2.toLocal8Bit());

    yhdistaTiliAsiakkaaseenManager = new QNetworkAccessManager(this);
    connect(yhdistaTiliAsiakkaaseenManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(yhdistaTiliAsiakkaaseenSlot(QNetworkReply*)));
    reply2 = yhdistaTiliAsiakkaaseenManager->post(request2, QJsonDocument(json2).toJson());
}

void PankkitilinYhdistaminenAsiakastiliin::tilinTiedotSlot(QNetworkReply *reply)
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

       tulostus +=  "Tilinumero: " + tilinumero + "\nSaldo: " + saldo + "\nLuotto " + creditsaldo + "\n\n";
       ui->tbPankkitiliInfo->setText(tulostus);
    }
}

void PankkitilinYhdistaminenAsiakastiliin::asiakasTiedotSlot(QNetworkReply *reply3)
{
    QByteArray response_data = reply3->readAll();
    QString tulostus;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {

       QJsonObject json_obj = value.toObject();
       QString idasiakas = QString::number(json_obj["idasiakas"].toInt());
       QString nimi = json_obj["nimi"].toString();
       QString osoite = json_obj["osoite"].toString();
       QString puhelinnro = json_obj["puhelinnro"].toString();

       tulostus +=  "Asiakas id: " + idasiakas + "\nNimi: " + nimi + "\nOsoite: " + osoite + "\nPuhelinnumero: " + puhelinnro + "\n\n";
       ui->tbAsiakasInfo->setText(tulostus);
    }
}

void PankkitilinYhdistaminenAsiakastiliin::yhdistaTiliAsiakkaaseenSlot(QNetworkReply *reply2)
{
    QByteArray response_data = reply2->readAll();
    qDebug() << response_data;
    if(response_data == "1")
    {
        ui->leAsiakasId->setText("");
        ui->leTilinumero->setText("");
        qDebug() << "Pankkitili yhdistetty asiakastiliin.";
        ui->labelInfo->setText("Pankkitili yhdistetty asiakastiliin.");
//        ui->labelInfo->setText("Pankkitili listätty ja yhdistetty asiakastiliin");
    }
    else
    {
        ui->leAsiakasId->setText("");
        ui->leTilinumero->setText("");
        qDebug() << "Pankkitilin yhdistäminen asiakastiliin epäonnistui";
        ui->labelInfo->setText("Pankkitilin yhdistäminen asiakastiliin epäonnistui");
//        ui->labelInfo->setText("Pankkitilin yhdistäminen asiakastiliin epäonnistui");
    }
}
