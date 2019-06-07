/*
 * horodateur.c
 *
 *  Created on: 5 juin 2019
 *      Author: laetitia
 */

#include "i2c.h"
#include<stdio.h>
#include"horodateur.h"

int mode = 1;
int up = 1;
int down = 0;
int champ = 2;
int sens = UP;
int unites_minutes;
int dizaine_minutes;
int minutes;
int unites_heures;
int dizaine_heures;
int heures;
int unites_secondes;
int dizaine_secondes;
int secondes;
int unites_jours;
int dizaine_jours;
int jours;
int unites_mois;
int dizaine_mois;
int mois;
int unites_annees;
int dizaine_annees;
int annees;
int retour;



/*
 * @brief Récupére dans le RTC la valeur que l'utilisateur souhaite modifier (heure, minute ou seconde.
 * @param Prend en parametre "choix_info_a_modifier" qui correspond au buffer de la RTC à modifier
 *
 */
uint8_t receive_info_rtc(int choix_info_a_modifier){

	uint8_t TxBuffer[1];
	uint8_t RxBuffer;

	TxBuffer[0] = choix_info_a_modifier;

	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SLAVE_ADRESS, (uint8_t*)&TxBuffer, 1, MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, (uint16_t)SLAVE_ADRESS,(uint8_t*)&RxBuffer, 1, MAX_DELAY);

	return RxBuffer;
}

/*
 * @brief incrémente ou décrémente en fonction de l'appuie sur le Btn_User
 * @param si on incrémente ou on décrémente
 * @param la valeur reçu
 * @param le type de valeur à modifier
 */
int modifier_valeur_heure_courante(int sens, int RxBuffer, int champ){

	switch (sens){
		case UP:
			switch(champ){
				case SECONDES:
					unites_secondes = (RxBuffer & MASQUE_UNITEES);
					dizaine_secondes = (RxBuffer & MASQUE_DIZAINES) >> 4;
					secondes = dizaine_secondes * 10 + unites_secondes;
					printf("%d\n", secondes);
					minutes++;
					if(secondes == 60){
						secondes = 0;
					}
					retour = secondes;
					break;

				case MINUTES:
					unites_minutes = (RxBuffer & MASQUE_UNITEES);
					dizaine_minutes = (RxBuffer & MASQUE_DIZAINES) >> 4;
					minutes = dizaine_minutes * 10 + unites_minutes;
					printf("%d\n", minutes);
					minutes++;
					if(minutes == 60){
						minutes = 0;
					}
					retour = minutes;
					break;

				case HEURES:
					unites_heures = (RxBuffer & MASQUE_UNITEES);
					dizaine_heures = (RxBuffer & MASQUE_DIZAINES) >> 4;
					heures = dizaine_heures * 10 + unites_heures;
					printf("%d\n", heures);
					heures++;
					if(heures == 24){
						heures = 0;
					}
					retour = heures;
					break;

				case JOURS:
					unites_jours = (RxBuffer & MASQUE_UNITEES);
					dizaine_jours = (RxBuffer & MASQUE_DIZAINES) >> 4;
					jours = dizaine_secondes * 10 + unites_jours;
					printf("%d\n", jours);
					jours++;
					if(jours == 32){
						jours = 0;
					}
					retour = jours;
					break;

				case MOIS:
					unites_mois = (RxBuffer & MASQUE_UNITEES);
					dizaine_mois = (RxBuffer & MASQUE_DIZAINES) >> 4;
					mois = dizaine_mois * 10 + unites_mois;
					printf("%d\n", mois);
					mois++;
					if(mois == 13){
						mois = 0;
					}
					retour = mois;
					break;

				case ANNEES:
					unites_annees = (RxBuffer & MASQUE_UNITEES);
					dizaine_annees = (RxBuffer & MASQUE_DIZAINES) >> 4;
					annees = dizaine_annees * 10 + unites_annees;
					printf("%d\n", annees);
					annees++;
					if(annees == 100){
						annees = 00;
					}
					retour = annees;
					break;
			}
			break;
		case DOWN:
			switch(champ){
			case SECONDES:
				unites_secondes = (RxBuffer & MASQUE_UNITEES);
				dizaine_secondes = (RxBuffer & MASQUE_DIZAINES) >> 4;
				secondes = dizaine_secondes * 10 + unites_secondes;
				printf("%d\n", secondes);
				minutes--;
				if(secondes == 0){
					secondes = 59;
				}
				retour = secondes;
				break;

			case MINUTES:
				unites_minutes = (RxBuffer & MASQUE_UNITEES);
				dizaine_minutes = (RxBuffer & MASQUE_DIZAINES) >> 4;
				minutes = dizaine_minutes * 10 + unites_minutes;
				printf("%d\n", minutes);
				minutes--;
				if(minutes == 0){
					minutes = 59;
				}
				retour = minutes;
				break;

			case HEURES:
				unites_heures = (RxBuffer & MASQUE_UNITEES);
				dizaine_heures = (RxBuffer & MASQUE_DIZAINES) >> 4;
				heures = dizaine_heures * 10 + unites_heures;
				printf("%d\n", heures);
				heures--;
				if(heures == 0){
					heures = 24;
				}
				retour = heures;
				break;
			case JOURS:
				unites_jours = (RxBuffer & MASQUE_UNITEES);
				dizaine_jours = (RxBuffer & MASQUE_DIZAINES) >> 4;
				jours = dizaine_secondes * 10 + unites_jours;
				printf("%d\n", jours);
				jours--;
				if(jours == 0){
					jours = 32;
				}
				retour = jours;
				break;

			case MOIS:
				unites_mois = (RxBuffer & MASQUE_UNITEES);
				dizaine_mois = (RxBuffer & MASQUE_DIZAINES) >> 4;
				mois = dizaine_mois * 10 + unites_mois;
				printf("%d\n", mois);
				mois--;
				if(mois == 0){
					mois = 13;
				}
				retour = mois;
				break;

			case ANNEES:
				unites_annees = (RxBuffer & MASQUE_UNITEES);
				dizaine_annees = (RxBuffer & MASQUE_DIZAINES) >> 4;
				annees = dizaine_annees * 10 + unites_annees;
				printf("%d\n", annees);
				annees--;
				if(annees == 00){
					annees = 100;
				}
				retour = annees;
				break;
			}
			break;
	}
	return retour;
}

/*
 * @brief Met à jour le RTC .
 * @param valeur modifier par l'utilisateur
 * @param Prend en parametre "choix_info_a_modifier" qui correspond au buffer de la RTC à modifier
 *
 */
void mise_a_jour_rtc(int RxBuffer, int choix_info_a_modifier){

	uint8_t TxBuffer[2];

	TxBuffer[0] = choix_info_a_modifier;
	TxBuffer[1] = RxBuffer;

	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SLAVE_ADRESS, (uint8_t*)&TxBuffer, 2, MAX_DELAY);

}

/*
 * @Brief Permet de passer du mode Horloge au mode Réglages via la touche tactile n°4.
 */
int Change_Mode(void){
	if(mode == HORLOGE){
		printf("         Mode Reglages\n");
		printf("---------------------------------\n");
		printf("| O       O        O      O     |\n");
		printf("| up/   param            mode   |\n");
		printf("|down     a             reglage/|\n");
		printf("|      modifier         horloge |\n");
		printf("---------------------------------\n");

		mode = REGLAGES;
	}
	else if(mode == REGLAGES){
		printf("Mode Horloge\n");
		mode = HORLOGE;
	}
	return mode;

}
/*
 * @Brief Permet de changer l'heure courante (secondes,minutes,heures).
 */
int Choix_Champ(void){
	switch (champ){
	case ANNEES:
		champ = SECONDES;
		printf("Secondes\n");
		break;
	case SECONDES:
		champ = MINUTES;
		printf("Minutes\n");
		break;
	case MINUTES:
		champ = HEURES;
		printf("Heures\n");
		break;
	case HEURES:
		champ = JOURS;
		printf("Jours\n");
		break;
	case JOURS:
		champ = MOIS;
		printf("Mois\n");
		break;
	case MOIS:
		champ = ANNEES;
		printf("Annees\n");
		break;
	}
	return champ;
}

/*
 * @Brief Permet de changer le sens du changement d'heure (- ou +)
 */
int Choix_Sens(void){
	sens++;
	if(sens%2 == UP){
		printf("Up\n");
	}
	else if(sens%2 == DOWN){
		printf("Down\n");
	}
	return sens%2;

}



