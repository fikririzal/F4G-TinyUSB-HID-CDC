/*
 * tusb_family.c
 *
 *  Created on: Aug 9, 2025
 *      Author: mines
 */

#include "main.h"

#include "tusb_family.h"
#include "tusb_config.h"
#include "tusb.h"

/* metadata:
   manufacturer: STMicroelectronics
*/

#include "stm32f4xx_hal.h"
//#include "bsp/board_api.h"

typedef struct {
  GPIO_TypeDef* port;
  GPIO_InitTypeDef pin_init;
  uint8_t active_state;
} board_pindef_t;

//#include "board.h"

//--------------------------------------------------------------------+
// Forward USB interrupt events to TinyUSB IRQ Handler
//--------------------------------------------------------------------+
void OTG_FS_IRQHandler(void) {
  tusb_int_handler(0, true);
}

//void OTG_HS_IRQHandler(void) {
//  tusb_int_handler(1, true);
//}

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM
//--------------------------------------------------------------------+
void board_init(void) {
//  board_clock_init();
//  //SystemCoreClockUpdate();
//
//  // Enable All GPIOs clocks
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//  __HAL_RCC_GPIOC_CLK_ENABLE();
//  __HAL_RCC_GPIOD_CLK_ENABLE();
//#ifdef __HAL_RCC_GPIOE_CLK_ENABLE
//  __HAL_RCC_GPIOE_CLK_ENABLE();
//#endif
//#ifdef __HAL_RCC_GPIOF_CLK_ENABLE
//  __HAL_RCC_GPIOF_CLK_ENABLE();
//#endif
//#ifdef __HAL_RCC_GPIOG_CLK_ENABLE
//  __HAL_RCC_GPIOG_CLK_ENABLE();
//#endif
//  __HAL_RCC_GPIOH_CLK_ENABLE();
//#ifdef __HAL_RCC_GPIOI_CLK_ENABLE
//  __HAL_RCC_GPIOI_CLK_ENABLE();
//#endif
//#ifdef __HAL_RCC_GPIOJ_CLK_ENABLE
//  __HAL_RCC_GPIOJ_CLK_ENABLE();
//#endif

//  for (uint8_t i = 0; i < TU_ARRAY_SIZE(board_pindef); i++) {
//    HAL_GPIO_Init(board_pindef[i].port, &board_pindef[i].pin_init);
//  }

//#if CFG_TUSB_OS == OPT_OS_NONE
//  // 1ms tick timer
//  SysTick_Config(SystemCoreClock / 1000);
//#elif CFG_TUSB_OS == OPT_OS_FREERTOS
//  // Explicitly disable systick to prevent its ISR runs before scheduler start
//  SysTick->CTRL &= ~1U;
//
//  // If freeRTOS is used, IRQ priority is limit by max syscall ( smaller is higher )
//  NVIC_SetPriority(OTG_FS_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );
//#endif

  board_led_write(false);


//  //------------- USB FS -------------//
//  GPIO_InitTypeDef GPIO_InitStruct;
//
//  /* Configure USB D+ D- Pins */
//  GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
//  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  /* Configure VBUS Pin */
//  GPIO_InitStruct.Pin = GPIO_PIN_9;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  /* ID Pin */
//  GPIO_InitStruct.Pin = GPIO_PIN_10;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  // Enable USB OTG clock
//  __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

#if CFG_TUD_ENABLED
//  board_vbus_sense_init(BOARD_TUD_RHPORT);
#endif

#if CFG_TUH_ENABLED
  board_vbus_set(BOARD_TUD_RHPORT, true);
#endif
}

//--------------------------------------------------------------------+
// Board porting API
//--------------------------------------------------------------------+

// Get USB Serial number string from unique ID if available. Return number of character.
// Input is string descriptor from index 1 (index 0 is type + len)
size_t myboard_usb_get_serial(uint16_t desc_str1[], size_t max_chars) {
  uint8_t uid[16] TU_ATTR_ALIGNED(4);
  size_t uid_len;

  if ( 1 ) {
    uid_len = board_get_unique_id(uid, sizeof(uid));
  }else {
    // fixed serial string is 01234567889ABCDEF
    uint32_t* uid32 = (uint32_t*) (uintptr_t) uid;
    uid32[0] = 0x67452301;
    uid32[1] = 0xEFCDAB89;
    uid_len = 8;
  }

  if ( uid_len > max_chars / 2 ) uid_len = max_chars / 2;

  for ( size_t i = 0; i < uid_len; i++ ) {
    for ( size_t j = 0; j < 2; j++ ) {
      const char nibble_to_hex[16] = {
          '0', '1', '2', '3', '4', '5', '6', '7',
          '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
      };
      uint8_t const nibble = (uid[i] >> (j * 4)) & 0xf;
      desc_str1[i * 2 + (1 - j)] = nibble_to_hex[nibble]; // UTF-16-LE
    }
  }

  return 2 * uid_len;
}

void board_led_write(bool state) {
#ifdef PINID_LED
  board_pindef_t* pindef = &board_pindef[PINID_LED];
  GPIO_PinState pin_state = state == pindef->active_state ? GPIO_PIN_SET : GPIO_PIN_RESET;
  HAL_GPIO_WritePin(pindef->port, pindef->pin_init.Pin, pin_state);
#else
  static GPIO_PinState last_pin_state = GPIO_PIN_RESET;
  GPIO_PinState pin_state = state == last_pin_state ? GPIO_PIN_SET : GPIO_PIN_RESET;
  HAL_GPIO_WritePin(UserLED_GPIO_Port, UserLED_Pin, pin_state);
#endif
}

uint32_t board_button_read(void) {
#ifdef PINID_BUTTON
  board_pindef_t* pindef = &board_pindef[PINID_BUTTON];
  return pindef->active_state == HAL_GPIO_ReadPin(pindef->port, pindef->pin_init.Pin);
#else
  return HAL_GPIO_ReadPin(UserBTN_GPIO_Port, UserBTN_Pin);
#endif
}

size_t board_get_unique_id(uint8_t id[], size_t max_len) {
  (void) max_len;
  volatile uint32_t *stm32_uuid = (volatile uint32_t *) UID_BASE;
  uint32_t *id32 = (uint32_t *) (uintptr_t) id;
  uint8_t const len = 12;

  id32[0] = stm32_uuid[0];
  id32[1] = stm32_uuid[1];
  id32[2] = stm32_uuid[2];

  return len;
}

#if CFG_TUSB_OS == OPT_OS_NONE
volatile uint32_t system_ticks = 0;

void SysTick_Handler(void) {
  HAL_IncTick();
  system_ticks++;
}

uint32_t board_millis(void) {
  return system_ticks;
}

#endif

void HardFault_Handler(void) {
  __asm("BKPT #0\n");
}





