/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "string.h"
#include "stdio.h"
#include "i2c.h"
#include "horodateur.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MASQUE_CHBit 0b10000000
#define MASQUE_CHBit_0 0b01111111
#define MASQUE_UNITEES 0b00001111
#define MASQUE_DIZAINES 0b01110000
#define MASQUE_DIZAINES_JOUR 0b00110000
#define MASQUE_DIZAINES_MOIS 0b00010000
#define MASQUE_DIZAINES_ANNEE 0b11110000


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t transmission_I2C1[4];
uint8_t reception_I2C1[3];
uint8_t * p_transmission_I2C1 = transmission_I2C1;
uint8_t * p_reception_I2C1 = reception_I2C1;
extern int mode;
extern int sens;
extern int champ;
uint8_t valeur = 0;
int unite;
					int dizaine;


/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId MyTaskModeHandle;
osThreadId myTaskChampsHandle;
osThreadId myTaskSensReglaHandle;
osThreadId myTaskValeurSuiHandle;
osThreadId myTaskRTCaffichHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void TaskMode(void const * argument);
void TaskChamps(void const * argument);
void TaskSensReglage(void const * argument);
void TaskValeurSuivante(void const * argument);
void TaskRTCaffichage(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* definition and creation of MyTaskMode */
	osThreadDef(MyTaskMode, TaskMode, osPriorityNormal, 0, 128);
	MyTaskModeHandle = osThreadCreate(osThread(MyTaskMode), NULL);

	/* definition and creation of myTaskChamps */
	osThreadDef(myTaskChamps, TaskChamps, osPriorityNormal, 0, 128);
	myTaskChampsHandle = osThreadCreate(osThread(myTaskChamps), NULL);

	/* definition and creation of myTaskSensRegla */
	osThreadDef(myTaskSensRegla, TaskSensReglage, osPriorityNormal, 0, 128);
	myTaskSensReglaHandle = osThreadCreate(osThread(myTaskSensRegla), NULL);

	/* definition and creation of myTaskValeurSui */
	osThreadDef(myTaskValeurSui, TaskValeurSuivante, osPriorityNormal, 0, 128);
	myTaskValeurSuiHandle = osThreadCreate(osThread(myTaskValeurSui), NULL);

	/* definition and creation of myTaskRTCaffich */
	osThreadDef(myTaskRTCaffich, TaskRTCaffichage, osPriorityNormal, 0, 128);
	myTaskRTCaffichHandle = osThreadCreate(osThread(myTaskRTCaffich), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for(;;)
	{
		osDelay(1000);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_TaskMode */
/**
 * @brief Function implementing the MyTaskMode thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TaskMode */
void TaskMode(void const * argument)
{
	/* USER CODE BEGIN TaskMode */
	/* Infinite loop */
	for(;;)
	{
		//le bouton tactile4 (MODE) est  activé
		if (HAL_GPIO_ReadPin(ToucheTactile4_GPIO_Port, ToucheTactile4_Pin) == 1)
		{
			Change_Mode();
		}

		osDelay(500);

	}
	/* USER CODE END TaskMode */
}

/* USER CODE BEGIN Header_TaskChamps */
/**
 * @brief Function implementing the myTaskChamps thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TaskChamps */
void TaskChamps(void const * argument)
{
	/* USER CODE BEGIN TaskChamps */
	/* Infinite loop */
	for(;;)
	{
		if (mode == REGLAGES)
		{
			//le bouton tactile3 (choix du champ) est  activé
			if (HAL_GPIO_ReadPin(ToucheTactile2_GPIO_Port, ToucheTactile2_Pin) == 1)
			{
				champ = Choix_Champ();
				valeur = receive_info_rtc(champ);
				//printf("valeur renvoyee : %d \n", valeur);
			}
		}
		osDelay(500);
	}
	/* USER CODE END TaskChamps */
}

/* USER CODE BEGIN Header_TaskSensReglage */
/**
 * @brief Function implementing the myTaskSensRegla thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TaskSensReglage */
void TaskSensReglage(void const * argument)
{
	/* USER CODE BEGIN TaskSensReglage */
	/* Infinite loop */
	for(;;)
	{
		if (mode == REGLAGES)
		{
			//le bouton tactile1 (sens reglage UP OU DOWN) est  activé
			if (HAL_GPIO_ReadPin(ToucheTactile1_GPIO_Port, ToucheTactile1_Pin) == 1)
			{
				sens = Choix_Sens();
			}
		}

		osDelay(500);
	}
	/* USER CODE END TaskSensReglage */
}

/* USER CODE BEGIN Header_TaskValeurSuivante */
/**
 * @brief Function implementing the myTaskValeurSui thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TaskValeurSuivante */
void TaskValeurSuivante(void const * argument)
{
	/* USER CODE BEGIN TaskValeurSuivante */
	/* Infinite loop */
	for(;;)
	{
		if (mode == REGLAGES)
		{
			//le USER BOUTON (reglage valeurs) est  activé
			if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == 1)
			{
				uint8_t new_valeur = modifier_valeur_heure_courante(sens, valeur, champ);

				if (champ == SECONDES)
				{
					//calcul des secondes
					unite = new_valeur%10;
					printf("unité nouvelle valeur %d\n", unite);
					dizaine = (new_valeur-unite)/10;
					printf("dizaine nouvelle valeur %d\n", dizaine);


					new_valeur =  (dizaine<<4) + unite ;
					mise_a_jour_rtc( new_valeur, champ);
				}
				else if (champ == MINUTES)
				{
					//séparation de la nouvelle valeur en unité et dizaine



					unite = new_valeur%10;
					printf("unité nouvelle valeur %d\n", unite);
					dizaine = (new_valeur-unite)/10;
					printf("dizaine nouvelle valeur %d\n", dizaine);


					new_valeur =  (dizaine<<4) + unite ;
					mise_a_jour_rtc( new_valeur, champ);
				}
				else if (champ == HEURES)
				{
					unite = new_valeur%10;
					printf("unité nouvelle valeur %d\n", unite);
					dizaine = (new_valeur-unite)/10;
					printf("dizaine nouvelle valeur %d\n", dizaine);


					new_valeur =  (dizaine<<4) + unite ;
					mise_a_jour_rtc( new_valeur, champ);
				}



				valeur = receive_info_rtc(champ);


			}
		}

		osDelay(500);
	}
	/* USER CODE END TaskValeurSuivante */
}

/* USER CODE BEGIN Header_TaskRTCaffichage */
/**
 * @brief Function implementing the myTaskRTCaffich thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TaskRTCaffichage */
void TaskRTCaffichage(void const * argument)
{
	/* USER CODE BEGIN TaskVariationLED */
	transmission_I2C1[0] = 0; //adresse des secondes dans la mémoire de la carte RTC

	//le programme récupère la valeur SECONDES de la RTC
	HAL_I2C_Master_Transmit(&hi2c1, (uint8_t)SLAVE_ADRESS, p_transmission_I2C1, (uint16_t)1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, (uint8_t)SLAVE_ADRESS, (uint8_t *)p_reception_I2C1, (uint16_t)1, HAL_MAX_DELAY);

	//le programme masque l'octet SECONDE envoyé à la RTC pour isoler la valeur du CH Bit
	uint8_t valeur_CH_Bit = (*p_reception_I2C1) & MASQUE_CHBit;

	//Si CHBit est égale à 1, la RTC est désactivé
	if (valeur_CH_Bit == MASQUE_CHBit)
	{
		//le programme active la RTC en passant CHBit à 0 sans écraser le reste et envoie l'info à la RTC
		transmission_I2C1[1] = (*p_reception_I2C1) & ( MASQUE_CHBit_0 );
		HAL_I2C_Master_Transmit(&hi2c1, (uint8_t)SLAVE_ADRESS, p_transmission_I2C1, (uint16_t)2, HAL_MAX_DELAY);
	}

	/* Infinite loop */
	for(;;)
	{

		if (mode == HORLOGE)
		{
			HAL_I2C_Master_Transmit(&hi2c1, (uint8_t)SLAVE_ADRESS, p_transmission_I2C1, (uint16_t)1, HAL_MAX_DELAY);
			HAL_I2C_Master_Receive(&hi2c1, (uint8_t)SLAVE_ADRESS, (uint8_t *)p_reception_I2C1, (uint16_t)3, HAL_MAX_DELAY);


			//calcul des secondes
			int unites_secondes = (*p_reception_I2C1) & (MASQUE_UNITEES);
			int dizaines_secondes = (*p_reception_I2C1 & (MASQUE_DIZAINES)) >> 4;
			int secondes = (dizaines_secondes * 10) + unites_secondes;

			//calcul des minutes
			int unites_minutes = (*(p_reception_I2C1+1))& (MASQUE_UNITEES);
			int dizaine_minutes =(*(p_reception_I2C1+1) & (MASQUE_DIZAINES)) >> 4;
			int minutes = dizaine_minutes * 10 + unites_minutes;

			//calcul des heures
			int unites_heure = (*(p_reception_I2C1+2))& (MASQUE_UNITEES);
			int dizaine_heure =(*(p_reception_I2C1+2) & (MASQUE_DIZAINES)) >> 4;
			int heure = dizaine_heure * 10 + unites_heure;

			printf("%d h : %d min : %d sec \n", heure, minutes ,secondes);
		}

		osDelay(1000);
	}
	/* USER CODE END TaskRTCaffichage */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
