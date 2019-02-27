#define _DEBUG_
// UIPEthernet for ENC28J60: https://github.com/ntruchsess/arduino_uip
#include <UIPEthernet.h>
#include <ThingerENC28J60.h>

#include <Servo.h>
Servo servo;

#define USERNAME "mejison"
#define DEVICE_ID "enc28j60"
#define DEVICE_CREDENTIAL "123456"

ThingerENC28J60 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int pinTwo = 2;
int pinThree = 3;
int pinFour = 4;
int pinFive = 5;

void setup() {
    Serial.begin(115200);

  // ENC28J60 using fixed IP Address. DHCP is too big for the sketch.
  uint8_t mac[] = {0x54, 0x34, 0x41, 0x30, 0x30, 0x31};
  Ethernet.begin(mac, IPAddress(192, 168, 0, 105));

  pinMode(pinTwo, OUTPUT);
  pinMode(pinThree, OUTPUT);
  pinMode(pinFour, OUTPUT);
  
  servo.attach(pinFive);
  
  thing["two"] << digitalPin(pinTwo);
  thing["three"] << digitalPin(pinThree);
  thing["four"] << digitalPin(pinFour);
  thing["five"] << [](pson& in){
    servo.write((int)in);
  };
}

void loop() {
  thing.handle();
}
