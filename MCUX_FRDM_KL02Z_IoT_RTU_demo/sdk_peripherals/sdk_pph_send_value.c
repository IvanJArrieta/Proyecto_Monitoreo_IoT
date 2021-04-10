/*
 * sdk_pph_sth31_envio.c
 *
 *  Created on: 15/03/2021
 *      Author: IVAN JOSE
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <sdk_pph_send_value.h>
#include "stdio.h"
#include "sdk_pph_ec25au.h"
#include "sdk_mdlw_leds.h"
#include "sdk_pph_sht3x.h"
#include "sdk_hal_uart0.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CLOCK	8000000
#define HABILITAR_SENSOR_SHT3X		1
#define SEND  0x1A

/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
void borrarBufferQuectel(void);

/*******************************************************************************
 * Local vars
 ******************************************************************************/
uint8_t sht3x_base_de_tiempo=0;
sht3x_data_t sht3x_datos;
uint8_t sht3x_detectado=0;
uint8_t sht3x_dato_salida=0;
uint8_t Enviar_MQTT[100];
uint8_t Enviar_PUB[50];

float value;
float value1;
float result;
float result1;

const uint8_t  *Subscrip_Topic[]={
	/*0*/"AT+QMTSUB=0 ,1,\"1/sensor\",1",
	/*1*/"AT+QMTPUB=0,0,0,0,\"1/sensor\""
};


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/

status_t enviarMQTT_ValueSHT3x(void) {
	sht3xReadData(&sht3x_datos);

//OPERACIONES PARA ENVIAR DATOS DE HUMEDAD Y TEMPERATURA

	value = (float)sht3x_datos.temperatura;
	result  = 175*value;
	result = result/65535;
	result = result - 45;

	value1  = (float)sht3x_datos.humedad;
	result1 = 100*(value1/65535);

//FIN DE OPERACIONES

	sprintf((char *)(&Enviar_PUB),"%s\r\n", Subscrip_Topic[kAT_QMTPUB_Topic]); //Creacion de string para enviar por Buffer
	printf("%s\r\n", Subscrip_Topic[kAT_QMTPUB_Topic]); //Imprime en consola la suscripcion
	uart0ImprimirMensaje((&Enviar_PUB[0]),strlen(Enviar_PUB));	//Enviar por puerto serial Micro-Modem

	waytTime(400); //Tiempo de espera entre comandos enviados por puerto serial

	sprintf((char *)(&Enviar_MQTT[0]),"temperatura,%.2f,humedad,%.2f,\r\n %c",result,result1,SEND); //Creacion de string para enviar por Buffer
	printf("temperatura,%.2f,humedad,%.2f,\r\n %c",result,result1,SEND); //Imprime datos de temperatura y humedad en consola
	uart0ImprimirMensaje((&Enviar_MQTT[0]),strlen(Enviar_MQTT)); //Enviar por puerto serial Micro-Modem


	waytTime(400);	//Tiempo de espera entre comandos enviados por puerto serial


	printf("\r\n");


	return(0);

}
