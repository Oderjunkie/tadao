#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>

void assert(int err) {
	if (err != 0) {
		printf("\n\n\x1b[91m[ERROR]\x1b[m\n");
		exit(err);
	}
}

int main(int argc, char **argv) {
	assert(libusb_init(NULL));

	libusb_device **devices;
	libusb_device_handle *handle;
	struct libusb_device_descriptor desc;
	char str[256];
		
	ssize_t device_count = libusb_get_device_list(NULL, &devices);

	printf("--- %i devices ---\n", (int) device_count);
	for (ssize_t i = 0; i < device_count; i++) {
		printf("device #%i - ", (int) i);
		assert(libusb_open(devices[i], &handle));
		assert(libusb_get_device_descriptor(devices[i], &desc));
		if (desc.iProduct) {
			assert(libusb_get_string_descriptor_ascii(handle, desc.iProduct, str, sizeof(str)));
			printf("%s\n", str);
		} else {
			printf("???\n");
		}
	}

	libusb_free_device_list(devices, 0);
	
	libusb_exit(NULL);
	return 0;
}
