
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NETWORK_ID_SIZE 6
#define SSID_LENGTH 32


typedef struct WifiScan {
	char ssid [SSID_LENGTH]; // Network name (SSID), consisting of up to 32 ASCII characters
	uint8_t bssid[NETWORK_ID_SIZE]; // Network ID (BSSID), consisting of 6 bytes
	uint8_t rssi_index; // Represents the index of Signal strength (RSSI)(a number ranging from 20 to -100).
					   // The index 0 represents 20, the index 40 represents 0, the index 240 represents 100.
} WifiScanContent;

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
 * The formula that is used is below
 *  index = -(rssi - 20)/0.5
 */
static uint8_t getRssiIndex(const float rssi) {
	assert(rssi <= 20 && rssi >= -100);

	uint8_t index = -(rssi - 20) / 0.5f;

	return index;
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
 */
static float getRssiValue(const uint8_t index) {
	assert(index >= 0 && index <= 240);

	float rssi = 20 - (index * 0.5f);

	return rssi;
}

/**
 * Synchronously sends the supplied data buffer to the MCU as a single complete
 * packet of data.
 *
 * @param data Buffer to transmit
 * @param len Number of bytes to send
 */
void transmitPacket(const void *data, size_t len) {
	// You do *not* need to implement this function, but should call it from
	// sendWifiScanResult();
}

void printfWifiScan(size_t ap_count, const char **ssid_list, const uint8_t **bssid_list, const float *rssi_list) {
	printf("\nNumber of scans %zu", ap_count);

	printf("\nSSI list");
	for (uint8_t i = 0; i < ap_count; i++) {
		printf("\n%hhu %s", i, ssid_list[i]);
	}

	printf("\nBSSI list");
	for (uint8_t i = 0; i < ap_count; i++) {
		printf("\n\tList -  %hhu \n\t", i);
		for (uint8_t index = 0; index < NETWORK_ID_SIZE; index++) {
			printf("Ox%x ", bssid_list[i][index]);
		}
	}

	printf("\nRSSI list");
	for (uint8_t i = 0; i < ap_count; i++) {
		printf("\n%hhu %f", i, rssi_list[i]);
	}

	printf("\n");
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
void sendWifiScanResult(size_t ap_count, const char **ssid_list, const uint8_t **bssid_list, const float *rssi_list) {
	printfWifiScan(ap_count, ssid_list, bssid_list, rssi_list);

	// Assuming that have malloc
	size_t data_size = sizeof(WifiScanContent) * ap_count;
	const void *data = (void *) malloc(data_size);

	WifiScanContent *wifiScan = (WifiScanContent *) data;
	for (uint8_t index = 0; index < ap_count; index++) {
		assert(strlen(ssid_list[index]) <= SSID_LENGTH);

		strcpy(wifiScan->ssid, ssid_list[index]);

		wifiScan->rssi_index = getRssiIndex(rssi_list[ap_count]);

		wifiScan++;
	}

	transmitPacket(data, data_size);
}


int main() {
	printf("\nScanning and transmitting\n");

	const size_t kAccessPointCount = 2;
	const char *ssid_list[kAccessPointCount] = {"abc", "x"};
	const uint8_t bssid1[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	const uint8_t bssid2[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
	const uint8_t *bssid_list[kAccessPointCount] = {bssid1, bssid2};
	const float rssi_list[kAccessPointCount] = {-48.0, -50.5};

	sendWifiScanResult(kAccessPointCount, ssid_list, bssid_list, rssi_list);

	return 0;
}

