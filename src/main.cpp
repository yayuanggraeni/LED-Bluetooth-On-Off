#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int received;// received value will be stored in this variable
char receivedChar;// received value will be stored as CHAR in this variable

const char turnON ='ON';
const char turnOFF ='OFF';
const int LEDpin = 2;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 PT LAPI ITB"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("To turn ON send: ON");//print on serial monitor  
  Serial.println("To turn OFF send: OFF"); //print on serial monitor 
  pinMode(LEDpin, OUTPUT);
 
}

void loop() {
    receivedChar =(char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  
  }
  if (SerialBT.available()) {
    
    SerialBT.print("Received:");// write on BT app
    SerialBT.println(receivedChar);// write on BT app      
    Serial.print ("Received:");//print on serial monitor
    Serial.println(receivedChar);//print on serial monitor    
    //SerialBT.println(receivedChar);//print on the app    
    //SerialBT.write(receivedChar); //print on serial monitor
    if(receivedChar == turnON)
    {
     SerialBT.println("LED ON:");// write on BT app
     Serial.println("LED ON:");//write on serial monitor
     digitalWrite(LEDpin, HIGH);// turn the LED ON
       
    }
    if(receivedChar == turnOFF)
    {
     SerialBT.println("LED OFF:");// write on BT app
     Serial.println("LED OFF:");//write on serial monitor
      digitalWrite(LEDpin, LOW);// turn the LED off 
    }    
   
  }
  delay(20);
}