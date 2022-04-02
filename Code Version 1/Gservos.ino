void Servos()
{

  for (int i=0;i<6;i++){
     if ((params[i+4]!= NULL)&& (params[i+4]!=Memservos[i])) { //si une valeur est passee et differente de la valeur actuelle
        servoTo(*objet[i], Memservos[i], params[i+4], toVitesse); //on execute la nouvelle position
        Memservos[i] = params[i+4];//on memorise la nouvelle position        
      }//fin if
  }// fin for
}// fin void Servos


void ServosFin(){
  for (int i=0;i<6;i++){
      servoTo(*objet[i], Memservos[i], 60, toVitesse);
//    
  }//fin for
}//fin void ServosFin



//... Fonction de positionnement progressif du servomoteur pas à pas fixe de n degrés...

 void servoTo(Servo toServo, int fromAngle, int toAngle, int toVitesse)  {
  
    int delta=toAngle-fromAngle;  // variation d'angle
    int deltaA=abs(delta);//valeur absolue de la variation
    int pas = delta/deltaA;//creation d'un pas de + ou - 1
   
    for (int i=0; i< deltaA;i++) {  // défile n positions pour atteindre l'angle final     
         fromAngle=fromAngle+pas;  // ajoute 1 cran
         toServo.write(fromAngle); // crée une impulsion   
         delay(toVitesse);//entre chaque positionnement    
    } // fin de for

} // fin de la fonction servoTo

