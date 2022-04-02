//****MODULE MOTEURS **** //
//Il met en oeuvre les parametres recus par voie serie
//et stocke dans les quatre premieres valeurs du tableau "params"
//(details dans communication)

//ATTENTION :Pour le passage de parametres en manuel par le port serie,le module
//n'integre pas de gestion des erreurs de frappe.Le but final etant de passer les
// parametres de facon automatique ,notamment par le biais d'une interface python.

void Moteurs() { // Application des parametres moteurs
   
     static int pinSens[2]={4,7};//broches pour ecriture digitalWrite
     static int diff[2];//tableau incrementation progressive des vitesses pour chaque moteur
        
          if ((sens[0]!=params[2]) or (sens[1]!=params[3]) or (vitesse[0]!=params[0]) or (vitesse[1]!=params[1])) {
      // si une valeur moteur change (ou plusieurs)...
      
          for(int k=0;k<2;k++) {// pour les deux moteurs (a supprimer si un seul moteur.
                                // sinon k<nombre de moteurs
             if(sens[k]!=params[k+2]){//Si changement de sens

                analogWrite(pins[k+5],0);//vitesse[k]);//on applique la vitesse nulle 
                // a adapter selon la broche vitesse choisie
                sens[k]=params[k+2];//on memorise le nouveau sens
                digitalWrite(pinSens[k],sens[k]);// on applique le nouveau sens                         
             }//fin if
             
              if(params[k]==0){//en cas de vitesse passee nulle
               
                 analogWrite(pins[k+5],0);//on met la vitesse a 0 sans ralentissement progressif
                 // a adapter  :k + No de broche le plus faible si les broches moteur se suivent.
                 //Si les broches ne se suivent pas,creer un tableau avec leurs numeros 
                 // pour pouvoir les appeler.(cf pinSens)
                 vitesse[k]=params[k];                                      
               }//fin if 0
               
                diff[k] =(params[k] - vitesse[k])/10;// on cree 10 pas /pour chaque moteur
                              
           }//fin for k
             
               
           for (int i =0;i<10;i++) { //on applique 10 fois ce pas pour chaque moteur)
                for(int m=0;m<2;m++){// alterne l'acceleration sur chaque moteur           
                      if(diff[m]!=0){//pour un pas non nul
                      vitesse[m]=vitesse[m] + diff[m];//a chaque boucle on incremente la vitesse du pas
                      //alternativement sur chaque moteur                                       
                      if (vitesse[m]>255){vitesse[m]=255;}//verifie qu'on reste<255
                      if (vitesse[m]<0){vitesse[m]=0;}// verifie qu'on reste>0
                      analogWrite(pins[m+5],vitesse[m]);//application de la vitesse
                      delay(100);//pour progressivite de l'acceleration
                      
                      if(i==9){//en fin de boucle
                         vitesse[m]=params[m];//on memorise la nouvelle vitesse            
                      }//fin if memo vitesse
                  
                      }//fin if diff                      
                    }// fin for m                                                     
                 }//fin for i
          }// fin if "s'il y a un changement d'etat moteur
}// fin void moteurs






