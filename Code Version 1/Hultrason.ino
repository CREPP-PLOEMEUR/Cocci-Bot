/*CAPTEUR DE DISTANCE ULTRASONIQUE

//***-Principe de fonctionnement-***

on emet une onde ultrasonique.Sur la broche de retour,
on detecte un etat haut dont la duree en microsecondes est
proportionnelle a la distance parcourue
cette distance represente un aller retour de l'onde.
on doit donc diviser par 2 pour avoir le temps jusqu'a l'obstacle.
La vitesse de propagation du son varie avec la temperature
A 20 degres au niveau de la mer elle est de 343,6 m/s
(10 deg:337,5; 15 deg:340,5 ;25 deg :346,3)
En 1 microseconde,la distance parcourue est de 0,03436 cm
Pour 1 cm :1/0.03436 = 29,1 microseconde
C'est le ratio que l'on utilisera dans le programme
pour determiner la distance a l'obstacle

les float etant traites plus lentement,on fera les calculs 
avec des entiers:
au lieu de calculer duree/2/29,1
on fera duree*5/291 qui represente le meme calcul
*/ 
void ultrason(){
 static int moteurs;//valeur moteurs en fonction de la distance
     ComSerie();
     mesure();


    if ((distance>150)&& (distance <400)) {
      params[0]=255;
      params[1]=255;
      Moteurs();
    }
    
    if ((distance<150)&& (distance >30)) {
      moteurs = map(distance,30,150,65,255);
      Serial.println(moteurs);
      params[0]= moteurs;
      params[1] = moteurs;
      Moteurs();
    }
    if (distance<30) {
      
      while (distance<50){
      ComSerie();
      if (automatic==0){
       break;   
      }
      chercheIssue();   
    
      params[2]=1-params[2];
      params[0]=100;
      Moteurs;
      delay(500);
      params[0]=65;
      Moteurs();

      chercheIssue(); 
    }
    } 
if (distance >= 400 || distance <= 0){
Serial.println("Hors plage");
}
else{

//Serial.println (distance);

}
delay(200);//delai entre deux mesures

}//fin void ultrason


void chercheIssue(){
  for(int i=0;i<5;i++){
    ComSerie();
    if(automatic==0){
      break;
    }
      params[0]=100;
      params[1]=0;
      Moteurs();
      delay(100);
      params[0]=65;
      Moteurs();
      mesure(); 
    
  }//fin for
}//fin chercheIssue

void mesure(){

long duree=0;
int rapport =291;//ratio duree-distance

// Envoi de l'onde
digitalWrite(pins[12], LOW);//broche emettrice a l'etat bas
delayMicroseconds(2);// delai
digitalWrite(pins[12], HIGH);//broche emettrice a l'etat haut
delayMicroseconds(10);//duree de l'impulsion
digitalWrite(pins[12], LOW);//remise a l'etat bas

duree = pulseIn(pins[13], HIGH);//reception echo
//distance = (duree*5)/rapport;
distance = (duree*5)/rapport;//calcul de la distance a l'obstacle
Serial.println(distance);
Serial.println("cm");
}//fin void mesure
