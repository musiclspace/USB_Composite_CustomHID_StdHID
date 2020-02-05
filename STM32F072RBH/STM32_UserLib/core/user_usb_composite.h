/***************************************************************************************
 * All Rights Reserved
 * STM32 UserLib
 ***************************************************************************************
 * @File    user_usb_composite.h
 *
 * @Author  Solen Liu <solen.pico@gmail.com>
 *
 * @Brief   Custom HID and Standard HID Composite
 *          
 * @Date    2019/12/27  
 *
 ***************************************************************************************/
#ifndef __USER_USB_COMPOSITE_H
#define __USER_USB_COMPOSITE_H 	   
#include "user_config.h"


#include "usbd_customhid.h"
#include "usbd_custom_hid_if.h"
#include "usbd_hid.h"
#include "usbd_desc.h"

static uint8_t  USBD_Composite_Init (USBD_HandleTypeDef *pdev,uint8_t cfgidx);
static uint8_t  USBD_Composite_DeInit (USBD_HandleTypeDef *pdev,uint8_t cfgidx);
//static uint8_t  USBD_Composite_EP0_TxReady(USBD_HandleTypeDef *pdev);
static uint8_t  USBD_Composite_EP0_RxReady(USBD_HandleTypeDef *pdev);
static uint8_t  USBD_Composite_Setup (USBD_HandleTypeDef *pdev,USBD_SetupReqTypedef *req);
static uint8_t  USBD_Composite_DataIn (USBD_HandleTypeDef *pdev,uint8_t epnum);
static uint8_t  USBD_Composite_DataOut (USBD_HandleTypeDef *pdev,uint8_t epnum);
//static uint8_t  USBD_Composite_SOF(USBD_HandleTypeDef *pdev);
//static uint8_t  USBD_Composite_IsoINIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);
//static uint8_t  USBD_Composite_IsoOutIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t  *USBD_Composite_GetFSCfgDesc (uint16_t *length);
static uint8_t  *USBD_Composite_GetDeviceQualifierDescriptor (uint16_t *length);

void USBD_Composite_DEVICE_Init(void);
#endif
