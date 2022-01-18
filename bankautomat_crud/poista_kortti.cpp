#include "poista_kortti.h"
#include "ui_poista_kortti.h"

Poista_Kortti::Poista_Kortti(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Poista_Kortti)
{
    ui->setupUi(this);
}

Poista_Kortti::~Poista_Kortti()
{
    delete ui;
}

void Poista_Kortti::on_btnTakaisin_clicked()
{
    this->close();
}

void Poista_Kortti::on_btnPoista_clicked()
{
    QString site_url = "http://localhost:3000/pankkikortti/";
    QString credentials = "root:root";
    QString kortinId = ui->leKortinId->text();
    QNetworkRequest request((site_url + kortinId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    PoistaTiedotManager = new QNetworkAccessManager(this);
    connect(PoistaTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(poistaSlot(QNetworkReply*)));
    reply = PoistaTiedotManager->deleteResource(request);
}

void Poista_Kortti::poistaSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();

    if(response_data == "1")
    {
        ui->leKortinId->setText("");
        ui->labelInfo->setText("Kortin tiedot poistettu");
    }
    else
    {
        ui->leKortinId->setText("");
        ui->labelInfo->setText("Tietojen poistaminen epäonnistui");
    }
}
