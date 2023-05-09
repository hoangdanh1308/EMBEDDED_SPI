/*
  File: SLAVESPI.ino
  Author: NGUYEN HOANG DANH
  Date: 08/05/2023
  Description: This is file for SLAVESPI using Arduino
*/
#define SS_PIN    4
#define SCLK_PIN  5
#define MISO_PIN  6
#define MOSI_PIN  7

void setup() {
  // put your setup code here, to run once:
  pinMode(SS_PIN, INPUT);
  pinMode(SCLK_PIN, INPUT);
  pinMode(MISO_PIN, OUTPUT);
  pinMode(MOSI_PIN, INPUT);
  Serial.begin(9600);
  delay(1);
}

void loop() {
  // put your main code here, to run repeatedly:
uint8_t receiveByte;
receiveByte = transferSlaveSPI('D');  // send char 'D' -> 68(dec)->0x44(hex)
Serial.println(receiveByte);
Serial.println(' ');
}
/*
  Function: transferSlaveSPI
  Description: This function use for Master to transfer data SPI. MODE 0 bitOrder MSB
  Input:
    input: None
  Output:
    return: None
*/
uint8_t transferSlaveSPI(uint8_t byteOut){
  uint8_t byteIn = 0;
  uint8_t coutByte = 0x80; // 1000.0000
  uint8_t tempBit;
  while(digitalRead(SS_PIN) == HIGH);
  for (coutByte = 0x80; coutByte > 0; coutByte = coutByte >> 1){
    tempBit = byteOut & coutByte;
    if(tempBit != 0){
      digitalWrite(MISO_PIN,HIGH);
      }else{
        digitalWrite(MISO_PIN,LOW);
        }
    while(digitalRead(SCLK_PIN) == LOW);
    if(digitalRead(MOSI_PIN) == HIGH){
      byteIn = byteIn | coutByte;
      }
    while(digitalRead(SCLK_PIN) == HIGH);
  }
  return byteIn;
}
