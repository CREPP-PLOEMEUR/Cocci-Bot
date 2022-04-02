
void setup()   { 


//**INITIALISATION COMMUNICATION**
Serial.begin(115200); // initialise la connexion série a 115200 bauds


//**INITIALISATION BROCHES**
//Mise en sortie des broches 
for (int v=2;v<13;v++){
  pinMode(pins[v],OUTPUT);
} 
pinMode(13,INPUT);

//**INITIALISATION SERVOS**

   for (int i=0;i<6;i++){  
      objet[i] = new Servo();//creation des 6 objets servo
   }//fin for 

  for (int i=0;i<6;i++){
      objet[i]->attach(pinsServo[i], MinServo[i], MaxServo[i]); // attache les servomoteurs à leur broche 
   // et initialisation des positions extremes

servoTo(*objet[i],params[i+4],Memservos[i],toVitesse);
Memservos[i]=params[i+4];
}
//**INITIALISATION BRAS** 







}
