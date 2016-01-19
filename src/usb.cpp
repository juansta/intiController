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

#include <usb.h>
#include <avr/pgmspace.h>

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#include <LUFA/Platform/Platform.h>

static Usb usb;

/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevHIDReportBuffer[21];

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
const USB_Descriptor_HIDReport_Datatype_t PROGMEM GenericReport[] =
{
    /* Use the HID class driver's standard Vendor HID report.
     *  Vendor Usage Page: 0
     *  Vendor Collection Usage: 1
     *  Vendor Report IN Usage: 2
     *  Vendor Report OUT Usage: 3
     *  Vendor Report Size: GENERIC_REPORT_SIZE
     */
    HID_DESCRIPTOR_VENDOR(0x00, 0x01, 0x02, 0x03, Usb::getReportSize())
};


Usb::Usb()
    //: LanguageString    (USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG)),
    //  ManufacturerString(USB_STRING_DESCRIPTOR(L"Juan Aguero")),
    //  ProductString     (USB_STRING_DESCRIPTOR(L"LUFA Generic HID Demo"))
{
    DeviceDescriptor.Header.Size = sizeof(USB_Descriptor_Device_t);
    DeviceDescriptor.Header.Type = DTYPE_Device;

    DeviceDescriptor.USBSpecification       = VERSION_BCD(1,1,0);
    DeviceDescriptor.Class                  = USB_CSCP_NoDeviceClass;
    DeviceDescriptor.SubClass               = USB_CSCP_NoDeviceSubclass;
    DeviceDescriptor.Protocol               = USB_CSCP_NoDeviceProtocol;

    DeviceDescriptor.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE;

    DeviceDescriptor.VendorID               = 0x03EB;
    DeviceDescriptor.ProductID              = 0x204F;
    DeviceDescriptor.ReleaseNumber          = VERSION_BCD(0,0,1);

    DeviceDescriptor.ManufacturerStrIndex   = STRING_ID_Manufacturer;
    DeviceDescriptor.ProductStrIndex        = STRING_ID_Product;
    DeviceDescriptor.SerialNumStrIndex      = NO_DESCRIPTOR;

    DeviceDescriptor.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS;


    ConfigurationDescriptor.Config.Header.Size = sizeof(USB_Descriptor_Configuration_Header_t);
    ConfigurationDescriptor.Config.Header.Type = DTYPE_Configuration;

    ConfigurationDescriptor.Config.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t);
    ConfigurationDescriptor.Config.TotalInterfaces        = 1;
    ConfigurationDescriptor.Config.ConfigurationNumber    = 1;
    ConfigurationDescriptor.Config.ConfigurationStrIndex  = NO_DESCRIPTOR;
    ConfigurationDescriptor.Config.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED);
    ConfigurationDescriptor.Config.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100);

    ConfigurationDescriptor.HID_Interface.Header.Size = sizeof(USB_Descriptor_Interface_t);
    ConfigurationDescriptor.HID_Interface.Header.Type = DTYPE_Interface;

    ConfigurationDescriptor.HID_Interface.InterfaceNumber        = INTERFACE_ID_GenericHID;
    ConfigurationDescriptor.HID_Interface.AlternateSetting       = 0x00;

    ConfigurationDescriptor.HID_Interface.TotalEndpoints         = 1;

    ConfigurationDescriptor.HID_Interface.Class                  = HID_CSCP_HIDClass;
    ConfigurationDescriptor.HID_Interface.SubClass               = HID_CSCP_NonBootSubclass;
    ConfigurationDescriptor.HID_Interface.Protocol               = HID_CSCP_NonBootProtocol;

    ConfigurationDescriptor.HID_Interface.InterfaceStrIndex      = NO_DESCRIPTOR;

    ConfigurationDescriptor.HID_GenericHID.Header.Size = sizeof(USB_HID_Descriptor_HID_t);
    ConfigurationDescriptor.HID_GenericHID.Header.Type = HID_DTYPE_HID;

    ConfigurationDescriptor.HID_GenericHID.HIDSpec                = VERSION_BCD(1,1,1);
    ConfigurationDescriptor.HID_GenericHID.CountryCode            = 0x00;
    ConfigurationDescriptor.HID_GenericHID.TotalReportDescriptors = 1;
    ConfigurationDescriptor.HID_GenericHID.HIDReportType          = HID_DTYPE_Report;
    ConfigurationDescriptor.HID_GenericHID.HIDReportLength        = sizeof(GenericReport);

    ConfigurationDescriptor.HID_ReportINEndpoint.Header.Size = sizeof(USB_Descriptor_Endpoint_t);
    ConfigurationDescriptor.HID_ReportINEndpoint.Header.Type = DTYPE_Endpoint;
    ConfigurationDescriptor.HID_ReportINEndpoint.EndpointAddress        = GENERIC_IN_EPADDR;
    ConfigurationDescriptor.HID_ReportINEndpoint.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA);
    ConfigurationDescriptor.HID_ReportINEndpoint.EndpointSize           = GENERIC_EPSIZE;
    ConfigurationDescriptor.HID_ReportINEndpoint.PollingIntervalMS      = 0x05;


    this->Config.InterfaceNumber = INTERFACE_ID_GenericHID;
    this->Config.ReportINEndpoint.Address              = GENERIC_IN_EPADDR;
    this->Config.ReportINEndpoint.Size                 = GENERIC_EPSIZE;
    this->Config.ReportINEndpoint.Banks                = 1;

    this->Config.PrevReportINBuffer           = PrevHIDReportBuffer;
    this->Config.PrevReportINBufferSize       = sizeof(PrevHIDReportBuffer);
}

Usb::~Usb()
{}

bool Usb::tick()
{
    HID_Device_USBTask(&Generic_HID_Interface);
    USB_USBTask();

    return false;
}
bool Usb::sendData()
{}
bool Usb::getData()
{}
/** Event handler for the library USB Connection event. */
void Usb::EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the library USB Disconnection event. */
void Usb::EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void Usb::EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    ConfigSuccess &= HID_Device_ConfigureEndpoints(&Generic_HID_Interface);

    USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Control Request reception event. */
void Usb::EVENT_USB_Device_ControlRequest(void)
{
    HID_Device_ProcessControlRequest(&Generic_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void Usb::EVENT_USB_Device_StartOfFrame(void)
{
    HID_Device_MillisecondElapsed(&Generic_HID_Interface);
}

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
    const uint8_t  DescriptorType   = (wValue >> 8);
    const uint8_t  DescriptorNumber = (wValue & 0xFF);

    const void* Address = NULL;
    uint16_t    Size    = NO_DESCRIPTOR;

    switch (DescriptorType)
    {
        case DTYPE_Device:
            Address = &DeviceDescriptor;
            Size    = sizeof(USB_Descriptor_Device_t);
            break;
        case DTYPE_Configuration:
            Address = &ConfigurationDescriptor;
            Size    = sizeof(USB_Descriptor_Configuration_t);
            break;
        case DTYPE_String:
            switch (DescriptorNumber)
            {
                case STRING_ID_Language:
                    Address = &LanguageString;
                    Size    = pgm_read_byte(&LanguageString.Header.Size);
                    break;
                case STRING_ID_Manufacturer:
                    Address = &ManufacturerString;
                    Size    = pgm_read_byte(&ManufacturerString.Header.Size);
                    break;
                case STRING_ID_Product:
                    Address = &ProductString;
                    Size    = pgm_read_byte(&ProductString.Header.Size);
                    break;
            }

            break;
        case HID_DTYPE_HID:
            Address = &ConfigurationDescriptor.HID_GenericHID;
            Size    = sizeof(USB_HID_Descriptor_HID_t);
            break;
        case HID_DTYPE_Report:
            Address = &GenericReport;
            Size    = sizeof(GenericReport);
            break;
    }

    *DescriptorAddress = Address;
    return Size;
}

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
    *ReportSize = GENERIC_REPORT_SIZE;
    return false;
}

void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
    // flag that new data has been received
}
