//MODULE COMMUNICATION PORT SERIE
// ce module permet de transmettre une rafale de parametres à Arduino sous forme d'un tableau
//Actuellement,10 parametres peuvent etre transmis.Si on ne tape que 4 parametres,ils correspondront 
//aux parametres moteurs

//valeurs des parametres transmis:

//param 0:vitesse PWM moteur gauche (min :0 max:255 )
//param 1:vitesse PWM moteur droit  (min :0 max:255 )
//param 2:sens moteur gauche.        0 en avant 1 en arriere
//param 3:sens moteur droit .        0 en avant 1 en arriere
//param 4:rotation camera.           angle min 0 ;angle max: 120?
//param 5:Elevation camera           angle min 0 ; angle max:120?
//param 6:Rotation bras              angle min 0 ; angle max:120?
//param 7:Elevation Bras             angle min 0 ; angle max:120?
//param 8:Avant/arriere Bras         angle min 0 ; angle max:120?
//param 9:Pince Bras                 angle min 0 ; angle max:120?

void ComSerie() {
        static int c =0;//compteur de parametres recus
        int caractere;// caractere unitaire recu sur le port serie
        int stock=1;//detection des virgules(2 a suivre ou pas)       
        int nombreReception = NULL;//nombre (parametre) en reception
  
  while ((Serial.available() > 0)) {   //tant qu'on recoit quelque chose...
        
        caractere = Serial.read();//...on le lit
                
           if (caractere == 10){// si c'est un saut de ligne(fin de sequence)
             
               params[c]=nombreReception;// le nombre precedemment stocké est le dernier du tableau
               nombreReception = NULL;// remise a zero des nombres recus   
               c = 0;   // remise a zero du compteur de parametres recus    
               break;// sortie de la boucle
           } // fin ifpour saut de ligne

       
          if (caractere == 44){// si c'est une virgule....
              
             if (stock==0){//si le caractere precedent n'etait pas une virgule
                params[c]= nombreReception;//on affecte la valeur precedente recue au tableau
                nombreReception = NULL;// on remet a zero la variable nombre recu
                stock=1;//on memorise le fait d'avoir recu une virgule
             }//fin if stock
                c++;// on passe a l indice parametre suivant                            
           }// fin if virgule      
          
          if (caractere == 102){
            ServosFin();
          }

          if ((caractere == 65) or (caractere == 97)){
            memauto = automatic;
            automatic =1;
            
          }

          if ((caractere == 77) or (caractere == 109)){
            if (memauto != automatic)
            params[0]=0;
            params[1]=0,
            Moteurs();
            automatic =0;
            memauto=0;
          }
          
          if ((caractere>47) & (caractere<58)){// si on recoit un chiffre...
            
              stock=0;//on memorise que l'on ne recoit pas une virgule
              caractere = caractere-48;//on transforme le chiffre ASCII en decimal
              nombreReception = (nombreReception*10)+caractere;// formule de reconstitution du nombre transmis
       
              delay(1);//laisse le temps au caractere suivant d'arriver
          }// fin if caractere

     
    }// fin while
  }//fin void comSerie
  
  
