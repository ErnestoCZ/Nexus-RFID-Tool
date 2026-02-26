#include <Arduino.h>
#include <SimpleSerialShell.h>
#include <MFRC522.h>
#include <SPI.h>

MFRC522 mfrc522(10, 9); // SS pin 10, RST pin 9
MFRC522::MIFARE_Key key = { .keyByte = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} }; // Default key for MIFARE cards

void setup() {
    //Serial
    Serial.begin(115200);
    SPI.begin();

    mfrc522.PCD_Init();
    if(!mfrc522.PCD_PerformSelfTest()) {
        Serial.println("Self test failed");
    }else{
        Serial.println("Self test passed"); 
    }
    mfrc522.PCD_Init();
    delay(500);
    mfrc522.PCD_DumpVersionToSerial();
    // mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);

}

void loop() {
    //TODO check serial if a shell command is present
    if(!mfrc522.PICC_IsNewCardPresent() && !mfrc522.PICC_ReadCardSerial()) {
        return;
    }else{
        Serial.println("Card detected");
        Serial.print("UID:");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.println();
    }
    // mfrc522.PCD_Authenticate(mfrc522.PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid));

    MFRC522::StatusCode status = mfrc522.PCD_Authenticate(mfrc522.PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid));
    delay(20);
    while(status == mfrc522.STATUS_TIMEOUT && mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        Serial.println("Authentication timed out, retrying...");
        status = mfrc522.PCD_Authenticate(mfrc522.PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid));
        delay(20);
    }


    delay(100);
    if(status != mfrc522.STATUS_OK) {
        Serial.print("Authentication failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }else{
        Serial.println("Authentication successful");
    }

    byte buffer[18] = {0};
    byte bufferSize = 18;
    status = mfrc522.MIFARE_Read(0, buffer, &bufferSize);
    if(status != mfrc522.STATUS_OK) {
        Serial.print("Reading failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }else{
        Serial.print("Data in block 1:");
        for (byte i = 0; i < 16; i++) {
            Serial.print(buffer[i] < 0x10 ? " 0" : " ");
            Serial.print(buffer[i], HEX);
        }
        Serial.println();
        mfrc522.PCD_StopCrypto1();
    }

    delay(200);

}