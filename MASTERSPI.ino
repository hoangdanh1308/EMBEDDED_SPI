/*
  File: MASTERSPI.ino
  Author: NGUYEN HOANG DANH
  Date: 08/05/2023
  Description: This is file for MASTERSPI using Arduino
*/
#define SS_PIN    4
#define SCLK_PIN  5
#define MISO_PIN  6
#define MOSI_PIN  7

#define TFULL 50 // us
#define THALF 25

void setup() {
  // put your setup code here, to run once:
  pinMode(SS_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(MOSI_PIN, OUTPUT);
  digitalWrite(SCLK_PIN, LOW);
  digitalWrite(SS_PIN, HIGH);
  Serial.begin(9600);
  delay(1);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(SS_PIN, LOW);
uint8_t receiveByte = transferMasterSPI('d');   // send char 'd' -> 100(dec)->0x64(hex)
digitalWrite(SS_PIN, HIGH);
digitalWrite(SCLK_PIN, LOW);
Serial.println(receiveByte);
Serial.println(' ');
delay(1000);
}
/*
  Function: transferMasterSPI
  Description: This function use for Master to transfer data SPI. MODE 0 bitOrder MSB
  Input:
    input: None
  Output:
    return: None
*/
uint8_t transferMasterSPI(uint8_t byteOut){
  uint8_t byteIn = 0;
  uint8_t coutByte = 0x80; // 1000.0000
  uint8_t tempBit;
  for (coutByte = 0x80; coutByte > 0; coutByte = coutByte >> 1){
    tempBit = byteOut & coutByte;
    if(tempBit != 0){
      digitalWrite(MOSI_PIN, HIGH);
      }else{
        digitalWrite(MOSI_PIN,LOW);
        }
    delayMicroseconds(THALF);
    digitalWrite(SCLK_PIN,HIGH);
    if(digitalRead(MISO_PIN) == HIGH){
      byteIn = byteIn | coutByte;
      }
    delayMicroseconds(THALF);
    digitalWrite(SCLK_PIN,LOW);
  }
  return byteIn;
}
