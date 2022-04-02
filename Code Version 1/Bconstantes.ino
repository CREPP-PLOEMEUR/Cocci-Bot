//**CONSTANTES GENERALES**
const int pins[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//tableau pins {0,1,camHB,camRot,sensG,vitesseG,vitesseD,sensD,....}
int automatic=0;//mode automatique =1, controle externe =0
int memauto =0;
//**CONSTANTES COMMUNICATION **


int params[10] = {0,0,0,0,60,60,60,60,60,60};//tableau des parametres sous la forme :
//[vitMotG,vitMotD,sensMotG,sensMotD,ht/basCam,rotationCam,RotationBras,Av/ArBras,
//ElevationBras,PinceBras]



//**CONSTANTES MOTEURS**

int sens[2];//tableau sens gauche/sens droit
int vitesse[2];// tableau vitesse gauche/vitesse droite

//**CONSTANTES SERVOS**

Servo *objet[6];//declaration tableau de pointeurs pour 6 objets servo
int Memservos[6]={60,60,60,60,60,60}; //Tableau pour memorisation des angles des servos
int toVitesse=50;//vitesse de positionnement des servos
const int MinServo[6] = {550,550,550,550,550,550};//tableau des largeurs d'impulsion min des servos
const int MaxServo[6] = {2250,2250,2250,2250,2250,2250};//Tabl. largeurs d'impulsion max des servos
const int pinsServo[6] = {2,3,8,9,10,11};  

//CONSTANTES DETECTION
long distance=0;//distance à un obstacle en cm


// Declaration constantes diverses







