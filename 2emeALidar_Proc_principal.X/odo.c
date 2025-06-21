#include <xc.h>
#include <math.h> 
#include "Fonction.h"
#include "LCD.h"

Odometrie_t odo = {0};

void LCD_afficher_odometrie(void) {
    LCD_Goto(0, 0);
    LCD_Print("G:");
    LCD_Goto(0, 2);
    LCD_Write_s16bits(odo.distance_gauche_int, 4);

    LCD_Goto(0, 9);
    LCD_Print("D:");
    LCD_Goto(0, 11);
    LCD_Write_s16bits(odo.distance_droite_int, 4);

    LCD_Goto(1, 0);
    LCD_Print("ang:");
    LCD_Goto(1, 5);
    LCD_Write_s16bits((signed short)odo.angle_abs, 5); 
}

void calcul_distance_roues(void) {
    odo.ticks_gauche = Motors_Get_Enc_Left();
    odo.distance_gauche_mm = (PI * DIAMETRE_ROUE_MM * odo.ticks_gauche) / ENCODEUR_TICKS_PAR_TOUR;
    odo.distance_gauche_mm *= COEF_CORRECTION_GAUCHE;
    odo.distance_gauche_int = (signed long)odo.distance_gauche_mm;

    odo.ticks_droite = Motors_Get_Enc_Right();
    odo.distance_droite_mm = (PI * DIAMETRE_ROUE_MM * odo.ticks_droite) / ENCODEUR_TICKS_PAR_TOUR;
    odo.distance_droite_mm *= COEF_CORRECTION_DROITE;
    odo.distance_droite_int = (signed long)odo.distance_droite_mm;
}

void calcul_angle_robot(float dist_gauche, float dist_droite) {
    static float ancienne_distance_g = 0.0f;
    static float ancienne_distance_d = 0.0f;

    float delta_g = dist_gauche - ancienne_distance_g;
    float delta_d = dist_droite - ancienne_distance_d;

    float delta_theta = (delta_d - delta_g) / ENTRAXE_ROUES_MM;
    odo.angle_rad += delta_theta;
    odo.angle_deg = odo.angle_rad * (180.0f / PI);

    odo.angle_abs = fmodf(odo.angle_deg, 360.0f);
    if (odo.angle_abs < 0.0f) {
        odo.angle_abs += 360.0f;
    }

    ancienne_distance_g = dist_gauche;
    ancienne_distance_d = dist_droite;
}

void mise_a_jour_odometrie(void) {
    calcul_distance_roues();
    calcul_angle_robot(odo.distance_gauche_mm, odo.distance_droite_mm);
}