void setup() {
  CommInitialize();
}

void loop() {
  char command;
  int data;
  if (CommTask(&command, &data))
  {
    Serial.println(command);
    Serial.println(data);
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

