#include "tunnuskysely.h"
#include "ui_tunnuskysely.h"

Tunnuskysely::Tunnuskysely(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tunnuskysely)
{
    ui->setupUi(this);
}

Tunnuskysely::~Tunnuskysely()
{
    delete ui;
}


void Tunnuskysely::on_pushButton_clicked()
{
    QJsonObject json;
    QString uname_users = ui->leKt->text();
    json.insert("username", uname_users);
    json.insert("password", ui->leSs->text());
    QString site_url = "http://localhost:3000/login_users";
    QString credentials = "root:root";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)),
            this, SLOT(loginSlot(QNetworkReply*)));
    reply = loginManager->post(request, QJsonDocument(json).toJson());
}

void Tunnuskysely::closeEvent(QCloseEvent *event)
{
    if(event)
    {
        emit close();
    }
}

void Tunnuskysely::loginSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    qDebug() << response_data;
    if(response_data == "true")
    {
        ui->leKt->setText("");
        ui->leSs->setText("");
        qDebug() << "Oikea tunnus";
        ui->labelTunnusInfo->setText("Oikea tunnus!");
        this->hide();
    }
    else
    {
        ui->leKt->setText("");
        ui->leSs->setText("");
        qDebug() << "Väärä tunnus nännännää";
        ui->labelTunnusInfo->setText("Väärä tunnus!");
    }
}
