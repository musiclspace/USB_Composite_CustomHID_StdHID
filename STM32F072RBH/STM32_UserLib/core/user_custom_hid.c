/****************************************************************************************
 * All Rights Reserved
 * STM32 UserLib
 ****************************************************************************************
 * @File    user_custom_hid.c
 *
 * @Author  Solen Liu
 *
 * @Brief   user_custom_hid
 *
 * @Date    2020/01/02  
 *
 *****************************************************************************************/
#include "usbd_customhid.h"
#include "user_custom_hid.h"
#include "user_log.h"
extern USBD_HandleTypeDef hUsbDeviceFS;
/**
  * @brief  user_custom_hid_send
  */
void user_custom_hid_send(uint8_t *pdata)
{
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,pdata,USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
}
/**
  * @brief  Call this API in  usbd_custom_hid_if.c / CUSTOM_HID_OutEvent_FS 
  */
void user_custom_hid_outevent_callback(uint8_t *pdata)
{
    //Debug Log
    for(int i = 0; i < USBD_CUSTOMHID_OUTREPORT_BUF_SIZE; i++)
    {
        pr_info("0x%x ",pdata[i]);
    }
}



