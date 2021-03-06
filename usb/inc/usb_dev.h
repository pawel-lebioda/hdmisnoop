#ifndef _USB_DEVICE_H
#define _USB_DEVICE_H

#include <usb.h>
#include <usb_conf.h>
#include <usb_dev_platform.h>
#include <usb_dev_endpoint.h>

struct usb_device;

struct usb_device_fops
{
	usb_ret_t (*sof)(struct usb_device * usbd);
	usb_ret_t (*get_device_descriptor)(struct usb_device * usbd, usb_descriptor_type_t type, uint8_t id, struct usb_device_buffer * buff);
};

struct usb_device
{
	struct
	{
		usb_speed_t speed;
		uint32_t mps;
	} config;
	struct usb_device_endpoint ep_in[USB_DEVICE_IN_ENDPOINTS_NUMBER];
	struct usb_device_endpoint ep_out[USB_DEVICE_OUT_ENDPOINTS_NUMBER];
	struct usb_device_fops fops;
	struct usb_setup_packet setup_packet;
	usb_device_state_t state;
	usb_address_t address;
	usb_dev_platform_handle_t platform;
	struct usb_dev_platform_callbacks platform_callbacks;
};

int usb_dev_init(struct usb_device * usbd);
int usb_dev_get_string_descriptor(const char * str, uint8_t * buff, int max);

#endif //_USB_DEVICE_H
