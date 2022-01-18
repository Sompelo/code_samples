#include "lisaa_uusi_tili.h"
#include "ui_lisaa_uusi_tili.h"

Lisaa_Uusi_Tili::Lisaa_Uusi_Tili(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lisaa_Uusi_Tili)
{
    ui->setupUi(this);
}

Lisaa_Uusi_Tili::~Lisaa_Uusi_Tili()
{
    delete ui;
}

void Lisaa_Uusi_Tili::on_btnTakaisin_clicked()
{
    this->close();
}

void Lisaa_Uusi_Tili::on_btnLisaa_clicked()
{
    QJsonObject json;
    QString saldo = ui->leSaldo->text();
    QString luotto = ui->leLuotto->text();
    QString luottoraja = ui->leLuottoRaja->text();

    if(saldo == "")
        ui->labelInfo->setText("Saldo-kentästä puuttuu tieto");

    else if(luotto == "")
        ui->labelInfo->setText("Luotto-kentästä puuttuu tieto"); //TO-DO: Lisää REST-API toiminto, jossa samalla, kun lisätään uusi tili
                                                                 //niin se tili linkataan asiakas_pankkitili tietokannan avulla
                                                                 //asiakkaaseen.

    else
    {
        json.insert("saldo", saldo);
        json.insert("creditsaldo", luotto);
        json.insert("luottoraja", luottoraja);

        QString site_url = "http://localhost:3000/pankkitili";
        QString credentials = "root:root";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray data = credentials.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        request.setRawHeader("Authorization", headerData.toLocal8Bit());

        lisaaTiliManager = new QNetworkAccessManager(this);
        connect(lisaaTiliManager, SIGNAL(finished (QNetworkReply*)),
                this, SLOT(lisaaTiliSlot(QNetworkReply*)));
        reply = lisaaTiliManager->post(request, QJsonDocument(json).toJson());
    }
}

void Lisaa_Uusi_Tili::lisaaTiliSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    qDebug() << response_data;
    if(response_data == "1")
    {
        ui->leSaldo->setText("");
        ui->leLuotto->setText("");
        ui->leLuottoRaja->setText("");
        qDebug() << "Pankkitili lisätty";
        ui->labelInfo->setText("Pankkitili lisätty");

        objPankkitilinYhdistaminenAsiakastiliin = new PankkitilinYhdistaminenAsiakastiliin;
        objPankkitilinYhdistaminenAsiakastiliin->show();
        objPankkitilinYhdistaminenAsiakastiliin->pankkitilinHaku();
        objPankkitilinYhdistaminenAsiakastiliin->asiakastilinHaku();

        ui->labelInfo->setText("Pankkitili yhdistetty asiakkaaseen");
    }
    else
    {
        ui->leSaldo->setText("");
        ui->leLuotto->setText("");
        qDebug() << "Pankkitilin lisääminen epäonnistui";
        ui->labelInfo->setText("Pankkitilin lisääminen epäonnistui");
    }
}


