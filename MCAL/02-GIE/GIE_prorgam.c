/*
 * GIE_prorgam.c
 *
 *  Created on: 12 Sep 2021
 *      Author: Maged
 */

#include "../../Services/BIT_MATH.h"
#include "../../Services/STD_Types.h"

#include "GIE_interface.h"
#include "GIE_config.h"
#include "GIE_private.h"

void GIE_voidEnableInterrupts(void) {
	SET_BIT(SREG, GIE_BIT);
}

void GIE_voidDisableInterrupts(void) {
	CLR_BIT(SREG, GIE_BIT);
}
