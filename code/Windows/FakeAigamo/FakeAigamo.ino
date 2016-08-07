void setup() {
  pinMode(13, OUTPUT);
  CommInitialize();
}

void loop() {
  char command;
  int data;
  if (CommTask(&command, &data))
  {
    switch (command)
    {
    case 'F': // Forward
      for (int i = 0; i < 1; i++)
      {
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        delay(200);
      }
      break;
    case 'B': // Backward
      for (int i = 0; i < 2; i++)
      {
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        delay(200);
      }
      break;
    case 'S': // Stop
      break;
    case 'L': // Left
      break;
    case 'R': // Right
      break;
    case 'c': // TurnCw
      break;
    case 'C': // TurnCcw
      break;
    }
  }
}

void CommInitialize()
{
  Serial.begin(115200);
  Serial.setTimeout(5000);
}

boolean CommTask(char* command, int* data)
{
  if (Serial.available() <= 0) return false;
  if (Serial.read() != ':') return false;
  
  String message = Serial.readStringUntil('\n');
  if (message.length() != 1 + 2) return false;

  int i = 0;
  String c = message.substring(i, i + 1); i += 1;
  String d = message.substring(i, i + 2); i += 2;

  *command = c[0];
  if (sscanf(d.c_str(), "%x", data) != 1) return false;

  return true;
}

