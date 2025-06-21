#include "Config.c"
#include "Define.c"
#include <xc.h>
#include "LCD.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include "Variables.c"
#include "Fonctions.c"
#include "Init.c"
#include "Isr.c"
#include "Fonction.h"

unsigned long pres_LCD = 0 , past_LCD = 0, pres_odo = 0, past_odo = 0;
signed char MOTEUR_SPEED_GAUCHE = 0, MOTEUR_SPEED_DROITE = 0, etat = 0;

void init(void) {
    Initialisation();
    LCD_Clear();
    LCD_Retro(1);
    Motors_Enable(1);
    MOTEUR_SPEED_GAUCHE = MOTEUR_ARRET;
    MOTEUR_SPEED_DROITE = MOTEUR_ARRET;
}

int main(void) {
    init();
    Motors_Turn_Angle(355);
    
    while (1) {

        pres_odo = Get_Millis();
        pres_LCD = Get_Millis();
        
        if (pres_odo - past_odo >= 10) {
            past_odo = pres_odo;
            mise_a_jour_odometrie();
        }

        if (pres_LCD - past_LCD >= 250) {
            past_LCD = pres_LCD;
            LCD_Clear();
            LCD_afficher_odometrie();
        }

        switch (etat) {
            case 0:
                break;
            case 1:
                break;
        }

        Motors_Speed(MOTEUR_SPEED_GAUCHE, MOTEUR_SPEED_DROITE);
    }

    return 0;
}
