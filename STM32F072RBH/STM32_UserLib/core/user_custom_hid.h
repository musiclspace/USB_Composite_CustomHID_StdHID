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

#define HID_DESC_IN  0x81
#define HID_DESC_OUT 0x91

#define CUSTOM_HID_ReportDesc_Module(ReportID, Direction) 0x85,ReportID,   /* REPORT ID */          \
                                                          0x09,ReportID+1, /* USAGE */              \
                                                          0x15,0x00,       /* LOGICAL_MINIMUM(0)*/  \
                                                          0x26,0xff,0x00,  /* LOGICAL_MAXIMUM(255)*/\
                                                          0x75,0x08,       /* REPORT SIZE(8) 8BIT*/ \
                                                          0x95,0x3F,       /* REPORT COUNT(63)8BIT*/\
                                                          0xb1,0x82,       /* FEATURE(Data,Var,Abs,Vol)*/\
                                                          0x85,ReportID,   /* REPORT ID */          \
                                                          0x09,ReportID+1, /* USAGE */              \
                                                          Direction,0x82   /* IN OUT(Data,Var,Abs,Vol)*/  





#endif
