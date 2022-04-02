// ---Programme pour le controle du Coccibot en Bluetooth - 

//---Déclaration des librairies utilisées---
#include <LiquidCrystal.h>  // Inclusion de la librairie LCD
#include <SimpleCDbot.h>    // Librairie avec fonctions de controle d'un robot à 2 servos RC
#include <Utils.h>          // Librairie personnelle avec plusieurs fonctions utiles
#include <Servo.h>          // Inclut la librairie servo
#include <SoftwareSerial.h>	// Inclut la librairie pour communiquer avec le module Bluetooth

//--- Déclaration constantes BUZZER---
const int BUZZER=11;        // constante pour la broche du BUZZER

//---Déclaration des sonstantes LEDS---
const int ledR=14;          // constante pour la broche de la led rouge
const int ledV=15;          // constante pour la broche de la led verte

// ---Déclaration constantes Pont diviseur batterie---
const int Pntdivbat=A5;
int Niveau = 0; // valeur niveau de charge
int Pourcentage=0;
//---Déclaration des constantes Photoresistances---
//const int PhotoresD=A1;     // constante pour la broche de la Photoresistance droite
//const int PhotoresG=A0;     // constante pour la broche de la Photoresistance gauche

//---Déclaration constantes broches LCD---
const int RS=2;               // constante pour la broche RS
const int E=3;                // constante pour la broche E
const int D4=4;               // constante pour la broche D4
const int D5=5;               // constante pour la broche D5
const int D6=6;               // constante pour la broche D6
const int D7=7;               // constante pour la broche D7
LiquidCrystal lcd (RS,E,D4,D5,D6,D7);  //  déclaration d'un objet lcd

//---Déclaration des constantes Servomoteurs---
const int Droit=0;               // identification du servo droit
const int Gauche=1;              // identification du servo gauche
const int neutre={1470};         // largeur impulsion arret
const int maxAV[2]={970,1970};   // largeur impulsion vitesse max en avant
const int maxAR[2]={1970,970};   // largeur impulsion vitesse max en arrière
const int brocheServo[2]={8,9};  // broches des servomoteurs

//---Déclaration constantes Capteur de distance GP2D12---
const int GP2D12=A2;             // déclaration broche analogique du GP2D12

//---Déclaration des variables globales---
int mesure_brute=0;              // variable pour acquisition résultat brut de conversion analogique-numérique
float mesuref=0.0;               // variable pour calcul résultat décimal de conversion analogique-numérique
int distance;                    // distance de référence

//---Déclaration des broches du module Bluetooth
const int TX = 12;
const int RX = 10;
char c;
String message;


Servo servo[2];                  // déclaration d'un objet servomoteur
Utils utils;
SimpleCDbot robot(brocheServo[Droit],maxAR[Droit],maxAV[Droit],brocheServo[Gauche],maxAR[Gauche],maxAV[Gauche],neutre);
SoftwareSerial bluetooth(TX, RX); //déclaration d'un objet SoftwareSerial

             
boolean etatMoteurs=false;       // témoin etatMoteurs
boolean detectObstacle=false;    // temoin detectObstacle

//---FONCTION SETUP---
void setup() {                    // executee au debut et en une seule fois

  //Leds
  pinMode(ledR,OUTPUT);
  pinMode(ledV,OUTPUT);
  Serial.begin(115200);           // initialise la vitesse de la connexion série - la meme que dans le Terminal série
  
  
  bluetooth.begin(115200);//vitesse de transmission du module -- PEUT VARIER D'UN MODULE À L'AUTRE (en cas de pb, essayez 9600) !!!!
  //...Gestion batterie...
  pinMode(Pntdivbat,INPUT);// met la broche en entree
    TestBatterie();//Appel de la fonction
      
  // ...Initialisation du LCD...
  lcd.begin(16,2);              // initialise LCD colonnes x lignes
  lcd.clear();                  // efface LCD + se place en 0,0
  
  
} // Fin de la fonction setup()

//---FONCTION LOOP---

void loop() {                     // exécutée en boucle sans fin

while(bluetooth.available()>0) { //vérifie que des données sont disponibles
   c = bluetooth.read();         //lit caractère par caractère
   message = message + c;        //"additionne" les caractères pour former une chaîne (concaténation)
   //Serial.println(message);
 }                               //fin while

 //vérification des messages reçus
  if(etatMoteurs==true) {digitalWrite(ledV, HIGH); //allume la led verte si le robot avance
                        digitalWrite(ledR, LOW);}

   if(etatMoteurs==false) {digitalWrite(ledV, LOW);//allume la led rouge si le robot recule
                        digitalWrite(ledR, HIGH);}                      
                    
  if(message=="c")      {message=""; //obligation de "vider" la chaine de caractère pour que le module puisse recevoir d'autre données
                         Melodie(1);}
                                
  else if(message=="a")   {message="";              //demande à ce que le robot avance
                           robot.enAvant(100);
                           etatMoteurs=true;}
                                
  else if(message=="r")   {message="";              //demande à ce que le robot recule
                           robot.enArriere(100);
                           etatMoteurs=false;}  
                                                      
  else if(message=="d")    {message="";             //demande à ce que le robot tourne à droite
                            robot.tourneDroite(-100);
                            etatMoteurs=true;}
                                
  else if(message=="g")    {message="";             //demande à ce que le robot tourne à gauche
                            robot.tourneGauche(-100);
                            etatMoteurs=true;} 
                                
  else if(message=="s")      {message="";           //demande à ce que le robot s'arrête
                              robot.arret();
                              digitalWrite(ledV, LOW);
                              digitalWrite(ledR, LOW);}
                                
  else if(message=="b")  {message="";               //demande à ce que le robot affiche la batterie
                          TestBatterie();}          //regarde la tension de la pile
                                                           
  else if(message=="A")  {gestion_mouvement();}   //on laisse volontairement message à "A"
  
  /* Si dans votre application, vous avez rajouté un bouton, il suffit d'integrer dans ce 
   * programme un "else if(message=="ce que l'appli renvoie") {faire l'action désirée;}
   */
 
 
} // Fin de la fonction loop()

//=-=-=-=-=-=AUTRES FONCTIONS=-=-=-=-=-=-=

// ---Fonction moyenne des mesure---

float moyenneMesure(int nombreMesure, int voie) {
  
  int mesure=0;
  long cumul=0;
  float moyenne=0;
  
  for (int i=0; i<nombreMesure; i++) {
    mesure=analogRead(voie);
    cumul=cumul+mesure;
  
  } // Fin for
  
  moyenne=cumul/nombreMesure;
  cumul=0;                     // RAZ cumul
  return moyenne;
  
} // Fin de la fonction moyenne

//---Fonction melodie Buzzer---

void Melodie(int j) {
  
  //...variables fréquences des notes ...
  int DO=262;    // variable de la fréquence note
  int RE=294;    // variable de la fréquence note
  int MI=330;    // variable de la fréquence note
  int FA=349;    // variable de la fréquence note
  int SOL=392;   // variable de la fréquence note
  int LA=440;    // variable de la fréquence note
  int SI=494;    // variable de la fréquence note
  
  int melodies[4][4]={{DO,FA,DO,FA},{SI,DO,DO,FA},{RE,DO,MI,FA},{LA,DO,RE,FA}};  // notes des 4 mélodies
  int dureeNotes[4][4]={{1,1,2,2},{1,2,1,2},{1,2,2,1},{2,1,1,2}};                // durée des notes des 4 mélodies
  pinMode(BUZZER,OUTPUT);//met la broche buzzer en sortie
  
    for (int i=0; i<4; i++) {        // joue la note de rang i
      tone(BUZZER, melodies[j-1][i]);  // lance le son
      delay(250*dureeNotes[j-1][i]);   // duree de la note
      
      noTone(BUZZER);                  // stoppe le son
      delay(1000);
      
    } // fin de for
   
}// Fin de la fonction Melodie
      
      
  // Fonction Test Batterie
  void TestBatterie(){
Niveau=analogRead(Pntdivbat);
  if (Niveau>960) {
     Niveau=960;
     
  } // Fin de if Niveau>960
  
  if (Niveau<750) {
     Niveau=750;
     
  } // Fin de if Niveau>750
  
  if (Niveau>855) {
    digitalWrite(ledV,HIGH);              // allume la led verte si charge batterie > Ã  50%
  
  Pourcentage=(Niveau-750)*10/21;
  lcd.setCursor(0,0);
  lcd.print("CHARGE BATTERIE");
  lcd.setCursor(0,1);
  lcd.print(Pourcentage);
  
  lcd.setCursor(5,1);
  lcd.print("POUR CENT");
  delay(4000);
  lcd.clear();
  
  } // Fin if (Niveau>855)
  
} // Fin de void TestBatterie()


 void gestion_mouvement() {

  
  while(message=="A") {//execute cette fonction jusqu'a ce qu'on appuie sur une touche. Si une touche est actionnée, le robot 
                          //passe en mode manuel (avec l'application)

  robot.enAvant(100);
    
    distance = moyenneMesure(30, A2);
    fin_automatique(); 
    if(distance>500) {

      robot.tourneGauche(100);
      delay(1500);
      distance = moyenneMesure(30, A2);
      fin_automatique(); 
      if(distance>500) {

        robot.tourneDroite(100);
        delay(3000);

        distance = moyenneMesure(30, A2);
        fin_automatique(); 
        if(distance>500) {

            robot.tourneGauche(100);
            delay(1500);
        }
        else{robot.enAvant(100);}

      }                
      else  {robot.enAvant(100);}   

    }
     else {robot.enAvant(100);}  

 }//fin while
 }//fin gestion mouvement

void fin_automatique() {//permet de stopper le robot avec un appui sur une touche lorsqu'il est en mode automatique

if(bluetooth.available()>0) {//vérifie que des données sont présentes
  robot.arret();
  message="";
  etatMoteurs=false;

}//fin if

}//fin fin_automatique
