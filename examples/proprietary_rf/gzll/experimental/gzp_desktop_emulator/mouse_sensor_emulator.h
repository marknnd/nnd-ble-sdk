/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 * $LastChangedRevision: 15516 $
 */

#ifndef __NRF_MOUSE_SENSOR_H
#define __NRF_MOUSE_SENSOR_H

/**
 * @file
 * @brief Mouse Emulator API
 */


/**
 * @defgroup gzp_mouse_emulator Mouse Emulator
 * @{
 * @ingroup gzp_desktop_device_emulator_example
 * @brief  Emulates a mouse using one of the nRF51's timer peripherals.
 */

#include "nrf.h"
#include <stdint.h>
#include <stdbool.h>
#include "nrf_gzllde_params.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum mouse_sensor_sample_period_t
 * @brief Enumerator used for setting the mouse sensor sample period.
 */
typedef enum
{
    MOUSE_SENSOR_SAMPLE_PERIOD_4_MS, ///<  Generate new mouse sample every 4 ms.
    MOUSE_SENSOR_SAMPLE_PERIOD_8_MS, ///<  Generate new mouse sample every 8 ms.
} mouse_sensor_sample_period_t;

/**
 * @brief Function for initializing the mouse sensor.
 *
 * @param sample_period specifies the mouse sensor sample period.
 *
 * @retval true If initialization succeeded.
 * @retval false If initialization failed.
 */
bool mouse_sensor_init(mouse_sensor_sample_period_t sample_period);

/**
 * @brief Enable mouse sensor.
 *
 * When enabled, the mouse sensor will start generating mouse movement samples
 * at the rate given by mouse_sensor_init(void).
 */
void mouse_sensor_enable(void);

/**
 * @brief Disable mouse sensor.
 */
void mouse_sensor_disable(void);

/**
 * @brief Function for polling if the mouse sensor
 * has data available for readout.
 *
 * @retval true If there is data available for reading.
 * @retval false If no data is available for reading.
 *
 * @sa mouse_sensor_read(void)
 */
bool mouse_sensor_data_is_ready(void);

/**
 * @brief Function for reading motion samples from the the mouse
 * sensor.
 *
 * The mouse sensor will generate a new sample at a rate given by
 * mouse_sensor_init(). If multiple samples are generated by the mouse sensor
 * between each call of this function, the samples will be accumulated.
 * Thus, the mouse packet returned by this function will tell the relative
 * movement of the mouse since the previous time this function was called.
 * The internal accumulator is cleared whenever the mouse sensor is read.
 *
 * @param out_mouse_packet returns an assembled mouse movement packet
 * (no buttons) as specified in "nrfdvl_params.h" .
 *
 * The length of the mouse packet is given by NRFR_MOUSE_MOV_PACKET_LENGTH.
 *
 * @retval true If a new packet was written to out_mouse_packet *.
 * @retval false If no new mouse data was available.
 */
bool mouse_sensor_read(uint8_t * out_mouse_packet);

// lint -save -esym(522,mouse_sensor_new_sample_generated_cb)
/**
 * @brief Callback function called when a new sample is generated
 * by the mouse sensor. When the mouse sensor is enabled, this
 * function will be called at a rate as specified by mouse_sensor_init().
 */
void mouse_sensor_new_sample_generated_cb(void);
// lint -restore

/** @} */

#ifdef __cplusplus
}
#endif

#endif
