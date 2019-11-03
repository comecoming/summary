#include <stdio.h>
#include <usb.h>

int main()
{
	struct usb_bus *busses;
	usb_init();
	usb_find_busses();
	usb_find_devices();

	busses = usb_get_busses();

	return 0;
}
