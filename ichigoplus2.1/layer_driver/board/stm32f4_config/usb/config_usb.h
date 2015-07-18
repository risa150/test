#ifndef CONFIG_USB_H
#define CONFIG_USB_H


#define HSE_VALUE ((uint32_t)8000000) /* STM32 discovery uses a 8Mhz external crystal */

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usb_dcd_int.h"

/*
 * The USB data must be 4 byte aligned if DMA is enabled. This macro handles
 * the alignment, if necessary (it's actually magic, but don't tell anyone).
 */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;




void OTG_FS_IRQHandler(void);
void OTG_FS_WKUP_IRQHandler(void);

void usb_put_char(char c);
void Init_usb(void);
void ColorfulRingOfDeath(void);

//void usb_put_char(char c);
//Discovery���microUSB�Ɉꕶ�����M���s��

//void Init_usb(void);
//Discovery���microUSB�̐ݒ�

//void ColorfulRingOfDeath(void);
//LED�߂�����Ђ����Ă߂����Ⴋ�ꂢ�I�I�I�I�@��while(1)�������Ă邱�Ƃɒ���

#define BUFFER_LENGTH 1024
int usb_available();
void usb_get_string(char *str);

#endif
