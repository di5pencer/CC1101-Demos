
#include <Arduino.h>
#include <cc1101.h>
#include <ccpacket.h>

#define CC1101Interrupt 0 // 
#define CC1101_GDO0 2

const int button1 = 6; // read a button
const int pot1 = A0;   // read an analogiue source
int potState;

CC1101 radio;

byte syncWord[2] = {199, 10};

}

void setup() {
  pinMode(6, INPUT);
  pinMode(pot1, INPUT)
;  Serial.begin(9600);
  radio.init();
  radio.setSyncWord(syncWord);
  radio.setCarrierFreq(CFREQ_433);
  radio.disableAddressCheck();
  radio.setChannel(1);
  radio.setTxPowerAmp(PA_Minus20);
  radio.writeReg(CC1101_MDMCFG1, 21);
  radio.writeReg(CC1101_DEVIATN, 62 );

    Serial.print(F("CC1101_PARTNUM "));
    Serial.println(radio.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
    Serial.print(F("CC1101_VERSION "));
    Serial.println(radio.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
    Serial.print(F("CC1101_MARCSTATE "));
    Serial.println(radio.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

    Serial.println(F("CC1101 radio initialized."));
    attachInterrupt(CC1101Interrupt, messageReceived, FALLING);

}


void loop() {

  int buttonState = digitalRead(button1);
  int potState = analogRead(pot1);
  potState = map(potState, 0, 1023, 0, 255);

 // Sends the button value and pot value as separate bytes
detachInterrupt(CC1101Interrupt);
       byte potData = potState;
        byte buttonData = buttonState;
        CCPACKET data;
        data.data[1] =buttonData;
        data.data[2] = potData;

        data.length = 4;
        radio.sendData(data);
        Serial.println("Sent data packet ");




delay(10);
    
}
