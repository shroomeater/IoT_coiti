/*
 * RST D9
 * SS (SDA) D10
 * MOSI D11
 * MISO D12
 * SCK D13 
 * 
 */

#include <SPI.h>
#include <MFRC522.h>
const int RST_PIN = 9; // Pin 9 para el reset del RC522
const int SS_PIN = 10; // Pin 10 para el SS (SDA) del RC522

MFRC522 mfrc522(SS_PIN, RST_PIN);
byte readUID[4]; // Almacena el tag leido
byte validKey1[4] = { 0x30, 0x59, 0x67, 0x89};//UID del llavero a validar

bool isEqualArray(byte arrayA[], byte arrayB[], int length)
{
for (int index = 0; index < length; index++)
{
if (arrayA[index] != arrayB[index]) return false;
}
return true;
}
void setup() {
Serial.begin(9600); // Iniciar serial
SPI.begin();
// Iniciar SPI
mfrc522.PCD_Init(); // Iniciar MFRC522
}
void loop() {
if (mfrc522.PICC_IsNewCardPresent())
{if (mfrc522.PICC_ReadCardSerial())
{
if (isEqualArray(mfrc522.uid.uidByte, validKey1, 4))
Serial.println("Tarjeta valida");
else
Serial.println("Tarjeta invalida");
mfrc522.PICC_HaltA(); // Finalizar lectura
}
}
delay(250);
}
