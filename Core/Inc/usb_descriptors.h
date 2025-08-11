/*
 * usb_descriptors.h
 *
 *  Created on: Aug 9, 2025
 *      Author: mines
 */

#ifndef INC_USB_DESCRIPTORS_H_
#define INC_USB_DESCRIPTORS_H_

enum {
  ITF_NUM_KEYBOARD = 0,
  ITF_NUM_CDC_0,
  ITF_NUM_CDC_0_DATA,
  ITF_NUM_TOTAL
};

uint8_t const *tud_descriptor_device_cb(void);
uint8_t const *tud_descriptor_configuration_cb(uint8_t index);
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid);

#endif /* INC_USB_DESCRIPTORS_H_ */
