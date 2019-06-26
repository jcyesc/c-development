
#ifndef WIFI_SCAN_H_
#define WIFI_SCAN_H_

#define NETWORK_ID_SIZE 6
#define SSID_LENGTH 32

/**
 * Represents a Wifi Scan. The Wifi Scan has:
 *
 * - Network name (SSI), consisting of up to 32 ASCII characters.
 * - Network ID (BSSID), consisting of 6 bytes
 * - Signal Strength (RSSI), consists of a number ranging from 20 to -100 in increments of 0.5.
 *
 * Note: Instead of storing RSSI as a float that usually takes 4 bytes (depending of architecture), the
 * RSSI is stored as a uint8_t. The reason of this is because there are 240 different numbers between
 * 20 and -100 that we are interested (20, 19.5, 19, 18.5, .... , -99, -99,5, -100) and we can represent
 * each number as an index. For example:
 *
 * - The index 0 represents 20
 * - The index 40 represents 0
 * - The index 240 represents 100
 *
 */
typedef struct WifiScan {
	char ssid[SSID_LENGTH];
	uint8_t bssid[NETWORK_ID_SIZE];
	uint8_t rssi_index; // Represents the index of Signal strength (RSSI)(a number ranging from 20 to -100).
						//
} WifiScanContent;

#endif /* WIFI_SCAN_H_ */



