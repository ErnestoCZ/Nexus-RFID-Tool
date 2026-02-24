#include <Arduino.h>
#include <ArduinoJson.h>
#include <SimpleSerialShell.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <MFRC522v2.h>

//PFP
void printHex(byte* buffer, byte bufferSize);

const String serial_separator = "///////////////////////////////////////////////////";

static MFRC522::MIFARE_Key key_default;  

MFRC522DriverPinSimple cs_pin{SS};
MFRC522DriverSPI spi_driver{cs_pin};
MFRC522 reader{spi_driver};

void setup() {

    //Serial
    Serial.begin(115200);

    //Init default MIFARE Key
    for (size_t i = 0; i < MFRC522Constants::MF_KEY_SIZE; i++)
    {
        key_default.keyByte[i] = 0xFF;
    }

    reader.PCD_Init();
    if(reader.PCD_Init()) Serial.println("Success in init PCD Device");

    
    MFRC522Debug::PCD_DumpVersionToSerial(reader,Serial);

    Serial.println(serial_separator);
    Serial.println("Performing selftest of the PCD...");
    if(reader.PCD_PerformSelfTest() == true){
        Serial.println("PCD Version : " + reader.PCD_GetVersion());
    }
    Serial.println(serial_separator);

}

void loop() {
    //TODO check serial if a shell command is present
    
    if(!reader.PICC_IsNewCardPresent()) return;
    if(!reader.PICC_ReadCardSerial()) return;

    MFRC522::StatusCode status;
    status = reader.PCD_Authenticate(MFRC522::PICC_Command::PICC_CMD_MF_AUTH_KEY_A,4,&key_default,&(reader.uid));
    if(status != MFRC522::StatusCode::STATUS_OK){
        Serial.println("ERROR in AUTH process : ERROR : " + status);
        reader.PCD_StopCrypto1();
        return;
    }

    Serial.println("Reading...");
    byte buffer[18] = {0};

    status = reader.MIFARE_Read(4,buffer,(byte*)18);
    printHex(buffer,18);
    memset(buffer,0,sizeof(byte));

    status = reader.MIFARE_Read(5,buffer,(byte*)18);
    printHex(buffer,18);
    memset(buffer,0,sizeof(byte));

    status = reader.MIFARE_Read(6,buffer,(byte*)18);
    printHex(buffer,18);
    memset(buffer,0,sizeof(byte));

    status = reader.MIFARE_Read(7,buffer,(byte*)18);
    printHex(buffer,18);
    memset(buffer,0,sizeof(byte));

    Serial.println("Reading done.");

    reader.PCD_StopCrypto1();
}
void printHex(byte* buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        char hex[3]; // Platz für 2 Zeichen + Null-Terminator
        sprintf(hex, "%02X", buffer[i]);
        Serial.print(hex);
    }
    Serial.println(); // Zeilenumbruch für das Protokoll
}