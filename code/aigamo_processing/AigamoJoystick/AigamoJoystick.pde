/**
 * Simple Write. 
 * 
 * Check if the mouse is over a rectangle and writes the status to the serial port. 
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port

void setup() 
{
  size(200, 200);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0];
  myPort = new Serial(this, "/dev/tty.usbmodem1421", 115200);
}

void draw() {
  background(255);
  if (mouseOverRect() == true) {  // If mouse is over square,
    fill(204);                    // change color and
    myPort.write(':');              // send an H to indicate mouse is over square
    myPort.write('F');
    myPort.write('1');
    myPort.write('0');
    myPort.write('\n');
    delay(100);

  } 
  else {                        // If mouse is not over square,
    //fill(0);                      // change color and
    //myPort.write(':');              // send an L otherwise
    //myPort.write('B');
    //myPort.write('1');
    //myPort.write('0');
    //myPort.write('\n');
    
  }
  rect(50, 50, 100, 100);         // Draw a square
}

boolean mouseOverRect() { // Test if mouse is over square
  return ((mouseX >= 50) && (mouseX <= 150) && (mouseY >= 50) && (mouseY <= 150));
}