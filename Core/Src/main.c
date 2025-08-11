/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "bsp/board_api.h"
#include "tusb.h"

#include "tusb_config.h"
#include "tusb_family.h"
#include "usb_descriptors.h"
#include <ctype.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */
char text[64] = "Muhammad Fikri Rizal Al - Amin";
uint8_t const conv_table[128][2] =  { HID_ASCII_TO_KEYCODE };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum {
	BLINK_NOT_MOUNTED = 250, BLINK_MOUNTED = 1000, BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

static void led_blinking_task(void);
static void cdc_task(void);
void hid_task(void);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */
	board_led_write(false);
	tusb_rhport_init_t dev_init = {
			.role = TUSB_ROLE_DEVICE,
			.speed = TUSB_SPEED_AUTO };
	tusb_init(BOARD_TUD_RHPORT, &dev_init);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		tud_task(); // tinyusb device task
		cdc_task();
		hid_task();
		led_blinking_task();
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(UserLED_GPIO_Port, UserLED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : UserBTN_Pin */
  GPIO_InitStruct.Pin = UserBTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(UserBTN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : UserLED_Pin */
  GPIO_InitStruct.Pin = UserLED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(UserLED_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// echo to either Serial0 or Serial1
// with Serial0 as all lower case, Serial1 as all upper case
static void echo_serial_port(uint8_t itf, uint8_t buf[], uint32_t count) {
	uint8_t const case_diff = 'a' - 'A';

	for (uint32_t i = 0; i < count; i++) {
		if (itf == 0) {
			// echo back 1st port as lower case
			if (isupper(buf[i]))
				buf[i] += case_diff;
		} else {
			// echo back 2nd port as upper case
			if (islower(buf[i]))
				buf[i] -= case_diff;
		}

		tud_cdc_n_write_char(itf, buf[i]);
	}
	tud_cdc_n_write_flush(itf);
}

// Invoked when device is mounted
void tud_mount_cb(void) {
	blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
	blink_interval_ms = BLINK_NOT_MOUNTED;
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
static void cdc_task(void) {
//	for (uint8_t itf = 0; itf < CFG_TUD_CDC; itf++) {
		// connected() check for DTR bit
		// Most but not all terminal client set this when making connection
//		 if ( tud_cdc_n_connected(ITF_NUM_CDC_0) )
		{
			if (tud_cdc_n_available(0)) {
				uint8_t buf[64];
				uint32_t count = tud_cdc_n_read(0, buf, sizeof(buf));

				// echo back to both serial ports
				echo_serial_port(0, buf, count);
//				echo_serial_port(1, buf, count);
			}

			// Press on-board button to send Uart status notification
			static uint32_t btn_prev = 0;
			static cdc_notify_uart_state_t uart_state = { .value = 0 };
			const uint32_t btn = board_button_read();
			if (!btn_prev && btn) {
				uart_state.dsr ^= 1;
				tud_cdc_notify_uart_state(&uart_state);
			}
			btn_prev = btn;
		}
//	}
}

// Invoked when cdc when line state changed e.g connected/disconnected
// Use to reset to DFU when disconnect with 1200 bps
void tud_cdc_line_state_cb(uint8_t instance, bool dtr, bool rts) {
	(void) rts;
	(void) instance;
	(void) dtr;

//	// DTR = false is counted as disconnected
//	if (!dtr) {
//		// touch1200 only with first CDC instance (Serial)
//		if (instance == 0) {
//			cdc_line_coding_t coding;
//			tud_cdc_get_line_coding(&coding);
//			if (coding.bit_rate == 1200) {
//				if (board_reset_to_bootloader) {
//					board_reset_to_bootloader();
//				}
//			}
//		}
//	}
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void) {
	// Poll every 10ms
	const uint32_t interval_ms = 1;
	static uint32_t start_ms = 0;

	if (board_millis() - start_ms < interval_ms)
		return; // not enough time
	start_ms += interval_ms;

	uint32_t const btn = board_button_read();
//  uint8_t debug = tud_hid_n_ready(ITF_NUM_KEYBOARD);

	if (tud_suspended() && btn) {
		// Wake up host if we are in suspend mode
		// and REMOTE_WAKEUP feature is enabled by host
		tud_remote_wakeup();
	} else {
		// keyboard interface
		if (tud_hid_n_ready(0)) {
			// used to avoid send multiple consecutive zero report for keyboard
			static bool has_keyboard_key = false;
			static bool typing = false;
			static uint32_t index = 0;
			static uint32_t textLen = 0;

			uint8_t const report_id = 0;
			uint8_t modifier = 0;
			uint8_t empty_key[6] = {0};
			uint8_t keycode[6] = { 0 };

//			if (btn) {
//
//				keycode[0] = HID_KEY_ARROW_RIGHT;
//
//				tud_hid_n_keyboard_report(0, report_id, modifier, keycode);
//				has_keyboard_key = true;
//			} else {
//				// send empty key report if previously has key pressed
//				if (has_keyboard_key)
//					tud_hid_n_keyboard_report(0, report_id, modifier,
//					NULL);
//				has_keyboard_key = false;
//			}

			if (btn) {
				typing = true;
				textLen = strlen(text);
			}

			if (typing) {
				if (has_keyboard_key) {
					modifier = 0;
					tud_hid_n_keyboard_report(ITF_NUM_KEYBOARD, report_id, modifier,
							empty_key);
					has_keyboard_key = false;
				} else {
					modifier = 0;
					uint8_t chr = text[index];

					if ( conv_table[chr][0] ) modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
					keycode[0] = conv_table[chr][1];
					tud_hid_n_keyboard_report(ITF_NUM_KEYBOARD, report_id, modifier, keycode);
					has_keyboard_key = true;
					index++;
					if (index >= textLen) {
						typing = false;
						index = 0;
					}
				}
			} else {
				if (has_keyboard_key) {
					modifier = 0;
					tud_hid_n_keyboard_report(ITF_NUM_KEYBOARD, report_id, modifier,
							empty_key);
				}
				has_keyboard_key = false;
			}
		}
	}
}

// Invoked when received SET_PROTOCOL request
// protocol is either HID_PROTOCOL_BOOT (0) or HID_PROTOCOL_REPORT (1)
void tud_hid_set_protocol_cb(uint8_t instance, uint8_t protocol)
{
  (void) instance;
  (void) protocol;

  // nothing to do since we use the same compatible boot report for both Boot and Report mode.
  // TODO set a indicator for user
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) instance;
  (void) report;
  (void) len;

  // nothing to do
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) report_id;

  // keyboard interface
//  if (instance == ITF_NUM_KEYBOARD)
	  if (instance == 0)
  {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
      // bufsize should be (at least) 1
      if ( bufsize < 1 ) return;

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
      {
        // Capslock On: disable blink, turn led on
        blink_interval_ms = 0;
        board_led_write(true);
      }else
      {
        // Caplocks Off: back to normal blink
        board_led_write(false);
        blink_interval_ms = BLINK_MOUNTED;
      }
    }
  }
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void) {
	static uint32_t start_ms = 0;
	static bool led_state = false;

	// Blink every interval ms
	if (board_millis() - start_ms < blink_interval_ms)
		return; // not enough time
	start_ms += blink_interval_ms;

	board_led_write(led_state);
	led_state = 1 - led_state; // toggle
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
