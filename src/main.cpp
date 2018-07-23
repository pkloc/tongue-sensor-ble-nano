#include <Arduino.h>
#include <SPI.h>
#include <BLEPeripheral.h>

#define BLE_REQ     10
#define BLE_RDY     2
#define BLE_RST     9

BLEPeripheral blePeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);

BLEService sensorService("88ec0a4d-521e-47af-8923-937518c57829");
BLEIntCharacteristic sensorCharacteristic("88ec0a4d-521e-47af-8923-937518c57829", BLERead | BLENotify);

int sensorValue = 0;

void setup() {
    Serial.begin(9600);

    blePeripheral.setLocalName("BleNano");
    blePeripheral.setAdvertisedServiceUuid(sensorService.uuid());

    blePeripheral.addAttribute(sensorService);
    blePeripheral.addAttribute(sensorCharacteristic);

    blePeripheral.begin();
    Serial.println("BLE Peripheral active");
}

void loop() {
    BLECentral central = blePeripheral.central();   // listen for connections

    // if you get a connection
    if(central){
        sensorValue += 1;
        Serial.print("Connected to central: ");
        Serial.println(central.address());

        sensorCharacteristic.setValue(sensorValue);

        // Central disconnected
        Serial.print("Disconnected from central: ");
        Serial.println(central.address());

        delay(1000);
    }
}
