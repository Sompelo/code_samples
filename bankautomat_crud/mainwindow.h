#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QCloseEvent>
#include "tunnuskysely.h"
#include "nayta_asiakkaan_tiedot.h"
#include "nayta_tilin_tiedot.h"
#include "nayta_kortin_tiedot.h"
#include "lisaa_uusi_asiakas.h"
#include "lisaa_uusi_tili.h"
#include "lisaa_uusi_kortti.h"
#include "paivita_asiakkaan_tietoja.h"
#include "paivita_kortin_tietoja.h"
#include "paivita_tilin_tietoja.h"
#include "poista_asiakas.h"
#include "poista_kortti.h"
#include "poista_tili.h"
#include "tilitapahtumien_tulostus.h"
#include "poista_asiakas_pankkitili_yhteys.h"
#include "asiakas_pankkitili_yhteys.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getUname() const;
    void setUname(const QString &value);

private slots:
    void closeEvent();

    void on_actionLopeta_triggered();

//Lisää
    void on_actionAsiakas_triggered();
    void on_actionTili_triggered();
    void on_actionKortti_triggered();

//Päivitä
    void on_actionAsiakas_2_triggered();
    void on_actionTili_2_triggered();
    void on_actionKortti_2_triggered();

//Poista
    void on_actionAsiakas_3_triggered();
    void on_actionTili_3_triggered();
    void on_actionKortti_3_triggered();

//Näytä tiedot
    void on_actionAsiakas_4_triggered();
    void on_actionTili_4_triggered();
    void on_actionKortti_4_triggered();

    void on_actionTilitapahtumat_triggered();

    void on_actionYhteys_triggered();

    void on_actionAsiakas_pankkitili_triggered();

private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;
    Tunnuskysely *objTunnuskysely;

    Nayta_Asiakkaan_Tiedot *objAsiakkaanTiedot;
    nayta_tilin_tiedot *objTilinTiedot;
    Nayta_Kortin_Tiedot *objKortinTiedot;
    Asiakas_Pankkitili_Yhteys *objAsPtYhteys;

    Lisaa_Uusi_Asiakas *objLisaaAsiakas;
    Lisaa_Uusi_Tili *objLisaaTili;
    Lisaa_Uusi_Kortti *objLisaaKortti;

    Paivita_Asiakkaan_Tietoja *objPaivitaAsiakas;
    Paivita_Tilin_Tietoja *objPaivitaTili;
    Paivita_Kortin_Tietoja *objPaivitaKortti;

    Poista_Asiakas *objPoistaAsiakas;
    Poista_Tili *objPoistaTili;
    Poista_Kortti *objPoistaKortti;
    Poista_Asiakas_Pankkitili_Yhteys *objPoistaYhteys;

    Tilitapahtumien_Tulostus *objTilitapahtumat;

    QNetworkAccessManager *asiakasManager;
    QNetworkAccessManager *tiliManager;

    QString uname;
};

#endif // MAINWINDOW_H
