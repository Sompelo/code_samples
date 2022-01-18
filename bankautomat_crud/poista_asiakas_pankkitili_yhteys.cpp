#include "poista_asiakas_pankkitili_yhteys.h"
#include "ui_poista_asiakas_pankkitili_yhteys.h"

Poista_Asiakas_Pankkitili_Yhteys::Poista_Asiakas_Pankkitili_Yhteys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Poista_Asiakas_Pankkitili_Yhteys)
{
    ui->setupUi(this);
}

Poista_Asiakas_Pankkitili_Yhteys::~Poista_Asiakas_Pankkitili_Yhteys()
{
    delete ui;
}

void Poista_Asiakas_Pankkitili_Yhteys::on_btnTakaisin_clicked()
{
    this->close();
}

void Poista_Asiakas_Pankkitili_Yhteys::on_btnPoista_clicked()
{
    QJsonObject json;
    QString site_url = "http://localhost:3000/del/";
    QString credentials = "root:root";
    QString asiakasId = ui->leAsiakasId->text();
    QString pankkitili = ui->leTilinumero->text();
    json.insert("idasiakas", asiakasId);
    json.insert("tilinumero", pankkitili);
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    PoistaTiedotManager = new QNetworkAccessManager(this);
    connect(PoistaTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(poistaSlot(QNetworkReply*)));
    reply = PoistaTiedotManager->post(request, QJsonDocument(json).toJson());
}

void Poista_Asiakas_Pankkitili_Yhteys::poistaSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();

    if(response_data == "1")
    {
        ui->leAsiakasId->setText("");
        ui->leTilinumero->setText("");
        ui->labelInfo->setText("Yhteys poistettu");
    }
    else
    {
        ui->leAsiakasId->setText("");
        ui->leTilinumero->setText("");
        ui->labelInfo->setText("Yhteyden poistaminen epäonnistui");
    }
}
