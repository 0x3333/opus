/**
 *      ____
 *     / __ \____  __  _______
 *    / / / / __ \/ / / / ___/
 *   / /_/ / /_/ / /_/ (__  )
 *   \____/ .___/\__,_/____/
 *       /_/         Framework
 *   Copyright (C) 2019 Tercio Gaudencio Filho.
 *
 *   This file is part of Opus Framework.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
// =================================================================================================
// Includes
// =================================================================================================

// Opus
#include "usbcdc.h"

#ifdef OP_USB_SERIAL

// =================================================================================================
// Definitions
// =================================================================================================

// Endpoints
#define USBD1_DATA_REQUEST_EP /*       */ 1
#define USBD1_DATA_AVAILABLE_EP /*     */ 1
#define USBD1_INTERRUPT_REQUEST_EP /*  */ 2

// =================================================================================================
// External Declarations
// =================================================================================================

// =================================================================================================
// Exported Variables
// =================================================================================================

SerialUSBDriver SDU1;

// =================================================================================================
// Local Variables / Types
// =================================================================================================

static const USBDescriptor *get_descriptor(USBDriver *usbp, uint8_t dtype, uint8_t dindex, uint16_t lang);
static void usb_event(USBDriver *usbp, usbevent_t event);
static void sof_handler(USBDriver *usbp);

// USB Device Descriptor
static const uint8_t cdc_device_descriptor_data[18] = {
    USB_DESC_DEVICE(0x0110, // + bcdUSB (1.1).
                    0x02,   // + bDeviceClass (CDC).
                    0x00,   // + bDeviceSubClass.
                    0x00,   // + bDeviceProtocol.
                    0x40,   // + bMaxPacketSize.
                    0x0483, // + idVendor (ST).
                    0x5740, // + idProduct.
                    0x0200, // + bcdDevice.
                    1,      // + iManufacturer.
                    2,      // + iProduct.
                    3,      // + iSerialNumber.
                    1)      // + bNumConfigurations.
};

// Configuration Descriptor tree for a CDC
static const uint8_t cdc_configuration_descriptor_data[67] = {
    // Configuration Descriptor
    USB_DESC_CONFIGURATION(67,   // + wTotalLength
                           0x02, // + bNumInterfaces
                           0x01, // + bConfigurationValue
                           0,    // + iConfiguration
                           0xC0, // + bmAttributes (self powered)
                           50),  // + bMaxPower (100mA)

    // Interface Descriptor
    USB_DESC_INTERFACE(0x00, // + bInterfaceNumber
                       0x00, // + bAlternateSetting
                       0x01, // + bNumEndpoints
                       0x02, // + bInterfaceClass (Communications Interface Class, CDC section 4.2)
                       0x02, // + bInterfaceSubClass (Abstract Control Model, CDC section 4.3)
                       0x01, // + bInterfaceProtocol (AT commands, CDC section 4.4)
                       0),   // + iInterface

    // Header Functional Descriptor (CDC section 5.2.3)
    USB_DESC_BYTE(5),     // + bLength
    USB_DESC_BYTE(0x24),  // + bDescriptorType (CS_INTERFACE)
    USB_DESC_BYTE(0x00),  // + bDescriptorSubtype (Header Functional Descriptor
    USB_DESC_BCD(0x0110), // + bcdCDC

    // Call Management Functional Descriptor
    USB_DESC_BYTE(5),    // + bFunctionLength
    USB_DESC_BYTE(0x24), // + bDescriptorType (CS_INTERFACE)
    USB_DESC_BYTE(0x01), // + bDescriptorSubtype (Call Management Functional Descriptor)
    USB_DESC_BYTE(0x00), // + bmCapabilities (D0+D1)
    USB_DESC_BYTE(0x01), // + bDataInterface

    // ACM Functional Descriptor
    USB_DESC_BYTE(4),    // + bFunctionLength
    USB_DESC_BYTE(0x24), // + bDescriptorType (CS_INTERFACE)
    USB_DESC_BYTE(0x02), // + bDescriptorSubtype (Abstract Control Management Descriptor)
    USB_DESC_BYTE(0x02), // + bmCapabilities

    // Union Functional Descriptor.
    USB_DESC_BYTE(5),    // + bFunctionLength
    USB_DESC_BYTE(0x24), // + bDescriptorType (CS_INTERFACE)
    USB_DESC_BYTE(0x06), // + bDescriptorSubtype (Union Functional Descriptor)
    USB_DESC_BYTE(0x00), // + bMasterInterface (Communication Class Interface)
    USB_DESC_BYTE(0x01), // + bSlaveInterface0 (Data Class Interface)

    // Endpoint 2 Descriptor
    USB_DESC_ENDPOINT(USBD1_INTERRUPT_REQUEST_EP | 0x80, // + bEndpointAddress
                      0x03,                              // + bmAttributes (Interrupt)
                      0x0008,                            // + wMaxPacketSize
                      0xFF),                             // + bInterval

    // Interface Descriptor
    USB_DESC_INTERFACE(0x01,  // + bInterfaceNumber
                       0x00,  // + bAlternateSetting
                       0x02,  // + bNumEndpoints
                       0x0A,  // + bInterfaceClass (Data Class Interface, CDC section 4.5)
                       0x00,  // + bInterfaceSubClass (CDC section 4.6)
                       0x00,  // + bInterfaceProtocol (CDC section 4.7)
                       0x00), // + iInterface

    // Endpoint 3 Descriptor
    USB_DESC_ENDPOINT(USBD1_DATA_AVAILABLE_EP, // + bEndpointAddress
                      0x02,                    // + bmAttributes (Bulk)
                      0x0040,                  // + wMaxPacketSize
                      0x00),                   // + bInterval

    // Endpoint 1 Descriptor
    USB_DESC_ENDPOINT(USBD1_DATA_REQUEST_EP | 0x80, // + bEndpointAddress
                      0x02,                         // + bmAttributes (Bulk)
                      0x0040,                       // + wMaxPacketSize
                      0x00)                         // + bInterval
};

// U.S. English language identifier
static const uint8_t cdc_string0[] = {
    USB_DESC_BYTE(4),                     // + bLength
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), // + bDescriptorType
    USB_DESC_WORD(0x0409)                 // + wLANGID (U.S. English)
};

// Vendor string
static const uint8_t cdc_string1[] = {
    USB_DESC_BYTE(56),                    // + bLength
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), // + bDescriptorType
    // Opus - FreeRTOS/ChibiOS HAL
    'O', 0, 'p', 0, 'u', 0, 's', 0, ' ', 0, '-', 0, ' ', 0, 'F', 0, 'r', 0, 'e', 0, 'e', 0,
    'R', 0, 'T', 0, 'O', 0, 'S', 0, '/', 0, 'C', 0, 'h', 0, 'i', 0, 'b', 0, 'i', 0, 'o', 0,
    's', 0, ' ', 0, 'H', 0, 'A', 0, 'L', 0};

// Device Description string
static const uint8_t cdc_string2[] = {
    USB_DESC_BYTE(44),                    // + bLength
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), // + bDescriptorType
    // Opus Virtual COM Port
    'O', 0, 'p', 0, 'u', 0, 's', 0, ' ', 0,
    'V', 0, 'i', 0, 'r', 0, 't', 0, 'u', 0, 'a', 0, 'l', 0, ' ', 0,
    'C', 0, 'O', 0, 'M', 0, ' ', 0, 'P', 0, 'o', 0, 'r', 0, 't', 0};

static const uint8_t cdc_string3[] = {
    USB_DESC_BYTE(24),                    /* bLength */
    USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType */
    '0' + OP_APP_MAJOR, 0,
    '.', 0,
    '0' + OP_APP_MINOR, 0,
    '.', 0,
    '0' + OP_APP_PATCH, 0,
    '-', 0,
    OP_SERIAL_NUMBER};

// Device Descriptor wrapper
static const USBDescriptor cdc_device_descriptor = {
    sizeof cdc_device_descriptor_data,
    cdc_device_descriptor_data};

// Configuration Descriptor wrapper
static const USBDescriptor cdc_configuration_descriptor = {
    sizeof cdc_configuration_descriptor_data,
    cdc_configuration_descriptor_data};

// Strings wrappers array
static const USBDescriptor cdc_strings[] = {
    {sizeof cdc_string0, cdc_string0},
    {sizeof cdc_string1, cdc_string1},
    {sizeof cdc_string2, cdc_string2},
    {sizeof cdc_string3, cdc_string3}};

// EP States
static USBInEndpointState ep1_in_state;   // IN EP1 state
static USBOutEndpointState ep1_out_state; // OUT EP1 state
static USBInEndpointState ep2_in_state;   // IN EP2 state

// EP1 initialization structure (both IN and OUT)
static const USBEndpointConfig ep1_config = {
    USB_EP_MODE_TYPE_BULK, // + uint32_t            ep_mode
    NULL,                  // + usbepcallback_t     setup_cb
    sduDataTransmitted,    // + usbepcallback_t     in_cb
    sduDataReceived,       // + usbepcallback_t     out_cb
    0x0040,                // + uint16_t            in_maxsize
    0x0040,                // + uint16_t            out_maxsize
    &ep1_in_state,         // + USBInEndpointState  *in_state
    &ep1_out_state,        // + USBOutEndpointState *out_state
    2,                     // + uint16_t            ep_buffers
    NULL                   // + uint8_t             *setup_buf
};

// EP2 initialization structure (IN only)
static const USBEndpointConfig ep2_config = {
    USB_EP_MODE_TYPE_INTR,   // + uint32_t            ep_mode
    NULL,                    // + usbepcallback_t     setup_cb
    sduInterruptTransmitted, // + usbepcallback_t     in_cb
    NULL,                    // + usbepcallback_t     out_cb
    0x0010,                  // + uint16_t            in_maxsize
    0x0000,                  // + uint16_t            out_maxsize
    &ep2_in_state,           // + USBInEndpointState  *in_state
    NULL,                    // + USBOutEndpointState *out_state
    1,                       // + uint16_t            ep_buffers
    NULL                     // + uint8_t             *setup_buf
};

// USB driver configuration
static const USBConfig usb_config = {
    usb_event,
    get_descriptor,
    sduRequestsHook,
    sof_handler};

// Serial over USB driver configuration
static const SerialUSBConfig usbcdc_config = {
    &USBD1,
    USBD1_DATA_REQUEST_EP,
    USBD1_DATA_AVAILABLE_EP,
    USBD1_INTERRUPT_REQUEST_EP};

// =================================================================================================
// Local Functions
// =================================================================================================

// Handles the GET_DESCRIPTOR callback. All required descriptors must be handled here
static const USBDescriptor *get_descriptor(USBDriver *usbp, uint8_t dtype, uint8_t dindex, uint16_t lang)
{
    UNUSED(usbp);
    UNUSED(lang);

    switch (dtype)
    {
    case USB_DESCRIPTOR_DEVICE:
        return &cdc_device_descriptor;
    case USB_DESCRIPTOR_CONFIGURATION:
        return &cdc_configuration_descriptor;
    case USB_DESCRIPTOR_STRING:
        if (dindex < 4)
            return &cdc_strings[dindex];
    }
    return NULL;
}

// Handles the USB driver global events
static void usb_event(USBDriver *usbp, usbevent_t event)
{
    switch (event)
    {
    case USB_EVENT_ADDRESS:
        return;

    case USB_EVENT_CONFIGURED:

        osalSysLockFromISR();
        // Enables the endpoints specified into the configuration.
        // Note, this callback is invoked from an ISR so I-Class functions must be used.
        usbInitEndpointI(usbp, USBD1_DATA_REQUEST_EP, &ep1_config);
        usbInitEndpointI(usbp, USBD1_INTERRUPT_REQUEST_EP, &ep2_config);
        // Resetting the state of the CDC subsystem
        sduConfigureHookI(&SDU1);
        osalSysUnlockFromISR();
        return;

    case USB_EVENT_RESET:
    case USB_EVENT_UNCONFIGURED:
    case USB_EVENT_SUSPEND:
        osalSysLockFromISR();
        // Disconnection event on suspend
        sduSuspendHookI(&SDU1);
        osalSysUnlockFromISR();
        return;

    case USB_EVENT_WAKEUP:
        osalSysLockFromISR();
        // Connection event on wakeup
        sduWakeupHookI(&SDU1);
        osalSysUnlockFromISR();
        return;

    case USB_EVENT_STALLED:
        return;
    }
    return;
}

// Handles the USB driver global events
static void sof_handler(USBDriver *usbp)
{
    UNUSED(usbp);

    osalSysLockFromISR();
    sduSOFHookI(&SDU1);
    osalSysUnlockFromISR();
}

// =================================================================================================
// Exported Functions
// =================================================================================================

FORCE_INLINE bool opUsbCdcIsReady()
{
    return SDU1.config->usbp->state == USB_ACTIVE;
}

/**
 * Activates the USB driver and then the USB bus pull-up on D+.
 */
void opUsbCdcInit()
{
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &usbcdc_config);

    usbDisconnectBus(usbcdc_config.usbp);
    // A delay is inserted in order to not have to disconnect the cable after a reset in some boards
    osalSysPolledDelayX(OSAL_MS2I(10));

    usbStart(usbcdc_config.usbp, &usb_config);
    usbConnectBus(usbcdc_config.usbp);
}

#endif /* OP_USB_SERIAL */