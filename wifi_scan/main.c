#include <stdio.h>
#include <stdlib.h>
#include "wifi_scan.h"

/**
 * Starts the scanning and transmission of the Wifi Content.
 *
 * To execute this program run:
 *
 *  make
 *  ./main
 */
int main() {
	printf("\nScanning and transmitting.....\n");

	const size_t kAccessPointCount = 2;
	const char *ssid_list[kAccessPointCount] = { "abc", "x" };
	const uint8_t bssid1[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
	const uint8_t bssid2[6] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
	const uint8_t *bssid_list[kAccessPointCount] = { bssid1, bssid2 };
	const float rssi_list[kAccessPointCount] = { -48.0, -50.5 };

	sendWifiScanResult(kAccessPointCount, ssid_list, bssid_list, rssi_list);

	return 0;
}

