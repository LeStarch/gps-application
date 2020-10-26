#include <RFM69.h>

RFM69 radio;
void setup() {
  radio.setCS(15);
  radio.initialize(RF69_915MHZ, 0, 50);
  radio.setHighPower();
  delay(1000);

}

void loop() {
  radio.send(1, "hey there\n", 10);
  delay(500);
}
