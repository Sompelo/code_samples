#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objTunnuskysely = new Tunnuskysely;

    connect(objTunnuskysely, SIGNAL(close()), this, SLOT(closeEvent()));
    objTunnuskysely->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
    delete objTunnuskysely;
    objTunnuskysely = nullptr;
}

void MainWindow::closeEvent()
{
    this->close();
}

void MainWindow::on_actionLopeta_triggered()
{
    this->close();
}

void MainWindow::on_actionAsiakas_triggered()
{
    objLisaaAsiakas = new Lisaa_Uusi_Asiakas;
    objLisaaAsiakas->show();
}

void MainWindow::on_actionTili_triggered()
{
    objLisaaTili = new Lisaa_Uusi_Tili;
    objLisaaTili->show();
}

void MainWindow::on_actionKortti_triggered()
{
    objLisaaKortti = new Lisaa_Uusi_Kortti;
    objLisaaKortti->show();
}

void MainWindow::on_actionAsiakas_2_triggered()
{
    objPaivitaAsiakas = new Paivita_Asiakkaan_Tietoja;
    objPaivitaAsiakas->show();
}

void MainWindow::on_actionTili_2_triggered()
{
    objPaivitaTili = new Paivita_Tilin_Tietoja;
    objPaivitaTili->show();
}

void MainWindow::on_actionKortti_2_triggered()
{
    objPaivitaKortti = new Paivita_Kortin_Tietoja;
    objPaivitaKortti->show();
}

void MainWindow::on_actionAsiakas_3_triggered()
{
    objPoistaAsiakas = new Poista_Asiakas;
    objPoistaAsiakas->show();
}

void MainWindow::on_actionTili_3_triggered()
{
    objPoistaTili = new Poista_Tili;
    objPoistaTili->show();

}

void MainWindow::on_actionKortti_3_triggered()
{
    objPoistaKortti = new Poista_Kortti;
    objPoistaKortti->show();

}

QString MainWindow::getUname() const
{
    return uname;
}

void MainWindow::setUname(const QString &value)
{
    uname = value;
}

void MainWindow::on_actionAsiakas_4_triggered()
{
    objAsiakkaanTiedot = new Nayta_Asiakkaan_Tiedot;
    objAsiakkaanTiedot->show();
}

void MainWindow::on_actionTili_4_triggered()
{
    objTilinTiedot = new nayta_tilin_tiedot;
    objTilinTiedot->show();
}

void MainWindow::on_actionKortti_4_triggered()
{
    objKortinTiedot = new Nayta_Kortin_Tiedot;
    objKortinTiedot->show();
}

void MainWindow::on_actionTilitapahtumat_triggered()
{
    objTilitapahtumat = new Tilitapahtumien_Tulostus;
    objTilitapahtumat->show();
}

void MainWindow::on_actionYhteys_triggered()
{
    objPoistaYhteys = new Poista_Asiakas_Pankkitili_Yhteys;
    objPoistaYhteys->show();
}

void MainWindow::on_actionAsiakas_pankkitili_triggered()
{
    objAsPtYhteys = new Asiakas_Pankkitili_Yhteys;
    objAsPtYhteys->show();
}
