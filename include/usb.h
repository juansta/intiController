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
#include <HIDClassDevice.h>

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

    /** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
     *  documentation) by the application code so that the address and size of a requested descriptor can be given
     *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
     *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
     *  USB host.
     */
    uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                        const uint8_t wIndex,
                                        const void** const DescriptorAddress);

    /** HID class driver callback function for the creation of HID reports to the host.
     *
     *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
     *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
     *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
     *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
     *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
     *
     *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
     */
    bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                             uint8_t* const ReportID,
                                             const uint8_t ReportType,
                                             void* ReportData,
                                             uint16_t* const ReportSize);

    /** HID class driver callback function for the processing of HID reports from the host.
     *
     *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
     *  \param[in] ReportID    Report ID of the received report from the host
     *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
     *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
     *  \param[in] ReportSize  Size in bytes of the received HID report
     */
    void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                              const uint8_t ReportID,
                                              const uint8_t ReportType,
                                              const void* ReportData,
                                              const uint16_t ReportSize);

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

    /** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
    static uint8_t PrevHIDReportBuffer[GENERIC_REPORT_SIZE];

    static const uint8_t FIXED_CONTROL_ENDPOINT_SIZE = 21;
    static const uint8_t FIXED_NUM_CONFIGURATIONS    = 1;

    /** LUFA HID Class driver interface configuration and state information. This structure is
     *  passed to all HID Class driver functions, so that multiple instances of the same class
     *  within a device can be differentiated from one another.
     */
    USB_ClassInfo_HID_Device_t Generic_HID_Interface;

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
