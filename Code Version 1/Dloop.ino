
void loop(){

  
  if (automatic==0){
ComSerie();

Moteurs();

Servos(); 
  }
  if (automatic==1){
ComSerie();    
ultrason();  
   
  }//fin if automatic
} // fin de la fonction loop() 

