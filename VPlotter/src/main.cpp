#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

String command;
char separator = 32;

void parseCommand(String msg)
{
  msg.trim();
  String command;
  String l_offset;
  String r_offset;
  String l_vals;
  String r_vals;

  int index [5];

  int len = msg.length();

  if (msg.startsWith("m"))
  {
    command = "move";
  }
  if (msg.startsWith("d"))
  {
    command = "draw";
  }  
  int j = 0;
  for (int i = 0; i<=len; i++)
  {
    if (msg[i] == separator)
    {
      Serial.println("Komma at: " + String(i));
      index[j] = i;
      j++;
    }
  }
  Serial.println("End: " + String(msg.length()));

  for (int i = 0; i < 4; i++)
  {
    Serial.print(String(index[i]));
    Serial.print(",");
  }
  Serial.println();

  l_offset = msg.substring(index[0],index[1]).toInt();
  r_offset = msg.substring(index[2],index[3]).toInt();
  l_vals = msg.substring(index[1], index[2]);
  r_vals = msg.substring(index[3]);

  Serial.println("Command: " + command);
  Serial.println("Offset left: " + String(l_offset));
  Serial.println("Offset right: " + String(r_offset));
  Serial.println("Steps left: " + l_vals);
  Serial.println("Steps right: " + r_vals);

}
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5000);
  Serial.println("Test\n");
}

void loop() {
  if (Serial.available())
  {
    char c = Serial.read();

    if (c == '\n')
    {
      parseCommand(command);
      command = "";
    }
    else
    {
      command += c;
    }
    
  }
}

