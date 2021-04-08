/*! @file : MCUX_FRDM_KL02Z_IoT_RTU_demo.c
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    8/01/2021
 * @brief   Funcion principal main
 * @details
 *			v0.1 dato recibido por puerto COM es contestado en forma de ECO
 *			v0.2 dato recibido por puerto COM realiza operaciones especiales
 *					A/a=invierte estado de LED conectado en PTB10
 *					v=apaga LED conectado en PTB7
 *					V=enciende LED conectado en PTB7
 *					r=apaga LED conectado en PTB6
 *			v0.3 nuevo comando por puerto serial para prueba de MMA8451Q
 *					M=detecta acelerometro MM8451Q en bus I2C0
 *
 *
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"


#include "sdk_hal_uart0.h"
#include "sdk_hal_gpio.h"
#include "sdk_hal_i2c0.h"
#include "sdk_hal_i2c1.h"
#include "sdk_hal_adc.h"
#include "sdk_hal_lptmr0.h"

#include "sdk_mdlw_leds.h"
#include "sdk_pph_ec25au.h"
#include <sdk_pph_send_value.h>
#include "sdk_pph_sht3x.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define HABILITAR_MODEM_EC25		1
#define HABILITAR_SENSOR_SHT3X		1
#define HABILITAR_TLPTMR0			1



/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
void waytTime(uint32_t tiempo) { //Funcion de control de tiempo de Timer

	//espera a que hayan ocurrido por lo menos 100ms interrupciones
	while (lptmr0GetTimeValue() < tiempo){
	}
	lptmr0SetTimeValue(0);		//Reset de variable contador de interrupciones
}
/*
 * @brief   Application entry point.
 */
int main(void) {
	uint8_t ec25_mensaje_de_texto[]="Hola desde EC25";
	uint8_t ec25_estado_actual;

	uint8_t sht3x_detectado=0;


    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    printf("Inicializa UART0:");
    //inicializa puerto UART0 y solo avanza si es exitoso el proceso
    if(uart0Inicializar(115200)!=kStatus_Success){	//115200bps
    	printf("Error");
    	return 0 ;
    };
    printf("OK\r\n");

    printf("Inicializa I2C0:");
    //inicializa puerto I2C0 y solo avanza si es exitoso el proceso
    if(i2c0MasterInit(100000)!=kStatus_Success){	//100kbps
    	printf("Error");
    	return 0 ;
    }
    printf("OK\r\n");

    printf("Inicializa I2C1:");
    //inicializa puerto I2C1 y solo avanza si es exitoso el proceso
    if(i2c1MasterInit(100000)!=kStatus_Success){	//100kbps
    	printf("Error");
    	return 0 ;
    }
    printf("OK\r\n");

#if HABILITAR_SENSOR_SHT3X
    printf("Detectando SHT3X:");

    //LLamado a funcion que identifica sensor SHT3X
    if(sht3xInit()== kStatus_Success){
    	sht3x_detectado=1;
    	printf("OK\r\n");
    }
#endif


#if HABILITAR_MODEM_EC25
    //Inicializa todas las funciones necesarias para trabajar con el modem EC25
    printf("Inicializa modem EC25\r\n");
    ec25Inicializacion();

    ec25EnviarMensajeDeTexto(&ec25_mensaje_de_texto[0], sizeof(ec25_mensaje_de_texto));
#endif

#if HABILITAR_TLPTMR0
    //Inicializa todas las funciones necesarias para trabajar con el modem EC25
    printf("Inicializa low power timer 0\r\n");

    lptmr0Init();
#endif

	//Ciclo infinito encendiendo y apagando led verde
	//inicia SUPERLOOP
    while(1) {
    	waytTime(500);		//Espera 400ms para entrar a ejecutar maquina de estados


#if HABILITAR_MODEM_EC25
    	ec25_estado_actual = ec25Polling();	//actualiza maquina de estados encargada de avanzar en el proceso interno del MODEM
											//retorna el estado actual de la FSM

		switch(ec25_estado_actual){			//control de color de los LEDs dependiendo de estado modem EC25
    	case kFSM_RESULTADO_ERROR:
    		toggleLedRojo();
    		apagarLedVerde();
    		apagarLedAzul();
    		break;

    	case kFSM_RESULTADO_EXITOSO:
    		apagarLedRojo();
    		toggleLedVerde();
    		apagarLedAzul();
    		if (ec25_estado_actual==kFSM_RESULTADO_EXITOSO){ //Llamado de funcion para enviar datos del sensor SHT3x
    		  	enviarMQTT_ValueSHT3x();
    		 	waytTime(1000);
    		 }
    		break;

    	case kFSM_RESULTADO_ERROR_RSSI:
    		toggleLedRojo();
    		apagarLedVerde();
    		toggleLedAzul();

    		break;

    	default:
    		apagarLedRojo();
    		apagarLedVerde();
    		toggleLedAzul();
    		break;
    	}
#endif
    }
    return 0 ;
}
