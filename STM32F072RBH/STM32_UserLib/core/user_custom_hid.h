/****************************************************************************************
 * All Rights Reserved
 * STM32 UserLib
 ****************************************************************************************
 * @File    user_custom_hid.h
 *
 * @Author  Solen Liu
 *
 * @Brief   user_custom_hid
 *
 * @Date    2020/01/02  
 *
 *****************************************************************************************/
#ifndef USER_HID_H
#define USER_HID_H
#include "usb_device.h"
#include "usbd_conf.h"
void user_custom_hid_send(uint8_t *pdata);
void user_custom_hid_outevent_callback(uint8_t *pdata);
#endif
