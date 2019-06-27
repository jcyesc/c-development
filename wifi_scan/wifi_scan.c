#include "wifi_scan.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Converts the RSSI value to a given index between 0 and 240.
 * See table below for examples
 *
 * RSSI value | index
 * -------------------
 * 20         |    0
 * 19.5       |    1
 * 19         |    2
 *   ...      |    ...
 * -99.5      | 239
 * -100       | 240
 *
 * The formula that is used is below:
 *
 * 	index = -(rssi - 20)/0.5
 *
 * @param rssi_value The RSSI value that will be converted into
 * 					 an index.
 */
static uint8_t getRssiIndex(const float rssi_value) {
	assert(rssi_value <= 20.0 && rssi_value >= -100.0);

	uint8_t rssi_index = -(rssi_value - 20) / 0.5f;
	return rssi_index;
}

/**
 * Converts the given index into the RSSI value.
 * See table below for examples:
 *
 * index | RSSI value
 * -------------------
 * 0     |    20
 * 1     |    19.5
 * 2     |    19
 * 3     |    18.5
 * 4     |    18
 * ...   |    ...
 * 239   |    -99.5
 * 240   |    -100
 *
 * The formula that is used is below:
 *
 *  rssi = 20 - (index * 0.5)
 *
 *  @param rssi_index The RSSI index that will be used to calculate the RSSI value.
 */
static float getRssiValue(const uint8_t rssi_index) {
	assert(rssi_index >= 0 && rssi_index <= 240);

	float rssiValue = 20 - (rssi_index * 0.5f);
	return rssiValue;
}

/**
 * Prints the Wifi scan. This function is only used for debugging purposes.
 *
 * @param ap_count  Number of access points in the scan result, and the size of the
 * 				    following list.
 * @param ssid_list List of SSIDs, given as an array of pointers null-terminated
 * 					ASCII strings.
 * @param bssid_list List of BSSIDs, given as an array of 6-byte arrays.
 * @param rssi_list  List of RSSIs
 */
static void printfWifiScan(size_t ap_count, const char **ssid_list,
		const uint8_t **bssid_list, const float *rssi_list) {
	printf("\nData to be processed");
	printf("\n\tNumber of scans %zu", ap_count);

	printf("\n\tSSI list");
	for (uint8_t i = 0; i < ap_count; i++) {
		printf("\n\t\tssid[%hhu] = %s", i, ssid_list[i]);
	}

	printf("\n\tBSSI list");
	for (uint8_t i = 0; i < ap_count; i++) {
		printf("\n\t\tList - %hhu \n\t\t", i);
		for (uint8_t j = 0; j < NETWORK_ID_SIZE; j++) {
			printf("0x%x ", bssid_list[i][j]);
		}
	}

	printf("\n\tRSSI list");
	for (uint8_t i = 0; i < ap_count; i++) {
		printf("\n\t\trssi[%hhu] = %f", i, rssi_list[i]);
	}

	printf("\n");
}

/**
 * Prints the data in hexadecimal.
 *
 * @param data Represents a pointer to the data to be printed.
 * @param len Number of bytes to print
 */
static void printWifiScanInHex(const void *data, size_t len) {
	printf("\t\t");

	char *ptr = (char *) data;
	for (uint8_t i = 0; i < len; i++) {
		if (i != 0 && i % 10 == 0) {
			printf("\n\t\t");
		}
		printf("Ox%x ", *ptr++);
	}
}

/**
 * Synchronously sends the supplied data buffer to the MCU as a single complete
 * packet of data.
 *
 * @param data Buffer to transmit
 * @param len Number of bytes to send
 */
static void transmitPacket(const void *data, size_t len) {
	printf("\n===================================");
	printf("\nTransmitting packet");
	printf("\n===================================");

	// This is how the MCU would decode the information.
	WifiScanContent *wifi_scan = (WifiScanContent *) data;
	size_t ap_count = len / sizeof(WifiScanContent);
	for (uint8_t i = 0; i < ap_count; i++) {
		printf("\n\nWifi Scan - %hhu", i);
		printf("\n\tName: %s", wifi_scan->ssid);
		printf("\n\tNetwork Id: ");
		for (uint8_t j = 0; j < NETWORK_ID_SIZE; j++) {
			printf("Ox%x ", wifi_scan->bssid[j]);
		}

		float rssid = getRssiValue(wifi_scan->rssi_index);
		printf("\n\tSignal Strength (SSID): %f", rssid);

		printf("\n\tHexadecimal \n");
		printWifiScanInHex((const void *) wifi_scan, sizeof(WifiScanContent));

		wifi_scan++;
	}

	free((void *) data);

	printf("\n\nEnd of the transmission .....\n");
}

/**
 * Encodes a WiFi scan result into the format sent over the wire. You should
 * implement this to call transmitPacket() to send the data to the MCU once
 * it's formatted appropriately.
 *
 * @param ap_count  Number of access points in the scan result, and the size of the
 * 				    following list.
 * @param ssid_list List of SSIDs, given as an array of pointers null-terminated
 * 					ASCII strings.
 * @param bssid_list List of BSSIDs, given as an array of 6-byte arrays.
 * @param rssi_list  List of RSSIs
 */
void sendWifiScanResult(size_t ap_count, const char **ssid_list,
		const uint8_t **bssid_list, const float *rssi_list) {
	printf("\n===================================");
	printf("\nProcessing Wifi Scan");
	printf("\n===================================");
	printfWifiScan(ap_count, ssid_list, bssid_list, rssi_list);

	// Assuming that we can use malloc
	size_t data_size = sizeof(WifiScanContent) * ap_count;
	const void *data = (void *) malloc(data_size);

	WifiScanContent *wifi_scan = (WifiScanContent *) data;
	for (uint8_t i = 0; i < ap_count; i++) {
		assert(strlen(ssid_list[i]) <= SSID_LENGTH);
		strcpy(wifi_scan->ssid, ssid_list[i]);
		wifi_scan->rssi_index = getRssiIndex(rssi_list[i]);

		for (uint8_t j = 0; j < NETWORK_ID_SIZE; j++) {
			wifi_scan->bssid[j] = bssid_list[i][j];
		}

		wifi_scan++;
	}
	printf("\nFinish encoding...\n");

	transmitPacket(data, data_size);
}

