/**
* @file adc/include/adc.h
* @brief header file for adc library
* @author hugo descoubes - copyleft
*/

/** @ingroup ADC */
/* @{ */
/** @defgroup ADC_8BITS */
/** @ingroup ADC_8BITS */
/* @{ */
#ifndef _ADC_H
#define _ADC_H

#include <common/include/common.h>

/* API reference */

 /**
  * @brief adc internal peripheral initialization
  * @li source : FRC internal ADC clock reference
  * @li pin : RA0/AN0
  * @li mode : left adjust, no interrupt
  * @li voltage range : Vref-=Vss and Vref+=VDD
  * @li precharge time : exclude from conversion
  * @li acquisition time : exclude from conversion 
  * @li misc : discontinuous mode, non aditionnal capacitance
  * @warning 8 bits conversion
  */
void adc_init(void);

 /**
  * @brief read 8 Msbits converted data from adc
  * @warning 8 bits conversion
  * @return 8 bits converted data
  */
uInt8_t adc_read(void);

 /**
  * @brief enable adc module
  */
#define adc_enable()

 /**
  * @brief start conversion
  */
#define adc_start()

 /**
  * @brief wait the end of conversion
  */
#define adc_busy()

#endif /* _ADC_H */


















