/*
 * tusb_family.h
 *
 *  Created on: Aug 9, 2025
 *      Author: mines
 */

#ifndef INC_TUSB_FAMILY_H_
#define INC_TUSB_FAMILY_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

void board_led_write(bool state);
uint32_t board_button_read(void);
uint32_t board_millis(void);
size_t board_get_unique_id(uint8_t id[], size_t max_len);
size_t myboard_usb_get_serial(uint16_t desc_str1[], size_t max_chars);

#endif /* INC_TUSB_FAMILY_H_ */
