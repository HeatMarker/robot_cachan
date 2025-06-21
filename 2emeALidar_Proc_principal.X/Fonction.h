#ifndef Fonction_H
#define	Fonction_H

#include <xc.h>  

#define PI                      3.14159265359f
#define DIAMETRE_ROUE_MM        32.43f
#define ENCODEUR_TICKS_PAR_TOUR 180
#define ENTRAXE_ROUES_MM        107.9f
#define COEF_CORRECTION_GAUCHE  1.007f
#define COEF_CORRECTION_DROITE  1.007f

typedef enum {
    MOTEUR_ARRIERE_TURBO  = -75,
    MOTEUR_ARRIERE_RAPIDE = -50,
    MOTEUR_ARRIERE_MOYEN  = -25,
    MOTEUR_ARRIERE_LENT   = -10,
    MOTEUR_ARRET          = 0,
    MOTEUR_LENT           = 10,
    MOTEUR_MOYEN          = 25,
    MOTEUR_RAPIDE         = 50,
    MOTEUR_TURBO          = 75
} VitesseMoteur_t;

typedef struct {
    long        ticks_gauche;
    long        ticks_droite;
    float       distance_gauche_mm;
    float       distance_droite_mm;
    signed long distance_gauche_int;
    signed long distance_droite_int;
    float       angle_rad;
    float       angle_deg;
    float       angle_abs;
} Odometrie_t;

extern unsigned long pres, past;
extern signed char MOTEUR_SPEED, etat;
extern Odometrie_t odo;

//Odometrie
void LCD_afficher_odometrie(void);
void calcul_distance_roues(void);
void calcul_angle_robot(float dist_gauche, float dist_droite);
void mise_a_jour_odometrie(void);



//Gestion du temps
unsigned long Get_Millis (void);                                                //incrémente de 1 à chaque milliseconde écoulée
void          Set_Millis (unsigned long t);                                     //donne une nouvelle valeur au compteur de millisecondes

//Gestion du BP et encodeur rotatif
unsigned short Enc_Get_Value (void);                                            //renvoie la valeur du compteur associé à l'encodeur rotatif
void           Enc_Set_Value (unsigned short val);                              //donne une nouvelle valeur au codeur associé à l'encodeur rotatif
unsigned char  BP_Get_Status (void);                                            //renvoie le status du bouton poussoir
unsigned char  BP_Get_Rising_Edge  (void);                                      //renvoie 1 si front descendant, sinon 0
unsigned char  BP_Get_Falling_Edge (void);                                      //renvoie 1 si front montant, sinon 0

//Gestion des moteurs
void Motors_Enable(unsigned char enable);                                       //enable/disable les moteurs
void Motors_Speed(signed char vitg, signed char vitd);                          //assigner vitesse aux moteurs, positif en marche avant, négatif en marche arrière
void Motors_Turn_Angle (signed short angle);                                    //tourne sur place de la valeur de angle, bloquant dans le main pour la durée de la manoeuvre

//Odometrie
signed long Motors_Get_Enc_Left (void);                                         //renvoie le compteur de coups d'encodeurs du moteur gauche, incrémente en marche avant, décrémente en marche arrière, 180 coups/tour
signed long Motors_Get_Enc_Right (void);                                        //renvoie le compteur de coups d'encodeurs du moteur droit, incrémente en marche avant, décrémente en marche arrière, 180 coups/tour
void        Motors_Set_Enc_Left (signed long cpt);                              //donne une nouvelle valeur au compteur de coups d'encodeurs du moteur gauche
void        Motors_Set_Enc_Right (signed long cpt);                             //donne une nouvelle valeur au compteur de coups d'encodeurs du moteur droit

//Gestion de la boussole
unsigned short Compass_Get_Angle_Magn(void);                                    //renvoie l'angle magnétique donné par la boussole

//Gestion du haut-parleur
void NOTE (unsigned char note, signed char alteration, unsigned char octave, unsigned short duree); //Jouer une note entre C2 et C6, durée en ms, bloquant dans le main pour la durée de la note. Exemple : NOTE('D',1,4,230); --> Ré# octave 4 pendant 230ms
void NOTE_Start (unsigned char note, signed char alteration, unsigned char octave);                 //Jouer une note, l'arrêt se fait avec la fonction NOTE_Stop()
void NOTE_Stop (void);                                                                              //Arrête la note en cours

//Gestion des entrées analogiques
unsigned char ADC_Get_CNYG (void);                                              //renvoie la valeur du capteur optique de gauche
unsigned char ADC_Get_CNYD (void);                                              //renvoie la valeur du capteur optique de droite
unsigned char ADC_Get_BATT (void);                                              //renvoie la tension batterie, 255=5V

//Gestion de l'écran LCD
extern void LCD_Goto(char ligne, char colonne);                                 //pour placer le curseur
void        LCD_Retro (unsigned char retro);                                    //allumer ou éteindre le retro éclairage du LCD
extern void LCD_Clear(void);                                                    //efface l'écran
extern void LCD_Print(char *t);                                                 //affiche une chaine de caractères
void        LCD_Write_u8bits(unsigned char var, unsigned char digit);           //écrire un 8 bits non signé avec combien de digits, curseur placé sur le digit le plus à gauche
void        LCD_Write_s8bits(signed char var, unsigned char digit);             //écrire un 8 bits signé avec combien de digits, curseur placé sur le digit le plus à gauche
void        LCD_Write_u16bits(unsigned short var, unsigned char digit);         //écrire un 16 bits non signé avec combien de digits, curseur placé sur le digit le plus à gauche
void        LCD_Write_s16bits(signed short var, unsigned char digit);           //écrire un 16 bits signé avec combien de digits, curseur placé sur le digit le plus à gauche
void        LCD_Write_u32bits(unsigned long var, unsigned char digit);          //écrire un 32 bits non signé avec combien de digits, curseur placé sur le digit le plus à gauche
void        LCD_Write_s32bits(signed long var, unsigned char digit);            //écrire un 32 bits signé avec combien de digits, curseur placé sur le digit le plus à gauche

//Gestion du lidar
void           LIDAR_Set_Search_Angle (unsigned short angle);                   //donner une valeur à l'angle central de recherche Lidar
unsigned short LIDAR_Get_Angle_min (void);                                      //renvoie l'angle, entre 315° et 45°, où le lidar voit la distance la plus courte
unsigned short LIDAR_Get_Angle_max (void);                                      //renvoie l'angle, entre Search_angle+45 et Search_angle-45, où le lidar voit la distance la plus longue
unsigned short LIDAR_Get_Distance_min (void);                                   //renvoie la distance correspondant à Angle_min, minimum 25mm     depuis le centre du lidar
unsigned short LIDAR_Get_Distance_max (void);                                   //renvoie la distance correspondant à Angle_max, maximum 16000mm  depuis le centre du lidar

//Gestion de la lecture/écriture en EEPROM
void          DATAEE_WriteByte(unsigned short bAdd, unsigned char bData);       //écrit bData à bAdd
unsigned char DATAEE_ReadByte(unsigned short bAdd);                             //renvoie la valeur stockée à bAdd

//Gestion du BlueTooth
void          BT_Send_Char (unsigned char var);                                 //envoie un char au module BT
void          BT_Send_String (unsigned char *str);                              //envoie une chaine de caractères au module BT
unsigned char BT_RC_Enabled (void);                                             //savoir si la récéption depuis la télécommande BT a été autorisée. Si oui, les moteurs sont à l'arrêt tant que la télécommande n'est pas connectée
unsigned char BT_RC_Connected (void);                                           //savoir si le BT est connecté à la telecommande BT

//Gestion du flag d'arrivée
void FLAG_Set (void);

//Gestion du départ
unsigned char Get_Start_Switch (void);                                          //renvoie 0 si le connecteur pour le départ est branché (RB7-GND), sinon 1

#endif

