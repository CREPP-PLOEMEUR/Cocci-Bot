#include <UART.h>
#include <HBRIDGE.h>
#include <LED.h>

#include <Servo.h>

#define SENS_1 0
#define SENS_2 1

const byte enable_moteur_droite = 5; //Broche PWM
const byte enable_moteur_gauche = 6; //Broche PWM
const byte sens_moteur_droite = 7; 	
const byte sens_moteur_gauche = 8;

const byte SHARP = A0;
const byte PONT_DIVISEUR = A1;

int RX_HC = 12;//12
int TX_HC = 10;//10

int position_servo_180 = 90;
int position_servo_120 = 90;

int distance = 0;
int nb_lecture_sharp = 10;


UART hc_05(RX_HC,TX_HC);
HBRIDGE robot(enable_moteur_gauche, sens_moteur_gauche, enable_moteur_droite, sens_moteur_droite);
LED led_verte(9);
LED led_jaune(11);
LED led_defaut(13);

Servo servo_rpi_180;
Servo servo_rpi_120;
//String message_pi;
String message_hc;

byte puissance_moteur = 100;

void setup() {

//robot.debug();
//Serial.begin(9600);
hc_05.begin(9600);
led_defaut.on();
led_verte.on(1000);
led_jaune.on();
servo_rpi_180.attach(3);
servo_rpi_120.attach(4);


servo_180(position_servo_120,90,40);
servo_120(position_servo_120,90,40);
}

void loop() {
  
message_hc = hc_05.read(LOCKED);
//message_pi = rpi.read();

 
if(message_hc!="") { 
   //Serial.println(message_hc);
   led_jaune.off();
   if(message_hc=="a")      {robot.motor_on(SENS_1,puissance_moteur, SENS_1, puissance_moteur);}
   else if(message_hc=="r") {robot.motor_on(SENS_2,puissance_moteur, SENS_2, puissance_moteur);
                             led_jaune.on();}
   else if(message_hc=="d") {robot.motor_on(SENS_1,puissance_moteur, SENS_2, puissance_moteur);}
   else if(message_hc=="g") {robot.motor_on(SENS_2,puissance_moteur, SENS_1, puissance_moteur);}
   else if(message_hc=="s") {robot.motor_off(0,0);}
   else if(message_hc=="1") {puissance_moteur=25;}
   else if(message_hc=="2") {puissance_moteur=50;}
   else if(message_hc=="3") {puissance_moteur=75;}
   else if(message_hc=="4") {puissance_moteur=100;}
   else if(message_hc=="5") {puissance_moteur=125;}
   else if(message_hc=="6") {puissance_moteur=150;}
   else if(message_hc=="7") {puissance_moteur=175;}
   else if(message_hc=="8") {puissance_moteur=200;}
   else if(message_hc=="9") {puissance_moteur=225;}
   else if(message_hc=="10"){puissance_moteur=255;}
   
   else if(message_hc=="11")  {servo_180(position_servo_180,20,40);}//servo_180(position_servo_180,20,40);
   else if(message_hc=="12")  {servo_180(position_servo_180,45,40);}
   else if(message_hc=="13")  {servo_180(position_servo_180,90,40);}
   else if(message_hc=="14")  {servo_180(position_servo_180,135,40);;}
   else if(message_hc=="15")  {servo_180(position_servo_180,160,40);}

   else if(message_hc=="20")  {servo_120(position_servo_120,30,40);}
   else if(message_hc=="21")  {servo_120(position_servo_120,60,40);}
   else if(message_hc=="22")  {servo_120(position_servo_120,90,40);}
   else if(message_hc=="23")  {servo_120(position_servo_120,120,40);}
   else if(message_hc=="24")  {servo_120(position_servo_120,140,40);}
   
   else if(message_hc=="c") {led_verte.blink(200,100,8);
                             //rpi.send("connect");
                             led_verte.on();}
   //else if(message_hc=="camera") {rpi.send("camera");}
 
}//fin if 


}//fin loop
//                    90                10
void servo_180(int pos_origine, int pos_expected, int delai_pas) {

   int delta = pos_expected - pos_origine;  //10-90 = -80
   int delta_abs = abs(delta);//80
   int pas = delta/delta_abs;//-1

   for (int i=0; i< delta_abs;i++) {  // défile n positions pour atteindre l'angle final     
         pos_origine=pos_origine+pas;  // ajoute 1 cran
         servo_rpi_180.write(pos_origine); // crée une impulsion   
    
         delay(delai_pas);//entre chaque positionnement    
    } // fin de for
    position_servo_180 = pos_origine;

}

void servo_120(int pos_origine, int pos_expected, int delai_pas) {

   int delta = pos_expected - pos_origine;
   int delta_abs = abs(delta);
   int pas = delta/delta_abs;

   for (int i=0; i< delta_abs;i++) {  // défile n positions pour atteindre l'angle final     
         pos_origine=pos_origine+pas;  // ajoute 1 cran
         servo_rpi_120.write(pos_origine); // crée une impulsion   
         
         delay(delai_pas);//entre chaque positionnement    
    } // fin de for
    position_servo_120 = pos_origine;
}




  
                          
 

  

