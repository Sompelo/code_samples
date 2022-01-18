#include "poista_asiakas.h"
#include "ui_poista_asiakas.h"

Poista_Asiakas::Poista_Asiakas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Poista_Asiakas)
{
    ui->setupUi(this);
}

Poista_Asiakas::~Poista_Asiakas()
{
    delete ui;
}

void Poista_Asiakas::on_btnTakaisin_clicked()
{
    this->close();
}

void Poista_Asiakas::on_btnPoista_clicked()
{
    QString site_url = "http://localhost:3000/asiakas/";
    QString credentials = "root:root";
    QString asiakasId = ui->leAsiakasId->text();
    QNetworkRequest request((site_url + asiakasId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    PoistaTiedotManager = new QNetworkAccessManager(this);
    connect(PoistaTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(poistaSlot(QNetworkReply*)));
    reply = PoistaTiedotManager->deleteResource(request);
}

void Poista_Asiakas::poistaSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();

    if(response_data == "1")
    {
        ui->leAsiakasId->setText("");
        ui->labelInfo->setText("Asiakkaan tiedot poistettu");
    }
    else
    {
        ui->leAsiakasId->setText("");
        ui->labelInfo->setText("Tietojen poistaminen epäonnistui");
    }

}
