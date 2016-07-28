void setup() {
  CommInitialize();
}

void loop() {
  int requestId;
  if (CommTask(&requestId))
  {
    Serial.println(requestId);
  }
}

void CommInitialize()
{
  Serial.begin(115200);
  Serial.setTimeout(5000);
}

boolean CommTask(int* requestId)
{
  if (Serial.available() <= 0) return false;
  if (Serial.read() != ':') return false;
  
  String message = Serial.readStringUntil('\n');
  if (message.length() < 4 + 1 + 3) return false;

  int i = 0;
  String senderId = message.substring(i, i + 2); i += 2;
  String command = message.substring(i, i + 2); i += 2;
  String data = message.substring(i, i + message.length() - (4 + 3)); i += message.length() - (4 + 3);
  String footer = message.substring(i, i + 2); i += 2;
  String delim = message.substring(i, i + 1); i += 1;

  if (senderId != "00") return false;
  if (command != "00") return false;
  if (delim != "\r") return false;

  if (data.length() != 2) return false;
  if (sscanf(data.c_str(), "%x", requestId) != 1) return false;

  return true;
}

