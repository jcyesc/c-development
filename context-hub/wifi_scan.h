
#ifndef WIFI_SCAN_H_
#define WIFI_SCAN_H_

#define NETWORK_ID_SIZE 6
#define SSID_LENGTH 32

/**
 * Represents a Wifi Scan. The Wifi Scan has:
 *
 * - Network name (SSI), consisting of up to 32 ASCII characters.
 * - Network ID (BSSID), consisting of 6 bytes
 * - Signal Strength (RSSI), consists of a number ranging from 20 to 100.
 */
typedef struct WifiScan {
	char ssid[SSID_LENGTH]; // Network name (SSID), consisting of up to 32 ASCII characters
	uint8_t bssid[NETWORK_ID_SIZE]; // Network ID (BSSID), consisting of 6 bytes
	uint8_t rssi_index; // Represents the index of Signal strength (RSSI)(a number ranging from 20 to -100).
						// The index 0 represents 20, the index 40 represents 0, the index 240 represents 100.
} WifiScanContent;


#endif /* WIFI_SCAN_H_ */



