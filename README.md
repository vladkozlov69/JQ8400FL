# JQ8400FL
Arduino library for JQ8400FL sound chip


Code snippets:


SoftwareSerial mySerial(11, 10); // RX, TX for connection with JQ8400FL
JQ8400FL player(&mySerial);

...

void setup() {
  mySerial.begin(9600); // Initial serial communication with JQ8400Fl

  player.volumeSet(20);

  player.begin();
  player.push("5635230244563523024456352302445635230244");
  player.commit();

}