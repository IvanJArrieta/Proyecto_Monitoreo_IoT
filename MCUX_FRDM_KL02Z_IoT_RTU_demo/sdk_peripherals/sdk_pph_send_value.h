/*
 * sdk_pph_sth31_envio.h
 *
 *  Created on: 15/03/2021
 *      Author: IVAN JOSE
 */

#ifndef SDK_PPH_SEND_VALUE_H_
#define SDK_PPH_SEND_VALUE_H_

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


enum _comandos_at_topic_sht3x {
	kAT_QMTSUB_Topic = 0,
	kAT_QMTPUB_Topic,

};

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
void waytTimeModem(uint32_t tiempo);

status_t enviarMQTT_ValueSHT3x(void);

/** @} */ // end of X group
/** @} */ // end of X group

#endif /* SDK_PPH_SEND_VALUE_H_ */
