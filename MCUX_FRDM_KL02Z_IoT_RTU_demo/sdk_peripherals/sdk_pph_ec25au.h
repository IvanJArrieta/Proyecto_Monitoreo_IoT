/*! @file : sdk_pph_ec25au.h
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    23/01/2021
 * @brief   Driver para modem EC25AU
 * @details
 *
 */
#ifndef SDK_PPH_EC25AU_H_
#define SDK_PPH_EC25AU_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sdk_hal_uart0.h"

/*!
 * @addtogroup PPH
 * @{
 */
/*!
 * @addtogroup EC25AU
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
enum _ec25_lista_comandos_at {
	kAT = 0,
	kATI,
	kAT_CPIN,
	kAT_QCFG_banda1,
	kAT_QCFG_banda2,
	kAT_CREG,
	kAT_CMGF_1,
	kAT_APN,
	kAT_QIACT_1,
	kAT_QIACT_2,
	kAT_CGDCONT_IP,
	kAT_QMTCONN_topic,
	kAT_CFUN_0,
	kAT_CFUN_1,
	kAT_CSQ,
};

enum _fsm_ec25_state{
	kFSM_INICIO=0,
	kFSM_ENVIANDO_AT,
	kFSM_ENVIANDO_ATI,
	kFSM_ENVIANDO_CPIN,
	kFSM_ENVIANDO_AT_QCFG_banda1,
	kFSM_ENVIANDO_AT_QCFG_banda2,
	kFSM_ENVIANDO_CREG,
	kFSM_ENVIANDO_CMGF,
	kFSM_ENVIANDO_AT_APN,
	kFSM_ENVIANDO_ATQIACT_1,
	kFSM_ENVIANDO_AT_QIACT_2,
	kFSM_ENVIANDO_AT_CGDCONT_IP,
	kFSM_ENVIANDO_AT_QMTCONN_topic,
	kFSM_ENVIANDO_STH31,
	kFSM_ESPERANDO_RESPUESTA,
	kFSM_RESULTADO_ERROR,
	kFSM_RESULTADO_EXITOSO,
	kFSM_ENVIANDO_CSQ,
	kFSM_PROCESANDO_RESPUESTA,
	kFSM_RESULTADO_ERROR_RSSI,
	kFSM_ENVIANDO_CFUN_0,
	kFSM_ENVIANDO_CFUN_1,
};

#define EC25_TIEMPO_MAXIMO_ESPERA	5		//Tiempo maximo que espera modem por respuesta
#define EC25_RSSI_MINIMO_ACEPTADO	20		//RSSI minimo aceptado segun tabla de fabricante
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
status_t enviarMQTT_ValueSHT3x(void);
status_t ec25Inicializacion(void);
status_t ec25EnviarMensajeDeTexto(uint8_t *mensaje, uint8_t size_mensaje );
uint8_t ec25Polling(void);
status_t ec25EnviarCFUN0(void);
/** @} */ // end of X group
/** @} */ // end of X group

#endif /* SDK_PPH_EC25AU_H_ */
