/*
Copyright (c) 2014-2015 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// Include guard
#pragma once

//================================================================================
// Settings
//================================================================================

//#define LAYOUT_US_ENGLISH
//#define LAYOUT_CANADIAN_FRENCH
//#define LAYOUT_CANADIAN_MULTILINGUAL
//#define LAYOUT_DANISH
//#define LAYOUT_FINNISH
//#define LAYOUT_FRENCH
//#define LAYOUT_FRENCH_BELGIAN
//#define LAYOUT_FRENCH_SWISS
//#define LAYOUT_GERMAN
//#define LAYOUT_GERMAN_MAC
//#define LAYOUT_GERMAN_SWISS
//#define LAYOUT_ICELANDIC
//#define LAYOUT_IRISH
//#define LAYOUT_ITALIAN
//#define LAYOUT_NORWEGIAN
//#define LAYOUT_PORTUGUESE
//#define LAYOUT_PORTUGUESE_BRAZILIAN
//#define LAYOUT_SPANISH
//#define LAYOUT_SPANISH_LATIN_AMERICA
//#define LAYOUT_SWEDISH
//#define LAYOUT_TURKISH
//#define LAYOUT_UNITED_KINGDOM
//#define LAYOUT_US_INTERNATIONAL

//================================================================================
// Definitions and Helpers
//================================================================================

// Default US keyboard layout
#if !defined(LAYOUT_CANADIAN_FRENCH) && !defined(LAYOUT_CANADIAN_MULTILINGUAL) \
&& !defined(LAYOUT_DANISH) && !defined(LAYOUT_FINNISH) && !defined(LAYOUT_FRENCH) \
&& !defined(LAYOUT_FRENCH_BELGIAN) && !defined(LAYOUT_FRENCH_SWISS) && !defined(LAYOUT_GERMAN) \
&& !defined(LAYOUT_GERMAN_MAC) && !defined(LAYOUT_GERMAN_SWISS) && !defined(LAYOUT_ICELANDIC) \
&& !defined(LAYOUT_IRISH) && !defined(LAYOUT_ITALIAN) && !defined(LAYOUT_NORWEGIAN) \
&& !defined(LAYOUT_PORTUGUESE) && !defined(LAYOUT_PORTUGUESE_BRAZILIAN) \
&& !defined(LAYOUT_SPANISH) && !defined(LAYOUT_SPANISH_LATIN_AMERICA) \
&& !defined(LAYOUT_SWEDISH) && !defined(LAYOUT_TURKISH) && !defined(LAYOUT_UNITED_KINGDOM) \
&& !defined(LAYOUT_US_INTERNATIONAL) && !defined(LAYOUT_US_ENGLISH)
#define LAYOUT_US_ENGLISH
#endif

#define HID_REPORTID_NONE 0

#ifndef HID_REPORTID_MOUSE
#define HID_REPORTID_MOUSE 1
#endif

#ifndef HID_REPORTID_KEYBOARD
#define HID_REPORTID_KEYBOARD 2
#endif

#ifndef HID_REPORTID_RAWHID
// This will not work properly in most cases.
// The number is just kept from the old number counting.
//#define HID_REPORTID_RAWHID 3
#endif

#ifndef HID_REPORTID_CONSUMERCONTROL
#define HID_REPORTID_CONSUMERCONTROL 4
#endif

#ifndef HID_REPORTID_SYSTEMCONTROL
#define HID_REPORTID_SYSTEMCONTROL 5
#endif

#ifndef HID_REPORTID_GAMEPAD
#define HID_REPORTID_GAMEPAD 6
#endif

#ifndef HID_REPORTID_MOUSE_ABSOLUTE
#define HID_REPORTID_MOUSE_ABSOLUTE 7
#endif

#ifndef HID_REPORTID_NKRO_KEYBOARD
#define HID_REPORTID_NKRO_KEYBOARD 8
#endif

#ifndef HID_REPORTID_TEENSY_KEYBOARD
#define HID_REPORTID_TEENSY_KEYBOARD 9
#endif

#ifndef HID_REPORTID_SURFACEDIAL
#define HID_REPORTID_SURFACEDIAL 10
#endif

#if defined(ARDUINO_ARCH_AVR)

#include "PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE		uint8_t
#define EP_TYPE_BULK_IN_MIDI 		EP_TYPE_BULK_IN
#define EP_TYPE_BULK_OUT_MIDI 		EP_TYPE_BULK_OUT
#define is_write_enabled(x)			(1)

#elif defined(ARDUINO_ARCH_SAM)

#include "USB/PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE		uint32_t
#define EP_TYPE_INTERRUPT_IN		(UOTGHS_DEVEPTCFG_EPSIZE_512_BYTE | \
									UOTGHS_DEVEPTCFG_EPDIR_IN |         \
									UOTGHS_DEVEPTCFG_EPTYPE_BLK |       \
									UOTGHS_DEVEPTCFG_EPBK_1_BANK |      \
									UOTGHS_DEVEPTCFG_NBTRANS_1_TRANS |  \
									UOTGHS_DEVEPTCFG_ALLOC)
#define EP_TYPE_INTERRUPT_OUT       (UOTGHS_DEVEPTCFG_EPSIZE_512_BYTE | \
									UOTGHS_DEVEPTCFG_EPTYPE_BLK |       \
									UOTGHS_DEVEPTCFG_EPBK_1_BANK |      \
									UOTGHS_DEVEPTCFG_NBTRANS_1_TRANS |  \
									UOTGHS_DEVEPTCFG_ALLOC)
#define USB_EP_SIZE					EPX_SIZE
#define USB_SendControl				USBD_SendControl
#define USB_Available				USBD_Available
#define USB_Recv					USBD_Recv
#define USB_Send					USBD_Send
#define USB_Flush					USBD_Flush
#define is_write_enabled(x)			Is_udd_write_enabled(x)

#elif defined(ARDUINO_ARCH_SAMD)

#include "USB/PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE		uint32_t
#define EP_TYPE_INTERRUPT_IN 		USB_ENDPOINT_TYPE_INTERRUPT | USB_ENDPOINT_IN(0);
#define EP_TYPE_INTERRUPT_OUT 		USB_ENDPOINT_TYPE_INTERRUPT | USB_ENDPOINT_OUT(0);
#define USB_EP_SIZE					EPX_SIZE
//#define USB_SendControl 			USBDevice.sendControl
#define USB_Available				USBDevice.available
#define USB_Recv					USBDevice.recv
#define USB_RecvControl				USBDevice.recvControl
#define USB_Send					USBDevice.send
#define USB_Flush					USBDevice.flush
#define is_write_enabled(x)			(1)

int USB_SendControl(void* y, uint8_t z);
int USB_SendControl(uint8_t x, const void* y, uint8_t z);

#define TRANSFER_PGM		0
#define TRANSFER_RELEASE	0xFF

#define HID_REPORT_TYPE_INPUT   1
#define HID_REPORT_TYPE_OUTPUT  2
#define HID_REPORT_TYPE_FEATURE 3

#else

#error "Unsupported architecture"

#endif