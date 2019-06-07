/*
 * horodateur.h
 *
 *  Created on: 5 juin 2019
 *      Author: laetitia
 */

#ifndef HORODATEUR_H_
#define HORODATEUR_H_

#define SLAVE_ADRESS 0b1101000<<1

#define HORLOGE 1
#define REGLAGES 0
#define SECONDES 0
#define MINUTES 1
#define HEURES 2
#define UP 0
#define DOWN 1
#define MAX_DELAY 1000

#define BTN_APPUYER 1

#define MASQUE_CHBit 0b10000000
#define MASQUE_CHBit_0 0b01111111
#define MASQUE_UNITEES 0b00001111
#define MASQUE_DIZAINES 0b01110000
#define MASQUE_DIZAINES_JOUR 0b00110000
#define MASQUE_DIZAINES_MOIS 0b00010000
#define MASQUE_DIZAINES_ANNEE 0b11110000


int Change_Mode(void);
int Choix_Champ(void);
int Choix_Sens(void);
uint8_t receive_info_rtc(int);
int modifier_valeur_heure_courante(int, int, int);
void mise_a_jour_rtc(int, int);




#endif /* HORODATEUR_H_ */
