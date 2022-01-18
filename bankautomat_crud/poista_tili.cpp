#include "poista_tili.h"
#include "ui_poista_tili.h"

Poista_Tili::Poista_Tili(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Poista_Tili)
{
    ui->setupUi(this);
}

Poista_Tili::~Poista_Tili()
{
    delete ui;
}

void Poista_Tili::on_btnTakaisin_clicked()
{
    this->close();
}

void Poista_Tili::on_btnPoista_clicked()
{
    QString site_url = "http://localhost:3000/pankkitili/";
    QString credentials = "root:root";
    QString tilinId = ui->leTilinId->text();
    QNetworkRequest request((site_url + tilinId));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    PoistaTiedotManager = new QNetworkAccessManager(this);
    connect(PoistaTiedotManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(poistaSlot(QNetworkReply*)));
    reply = PoistaTiedotManager->deleteResource(request);
}

void Poista_Tili::poistaSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();

    if(response_data == "1")
    {
        ui->leTilinId->setText("");
        ui->labelInfo->setText("Tilin tiedot poistettu");
    }
    else
    {
        ui->leTilinId->setText("");
        ui->labelInfo->setText("Tietojen poistaminen epäonnistui");
    }
}
