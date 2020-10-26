#include <RFM69.h>

RFM69 radio;
char buffer[1000];
int i = 0;

void setup() {
  Serial.begin(115200);
  radio.setCS(15);
  bool worked = radio.initialize(RF69_915MHZ, 0, 50);
  radio.setHighPower();
}

void loop() {
    if (radio.receiveDone())
    {
        for (int i = 0; i < radio.DATALEN; i++)
        {
            Serial.write(radio.DATA[i]);
        }
    }
    for (; i < sizeof(buffer) && Serial.available(); i++) {
        int byte_in = Serial.read();
        if (byte_in != -1) {
            buffer[i] = (char)byte_in;
        }
    }
    if (i > 2) {
        radio.send(1, buffer, i);
        i = 0;
    }
}
