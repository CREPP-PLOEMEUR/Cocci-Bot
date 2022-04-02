#include <Servo.h>
//#include <Utils.h>
//Utils utils;

// Auteurs du Programme : Groupe robotique avancee-CREPP
//- Tous droits réservés //  2017/2018

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License,
//  or any later version.
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.


//Ce programme est developpe pour le controle du Raspibot
//construit dans le cadre du groupe robotique avancee du CREPP

//Nous avons pris le parti de le concevoir sous forme de modules
//Ceci permet à chaque membre de construire son propre module
//Ces modules seront facilement integrables et interchangeables 
//Dans le cadre de ce projet et eventuellement pour d'autres utilisations.

//En ce qui concerne le raspibot,cette conception impose un certain nombre
//de conventions partagees par les participants au projet
//pour faciliter l'interoperabilite
//voici ces conventions à respecter pour la creation de module :

//CONVENTION MOTEURS:
//Pour le reperage des moteurs gauche (1) et droit (2),on se place 
//"en position de conducteur",l'arriere du robot etant au plus proche de soi.

//CONVENTION DE ROTATION :
//Pour les MOTEURS : "0" represente la marche avant, "1" la marche arriere
//dans les commandes du code

//Pour les SERVOMOTEURS :arbre devant soi,en haut du servomoteur :
//valeur minimale (millisecondes ou degres) : rotation en bout de course vers la gauche.
//valeur maximale (millisecondes ou degres) : rotation en bout de course vers la droite


//CONVENTION DE BROCHAGE ARDUINO:
//Broche  Fonction
//  0     Reserve televersement/communication
//  1     Reserve televersement/communication
//  2     Servomoteur haut/bas camera
//  3     Servomoteur rotation camera
//  4     Moteur "M1" (sens moteur)
//  5     Moteur "E1" (PWM)
//  6     Moteur "E2" (PWM)
//  7     Moteur "M2" (sens moteur)
//  8     Bras servo base(rotation)
//  9     Bras servo Avant/Arriere
//  10    Bras servo Elevation
//  11    Bras servo pince
//  12    ultrason emetteur (trigger)
//  13    Ultrason reception (echo)
//  A0
//  A1
//  A2
//  A3
//  A4
//  A5


// les particularites de mise en oeuvre et fonctionnement
//des modules seront à decrire en commentaires
//au debut dudit module.









    
                  
