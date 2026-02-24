#include <Arduino.h>
#include <ArduinoJson.h>
#include <SimpleSerialShell.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <MFRC522v2.h>

MFRC522DriverPinSimple cs_pin{SS};
MFRC522DriverSPI spi_driver{cs_pin};

MFRC522 reader{spi_driver};

void setup() {


}

void loop() {
}
