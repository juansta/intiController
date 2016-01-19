/*
 * This file is part of intiLED.
 *
 * intiLED is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * intiLED is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with intiLED.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// Include LUFA driver
#include <LUFA/Drivers/USB/USB.h>


class Usb
{
public:
    Usb();
    ~Usb();

    bool tick();

    bool getData ();
    bool sendData();

    static uint8_t getReportSize()
    {
        return GENERIC_REPORT_SIZE;
    }

private:
    void EVENT_USB_Device_Connect(void);
    void EVENT_USB_Device_Disconnect(void);
    void EVENT_USB_Device_ConfigurationChanged(void);
    void EVENT_USB_Device_ControlRequest(void);
    void EVENT_USB_Device_StartOfFrame(void);

    /** Endpoint address of the Generic HID reporting IN endpoint. */
    static const uint8_t GENERIC_IN_EPADDR = (ENDPOINT_DIR_IN | 1);

    /** Size in bytes of the Generic HID reporting endpoint. */
    static const uint8_t GENERIC_EPSIZE    = 8;

    /** Size in bytes of the Generic HID reporting endpoint. */
    static const uint8_t GENERIC_REPORT_SIZE = 21;

    /** Enum for the device interface descriptor IDs within the device. Each interface descriptor
     *  should have a unique ID index associated with it, which can be used to refer to the
     *  interface from other descriptors.
     */
    enum InterfaceDescriptors_t
    {
        INTERFACE_ID_GenericHID = 0, /**< GenericHID interface descriptor ID */
    };

    /** Enum for the device string descriptor IDs within the device. Each string descriptor should
     *  have a unique ID index associated with it, which can be used to refer to the string from
     *  other descriptors.
     */
    enum StringDescriptors_t
    {
        STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
        STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
        STRING_ID_Product      = 2, /**< Product string ID */
        STRING_ID_Serial       = 3, /**< Product string Serial */
    };

    /** Type define for the device configuration descriptor structure. This must be defined in the
     *  application code, as the configuration descriptor contains several sub-descriptors which
     *  vary between devices, and which describe the device's usage to the host.
     */
    typedef struct
    {
        USB_Descriptor_Configuration_Header_t Config;

        // Generic HID Interface
        USB_Descriptor_Interface_t            HID_Interface;
        USB_HID_Descriptor_HID_t              HID_GenericHID;
        USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
    } USB_Descriptor_Configuration_t;


    /** LUFA HID Class driver interface configuration and state information. This structure is
     *  passed to all HID Class driver functions, so that multiple instances of the same class
     *  within a device can be differentiated from one another.
     */
    //USB_ClassInfo_HID_Device_t Generic_HID_Interface;

    /** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
     *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
     *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
     */
    USB_Descriptor_String_t LanguageString;

    /** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
     *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
     *  Descriptor.
     */
    USB_Descriptor_String_t ManufacturerString;

    /** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
     *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
     *  Descriptor.
     */
    USB_Descriptor_String_t ProductString;

    /** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
     *  device characteristics, including the supported USB version, control endpoint size and the
     *  number of device configurations. The descriptor is read out by the USB host when the enumeration
     *  process begins.
     */
    USB_Descriptor_Device_t DeviceDescriptor;

    /** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
     *  of the device in one of its supported configurations, including information about any device interfaces
     *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
     *  a configuration so that the host may correctly communicate with the USB device.
     */
    USB_Descriptor_Configuration_t ConfigurationDescriptor;
};
