//Matopeli koodinäyte. Kevät 2021 - Samuli Salmi TVT21KMO
 
//Tämä koodi on minun osuuteni 4:n hengen ryhmämme projektityöstä "Matopeli", jossa kirjoitimme matopelin arduinolle.
//Näyttönä pelille käytimme 8x8 ledimatriisinäyttöä ja ohjaimena painonappeja koekytkentälevyllä (breadboard).
//Koodissa on funktiot ledimatriisin ajuripiirin eri toimintojen hallintaan, funktiot painonappien käyttöön, koodi pelilogiikalle, 
//pelaajan sijainnin ja madon hännän kasvun seurannalle ja ruuan synnyttämiselle. 
 
//Poistin ohjelmasta muiden ryhmäläisten osuudet, eli funktiot pelin aloitus- ja lopetusnäytöille, kirjaingrafiikoille ja valikkorakenteelle. 


/*-------------------HEI! TERVETULOA MATOPELIIN!--------------------------*
 *------------TÄSSÄ VIIMEISIN VERSIO MATOPELIN KOODISTA-------------------*
 *--------OLEN KOITTANUT KOMMENTOIDA MAHDOLLISIMMAN SELKEÄSTI-------------*
 *------MAHDOLLISIMMAN MONEEN KOHTAAN, ETTÄ OHJELMAN TOIMINTOJA-----------*
 *--------------------OLISI HELPPO TARKASTELLA----------------------------*
 *------------------------------------------------------------------------*
 *----Huomio! Kommenteissa käytetään vuorotellen vähän fiiliksen mukaan --*
 *----termejä "IC-piiri" tai "ledimatriisiajuri" tai "ajuripiiri".--------*
 *----Näillä tarkoitan samaa asiaa eli MAX7219 LED DRIVER-IC-piiriä - S---*/
 
 
#define DELAYTIME 10                                                      //Viive, jota käytetään varmistamaan hallintafunktioiden toimiminen. (en ole satavarma onko tarpeellinen. Tämä arvo on ollut tässä kurssin alusta alkaen. - Samuli)
#define VALKE 30

                                                                          

void normalOperation(bool);                                               //normalOperation()-Määrittää IC-piirille onko normal mode päällä (true) vai shutdown mode (false).
void scanRegister(byte);                                                  //scanRegister()----Funktio scan limit- rekisterin säätämiseen. Parametri määrää käytettävien ledirivien määrän. Vakiona 7.
void rekNollaus();                                                        //rekNollaus()------Asettaa kaikki komentorekisterit nollaan. Käytetään ohjelman alussa.
void nollaus();                                                           //nollaus()---------Nollaa näytön rekisterit.
void lahetys(int, int, bool);                                             //lahetys()---------Lähettää datan IC-piirille. Ensimmäinen int on rekisteri (4 bittiä) ja toinen on itse data (8 bittiä). Boolean päättää sytytetäänkö ledi vai sammutetaanko. 
void displayTest(bool);                                                   //Laittaa kaikki ledit päälle täydellä kirkkaudella. (Ärsyttävä ominaisuus, jos siihen törmää ohjelmointivirheen takia.) 
void kirkkaus(int);                                                       //Funktio, jolla säädetään ledien kirkkautta.
void spawnaaOmena();                                                      //Funktio madon ruuan spawnaamiseksi. 

bool gameOver = false;

int cs  = 11;                                                             //Pinni datan siirtoa varten siirtorekisteriin.
int clk = 10;                                                             //Kellopinni.
int din = 12;                                                             //data in- pinni.

int up = 2, down = 3, left = 4, right = 5;                                //Painonappien pinnit.

int suunta = right;                                                       //Tallentaa viimeisimmän napinpainalluksen.
int edellinenSuunta;                                                      //Muuttuja, joka tallentaa edellisen suunnan. Käytetään siihen, että matoa estetään kääntymästä 180 astetta ympäri.

struct karttaKoordinaatit {                                               //Rekisteriarvot, jotka määräävät sytytettävien ledien paikan.
  public:
    const int y[8] = {1, 2, 3, 4, 5, 6, 7, 8};                            //Käytettävän rivin valinta ledimatriisinäytöllä.
    const int x[8] = {1, 2, 4, 8, 16, 32, 64, 128};                       //Riville syötettävä data (mikä tai mitkä ledit ovat päällä/pois).
};
struct positio {                                                          //structi, jota käytetään madon ja omenan paikan ilmaisemiseen.
  public:
    int x;
    int y;
};
struct pelaaja {                                                          //structi, jota käytetään pelaajan nimen ja pisteiden tallentamiseen ja tulostamiseen.
  public:
    String nimi;
    int pisteet;
};

pelaaja pelaaja;                                                          //Struct objektien määrittelyjä.
positio mato;
positio omena;
karttaKoordinaatit kartta;

int hantaX[32], hantaY[32];                                               //Madon hännän sijainnit molemmilla akseleilla tallentavat taulukot.
int kasvuIndeksi = 0;                                                     //Indeksi kasvaa yhdellä aina madon syödessä ruokaa.
int laskuri = 0;                                                          //Laskuri, jota käytetään pelin frameraten säätöön ja pelin nopeuden säätöön.
int GAMESPEED;                                                            //Muuttuja jonka arvoa käytetään pelin vaikeuden vaihtamiseen.

void setup() {
  Serial.begin(9600);

  pinMode(clk, OUTPUT);                                                   //Matriisiajuripiirin pinnien määrittelyä.
  pinMode(cs, OUTPUT);
  pinMode(din, OUTPUT);

  pinMode(up, INPUT);                                                     //Pelin ohjauspainonappien pinnien määrittely.
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  
  rekNollaus();                                                           //Joka kerta ohjelmaa ajettaessa ensin asetetaan kaikki hallintarekisterit nolliin.
  nollaus();                                                              //Tämä aliohjelma asettaa näytön ledit nolliin.
  normalOperation(1);                                                     //Normal Op päättää käytetäänkö lediajuria 7-segmenttinäytön kanssa vai ledimatriisinäytön(tai useamman 7-segmentin) kanssa.
  scanRegister(7);                                                        //Päätetään, mitkä output-pinnit lediajurilta ovat käytössä, eli meidän tapauksessa määrää kuinka monta riviä matriisinäytöltä on käytössä.
  displayTest(false);                                                     //Display test-moodin valinta (joko päällä tai pois).
  kirkkaus(1);                                                            //kirkkauden säätö asteikolla 0 - 15.

  gameOver = false;                                                       //Pelin alun parametrejä, kuten että peli käynnistyy, 
  mato.x = 4;                                                             //madon aloituskoordinaatit, 
  mato.y = 4;
  omena.x = 0;                                                            //ensimmäisen omenan koordinaatit.
  omena.y = 0;

}
void loop()
{ 
  while (!gameOver)                                                       //Peli-looppi.
  {
    draw();                                                               //Päivittää näyttöä jatkuvasti.
    input();                                                              //Tarkistaa onko tullut uusia näppäinten painalluksia.
    spawnaaOmena();                                                       //Spawnaa ruoan, jos sitä ei ole ruudulla.
    if (laskuri == GAMESPEED)                                             //Luuppi, joka hidastaa pelilogiikan päivittymistä, jotta näyttöä saadaan päivitettyä useammin
    {                                                                     //per peli ticki. Vähentää ledien välkkymistä ja parantaa pelattavuutta.
      logic();                                                            //Pelin logiikan sisältävä aliohjelma. 
      laskuri = 0;                                                        //Asettaa laskurin alkuasentoon, kun pelilogiikka on suoritettu.
    }
    laskuri++;
    for(int i = 0; i < 9; i++)                                            //Luuppi tyhjentää näytön ohjelman joka kierroksella ennen kuin päivittää sen taas uusilla tiedoilla.
    {                                                                     
      for(int j = 0; j < 8; j++) lahetys(i, j, false);                    //samaa luuppia. 'i' valitsee tyhjennettävän rivin ja 'j' tyhjentää rivin kaikki paikat.
    }                                                                     //Jostain syystä piti laittaa 'i < 9' eikä 'i < 8', jotta luuppi tyhjentää kaikki rivit.
    //Serial.print(omena.x);
    //Serial.print(omena.y);
    //Serial.print("    ");
    //Serial.println(kasvuIndeksi);
  }
  lopetus();                                                              //Kun gameOver = true, rikkoutuu game-looppi ja ajetaan lopetus-aliohjelma.
}
void draw()                                                               //Ottaa madon osien ja omenan sijaintien koordinaatit ja piirtää ne ledimatriisinäytölle. 
{
  for (int i = 0; i < 9; i++)                                             //Sisäkkäin olevat for-loopit päivittävät kuvan näytölle rivi ja pystyrivi kerrallaan. 
  {
    for (int j = 0; j < 8; j++) 
    {
      if (i == mato.y && j == mato.x)                                     //Jos tarkasteltavalla ledillä on sama arvo kuin madon koordinaateilla, lähetetään näytölle 
      {                                                                   //käsky sytyttää ledi.
        lahetys(kartta.y[i], kartta.x[j], true);                          //Lähettää arduinolta ic-piirille käskyn sytyttää tietty ledi.
        delay(1.5*VALKE);                                                 //Viive vähentämään näytön välkkymistä.
      }
      else if (i == omena.y && j == omena.x)                              //Tässä tarkastellaan että onko omenan koordinaatit samat kuin missä luuppi menee.
      {
        lahetys(kartta.y[i], kartta.x[j], true);                          //Ja sitten piirretään omena näytölle jos se löytyy.
        delay(VALKE);                                                     //Vähän pienempi viive tässä, että omena ja madon pää erottuisivat toisistaan paremmin.
      }   
      else 
      {
        for (int k = 0; k < kasvuIndeksi; k++)                            //Tässä katsoo sitten, että onko madolle syytä lisätä häntäsegmenttejä.
        {
          if (hantaX[k] == j && hantaY[k] == i)
          {
            lahetys(kartta.y[hantaY[k]], kartta.x[hantaX[k]], true);
            delay(VALKE / kasvuIndeksi);                                  //Viive jaettuna kasvuindeksillä, jotta pelin nopeus ei olisi riippuvainen häntäsegmenttien määrästä.
          }
        }
      }
    }
  }
}


void input()                                                              //Funktio tutkii, onko painonappeja painettu ja määrittää näiden pohjalta suunnan madolle.
{
  int upVal = 0, downVal = 0, leftVal = 0, rightVal = 0;
  
  upVal     = digitalRead(up);
  downVal   = digitalRead(down);
  leftVal   = digitalRead(left);
  rightVal  = digitalRead(right);
  if         (upVal == HIGH && edellinenSuunta != down)                   //Esimerkkinä tässä määritetään suunta 'ylös', mutta vain jos edellinen suunta ei ole 'alas'päin.
  {
    suunta = up;
    edellinenSuunta = suunta;
  }
  else if  (downVal == HIGH && edellinenSuunta != up)
{
    suunta = down;
    edellinenSuunta = suunta;
  }
  else if  (leftVal == HIGH && edellinenSuunta != right)
{
    suunta = left;
    edellinenSuunta = suunta;
  }
  else if (rightVal == HIGH && edellinenSuunta != left)   
  {
    suunta = right;
    edellinenSuunta = suunta;
  }
}
void logic()                                                              //Logiikkafunktio. Sisältää pelin sisäisen logiikan. 
{
  int prevX = hantaX[0];                                                  //Tässä määritellään madon häntäsegmenttien aloitusarvoja ja tallennetaan madon sijainti taulukkoon.
  int prevY = hantaY[0];
  int prev2X, prev2Y;
  hantaX[0] = mato.x;
  hantaY[0] = mato.y;
  
  for(int i = 1; i < kasvuIndeksi; i++)                                   //For-luuppi siirtää madon edellisiä sijainteja taulukossa eteenpäin, jotta niiden pohjalta voidaan
  {                                                                       //piirtää madon häntäsegmentit.
    prev2X    = hantaX[i];        
    prev2Y    = hantaY[i];
    hantaX[i] = prevX;
    hantaY[i] = prevY;
    prevX     = prev2X;
    prevY     = prev2Y;
  }
  
  if(suunta == right) mato.x--;                                           //Tässä otetaan 'input()' funktion antama 'suunta'-arvo ja siirretään madon paikkaa sen mukaisesti.
  if(suunta == left)  mato.x++;
  if(suunta == up)    mato.y--;
  if(suunta == down)  mato.y++;

  if(mato.x < 0) mato.x = 7;                                              //Tässä on asetettu ledimatriisinäytön rajat niin, että jos mato menee rajan yli, ilmestyykin
  if(mato.x > 7) mato.x = 0;                                              //se näytön toiselle laidalle.
  if(mato.y < 0) mato.y = 7;
  if(mato.y > 7) mato.y = 0;

  for (int i = 0; i < kasvuIndeksi; i++)                                  //Tässä on pelin lopettava luuppi,  eli jos mato osuu häntäänsä, loppuu  peli.
  {
    if(hantaX[i] == mato.x && hantaY[i] == mato.y)
      gameOver = true;
  }

  if (mato.x == omena.x && mato.y == omena.y)                             //Tässä taas määrätään, että jos madon pää on omenan kohdalla, eli mato 'syö' omenan
  {                                                                       //synnytetään sattumanvaraisen seedin mukaan kartalle ja lisätään kasvuIndeksi- muuttujan arvoa yhdellä.
    spawnaaOmena();
    kasvuIndeksi++; 
  }
}

void spawnaaOmena()                                                       //Omenan synnyttämiseen funktio.
{
  for (int i = 0; i < kasvuIndeksi; i++) 
  {
    while(omena.x == mato.x && omena.y == mato.y || omena.x == hantaX[i] && omena.y == hantaY[i]) //Estää sen, että omenaa ei voi syntyä madon sisään.
    {
      omena.x = rand() % 7;
      omena.y = rand() % 7;
    }
  }
}

void rekNollaus()                                                          //Funktio, jolla alustetaan kaikki hallintarekisterit nollaan.
{
  int rekisteri = 0;
  
  for (int i = 0; i < 15; i++)                                             //Luuppi käy läpi kaikki rekistterit ja asettaa niiden arvoksi 0.
  {
    rekisteri++;
    delay(DELAYTIME);
    lahetys(rekisteri, 0, true);
  }
}

void scanRegister(byte m)                                                   //Funktio, jolla valitaan ledinäytön käytettävien rivien määrä (0-7). Me käytämme kaikkia,
{                                                                           //joten tämän arvo on vakiona 7.
  int r = 0b1011;
  lahetys(r, m, true); 
  delay(DELAYTIME);
}

void normalOperation(bool b)                                                //Funktio ShutDown moden ja normaalin toiminnan valitsemiseen.
{                                                                           //ShutDown moodissa kaikki ledit pimenevät, mutta niiden tilat jäävät muistiin
  if(b)                                                                     //jotta kun ShutDown moodin ottaa pois päältä palavat samat ledit samoilla paikoilla.
  {
    int r = 0b1100;
    int data = 1;                                                          
    lahetys(r, data, true);                                                      
    delay(DELAYTIME);                                                      
  }
  else
  {
    int r = 0b1100;
    int data = 0;
    lahetys(r, data, true);
    delay(DELAYTIME);
  }
}

void lahetys(int rekisteri, int data, bool on)                             //Funktio cs-pinnin avaamiselle ja tiedon lähettämiselle Arduinolta IC-piirille.
{
  digitalWrite(cs, LOW);                                                   //Valmistaudutaan lähettämään dataa säätämällä cs- pinni nollaan.
                                                                           
  (on == true) ? data = data : data = 0;                                   //Tässä määritellään ehto, että jos 'boolean on' on 'true', lähetetään data IC-piirille
  data |= (rekisteri << 8);                                                //muuten data korvataan nollalla. Eli tämä määrää onko haluttu ledi päällä vai pois päältä.
  int dataTaulukko[16];
  for (int i = 15; i > -1; i--)
  {                                                                        //For-looppi desimaaliluvun muuntamiseksi binääriksi.
    dataTaulukko[i] = (data >> i) & 1;                                     //Samalla tallentaa ne taulukkoon.
  }
  for (int i = 15; i > -1; i--)
  {
    digitalWrite(clk, LOW);                                                //Kello laitetaan ala-asentoon lähetystä varten.
    digitalWrite(din, dataTaulukko[i]);                                    //Lähettää yhden bitin kerrallaan per kellon lyömä IC-piirille.
    digitalWrite(clk, HIGH);                                               //Asetetaan kello ylätilaan jotta bitti tallentuu IC-piirille.
    //Serial.print(dataTaulukko[i]);                                       //Debuggausta varten
  }
  //Serial.println(" ");
  //delay(1);
  digitalWrite(cs, HIGH);                                                  //cs- pinni HIGH-tilassa latchaa datan siirtorekisteriin.
}


void nollaus()                                                             //Tyhjentää ledinäytön ruudun käymällä kaikki rivit läpi ja asettamalla niille arvon 0.
{
  for (int i = 0; i < 8; i++)
  {
    int rekisterit[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int x = rekisterit[i];
    lahetys(x, 0, true);
  }
}

void displayTest(bool b)                                                    //Kytkee Test moden päälle, eli laittaa kaikki ledit täysillä palamaan. (Jos matopelille on 
{                                                                           //asetettu y-akselin mukainen yläraja väärin syystä tai toisesta, tämä tuli helposti 
  if(b) lahetys(15, 1, true);                                               //vahingossa asetettua päälle ja sokaisi sitten pariksi sekunniksi koodaajan :D. Seuraavaa
                                                                            //matriisinäyttöprojektia varten hankittava mahdollisesti hitsauskypärä.)
  else lahetys(15, 0, true);
}

void kirkkaus(int data)                                                     //Tällä voidaan asettaa haluttu kirkkaus ledeille (0-15). Vakiona '1'.
{
  lahetys(10, data, true);
}