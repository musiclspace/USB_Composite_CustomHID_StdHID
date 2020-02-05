/***************************************************************************************
 * All Rights Reserved
 * STM32 UserLib
 ***************************************************************************************
 * @File    user_usb_composite.c
 *
 * @Author  Solen Liu <solen.pico@gmail.com>
 *
 * @Brief   CustomHID and Standard HID
 *          
 * @Date    2019/12/27  
 *
 ***************************************************************************************/
#include "user_usb_composite.h"

static USBD_CUSTOM_HID_HandleTypeDef *pCustomHID_ClassData;
//static USBD_HID_HandleTypeDef *pStdHID_ClassData;
extern USBD_HandleTypeDef hUsbDeviceFS;


/* USB CUSTOM_HID device FS Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_Composite_CfgFSDesc[USB_CUSTOM_HID_CONFIG_DESC_SIZ] __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_CUSTOM_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xC0,         /*bmAttributes: bus powered */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

  /************** Descriptor of CUSTOM HID interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x02,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: CUSTOM_HID*/
  0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of CUSTOM_HID *************************/
  /* 18 */
  0x09,         /*bLength: CUSTOM_HID Descriptor size*/
  CUSTOM_HID_DESCRIPTOR_TYPE, /*bDescriptorType: CUSTOM_HID*/
  0x11,         /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  USBD_CUSTOM_HID_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Custom HID endpoints ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  CUSTOM_HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  CUSTOM_HID_EPIN_SIZE, /*wMaxPacketSize: 2 Byte max */
  0x00,
  CUSTOM_HID_FS_BINTERVAL,          /*bInterval: Polling Interval */
  /* 34 */

  0x07,          /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT, /* bDescriptorType: */
  CUSTOM_HID_EPOUT_ADDR,  /*bEndpointAddress: Endpoint Address (OUT)*/
  0x03, /* bmAttributes: Interrupt endpoint */
  CUSTOM_HID_EPOUT_SIZE,  /* wMaxPacketSize: 2 Bytes max  */
  0x00,
  CUSTOM_HID_FS_BINTERVAL,  /* bInterval: Polling Interval */
  /* 41 */
};



/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_Composite_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END=
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

USBD_ClassTypeDef  USBD_COMPOSITE =
{
  USBD_Composite_Init,
  USBD_Composite_DeInit,
  USBD_Composite_Setup,
  NULL,/*USBD_Composite_EP0_TxReady*/
  USBD_Composite_EP0_RxReady,
  USBD_Composite_DataIn,
  USBD_Composite_DataOut,
  NULL,/*USBD_Composite_SOF*/
  NULL,/*USBD_Composite_IsoINIncomplete*/
  NULL,/*USBD_Composite_IsoOutIncomplete*/
  USBD_Composite_GetFSCfgDesc,
  USBD_Composite_GetFSCfgDesc,
  USBD_Composite_GetFSCfgDesc,
  USBD_Composite_GetDeviceQualifierDescriptor
};

static uint8_t  USBD_Composite_Init (USBD_HandleTypeDef *pdev,uint8_t cfgidx)
{
    uint8_t ret = 0;
    pdev->pUserData =  &USBD_CustomHID_fops_FS;
    ret +=  USBD_CUSTOM_HID.Init(pdev,cfgidx);
    pCustomHID_ClassData = pdev->pClassData;
    
//    ret +=  USBD_HID.Init(pdev,cfgidx);
//    pStdHID_ClassData = pdev->pClassData;
    return ret;
}
static uint8_t  USBD_Composite_DeInit (USBD_HandleTypeDef *pdev,uint8_t cfgidx)
{
    uint8_t ret = 0;
    pdev->pClassData = pCustomHID_ClassData;
    pdev->pUserData = &USBD_CustomHID_fops_FS;
    ret +=  USBD_CUSTOM_HID.DeInit(pdev,cfgidx);
    
//    pdev->pClassData = pStdHID_ClassData;
//    pdev->pUserData = NULL;
//    ret +=  USBD_HID.DeInit(pdev,cfgidx);
    return ret;
}
/**
  * @brief  USBD_Composite_EP0_RxReady 
  */
static uint8_t  USBD_Composite_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
    uint8_t ret = 0;
    pdev->pClassData = pCustomHID_ClassData;
    pdev->pUserData = &USBD_CustomHID_fops_FS;
    ret += USBD_CUSTOM_HID.EP0_RxReady(pdev);
    return ret;
}
/**
  * @brief  USBD_Composite_Setup 
  */
static uint8_t  USBD_Composite_Setup (USBD_HandleTypeDef *pdev,USBD_SetupReqTypedef *req)
{
    uint8_t ret = 0;
    if(req->wIndex == 0)  //Interface 0: Custom HID
    {
        pdev->pClassData = pCustomHID_ClassData;
        pdev->pUserData = &USBD_CustomHID_fops_FS;
        ret = USBD_CUSTOM_HID.Setup(pdev,req);
    }
    else
    {
//        pdev->pClassData = pStdHID_ClassData;
//        pdev->pUserData = NULL;
//        ret = USBD_HID.Setup(pdev,req);
    }
    return ret;
}
/**
  * @brief  USBD_Composite_DataIn 
  */
static uint8_t  USBD_Composite_DataIn (USBD_HandleTypeDef *pdev,uint8_t epnum)
{
    uint8_t ret = 0;
//    if(epnum == (CUSTOM_HID_EPIN_ADDR & 0x0F))
//    {
        pdev->pClassData = pCustomHID_ClassData;
        pdev->pUserData = &USBD_CustomHID_fops_FS;
        ret += USBD_CUSTOM_HID.DataIn(pdev,epnum);
//    }
//    else
//    {
//        pdev->pClassData = pStdHID_ClassData;
//        pdev->pUserData = NULL;
//        ret += USBD_HID.DataIn(pdev,epnum);
//    }
    return ret;
}
/**
  * @brief  USBD_Composite_DataOut / Only CustomHID
  */
static uint8_t  USBD_Composite_DataOut (USBD_HandleTypeDef *pdev,uint8_t epnum)
{
    uint8_t ret = 0;
//    if(epnum == (CUSTOM_HID_EPIN_ADDR & 0x0F))
    {
        pdev->pClassData = pCustomHID_ClassData;
        pdev->pUserData = &USBD_CustomHID_fops_FS;
        ret += USBD_CUSTOM_HID.DataOut(pdev,epnum);
    }
    return ret;
}
static uint8_t  *USBD_Composite_GetFSCfgDesc (uint16_t *length)
{
    *length = sizeof(USBD_Composite_CfgFSDesc);
    return USBD_Composite_CfgFSDesc;
}
static uint8_t  *USBD_Composite_GetDeviceQualifierDescriptor (uint16_t *length)
{
    *length = sizeof (USBD_Composite_DeviceQualifierDesc);
    return USBD_Composite_DeviceQualifierDesc;
}


void USBD_Composite_DEVICE_Init(void)
{
    USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);
    USBD_RegisterClass(&hUsbDeviceFS, &USBD_COMPOSITE);
    //USBD_RegisterClass(&hUsbDeviceFS, &USBD_CUSTOM_HID);
    //USBD_CUSTOM_HID_RegisterInterface(&hUsbDeviceFS, &USBD_CustomHID_fops_FS);
    USBD_Start(&hUsbDeviceFS);
  
}
