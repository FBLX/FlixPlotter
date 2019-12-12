#include <Arduino.h>
#include <SimpleCLI.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include "buffer.h"

unsigned int motorPositionLeft;
unsigned int motorPositionRight;
unsigned int maxValue = 2147483646;
boolean penState = false;

AccelStepper motorLeft(1,8,9);
AccelStepper motorRight(1,11,12);
MultiStepper motors;

int maxSpeed = 400;

SimpleCLI cli;

Buffer commandBuffer;

void print(Element *a)
{
  Serial.print("    printing: ");
  Serial.print(a->pos[0]);
  Serial.print("   ");
  Serial.println(a->pos[1]);
  unsigned long g = a->pos[0];
  unsigned long h = a->pos[1];
  long coordinates [2] = {g,h};
  motors.moveTo(coordinates);
  motors.runSpeedToPosition();
  delay(50);
  
}

void moveCallback(cmd* c)
{
  Command cmd(c);
  Argument left = cmd.getArg("l");
  Argument right = cmd.getArg("r");

  String leftVal = left.getValue();
  String rightVal = right.getValue();

  unsigned long ll = leftVal.toInt();
  unsigned long rr = rightVal.toInt();

  commandBuffer.add(ll,rr);



}

void drawCallback(cmd* c)
{
  Command cmd(c);
  Argument left = cmd.getArg("l");
  Argument right = cmd.getArg("r");

  String leftVal = left.getValue();
  String rightVal = right.getValue();

  unsigned long ll = leftVal.toInt();
  unsigned long rr = rightVal.toInt();

  commandBuffer.add(ll,rr, true);


}

void setCallback(cmd* c)
{
  Command cmd(c);
  Argument left = cmd.getArg("l");
  Argument right = cmd.getArg("r");

  String leftVal = left.getValue();
  String rightVal = right.getValue();

  if (leftVal != "$" and rightVal != "$")
  {
    motorPositionLeft = leftVal.toInt();
    motorPositionRight = rightVal.toInt();
    if (leftVal.toInt() > maxValue or rightVal.toInt() > maxValue)
    {
      Serial.println("Maximum Value exceeded");
    }
    else
    {
      Serial.println("   motor positions set to: " + leftVal + "|" + rightVal);
      motorLeft.setCurrentPosition(motorPositionLeft);
      motorRight.setCurrentPosition(motorPositionRight);
    }
  }
  else
  {
    Serial.println("   ...error");
  }
}
void helpCallback(cmd* c)
{
  Serial.println("Help:");
  Serial.println(cli.toString());
}
void infoCallback(cmd* c)
{
  Serial.println("Info:");
  Serial.println("Current Position left: " + String(motorPositionLeft));
  Serial.println("Current Position right: "+ String(motorPositionRight));
  Serial.println("Max Motor Speed: " + String(maxSpeed));
  commandBuffer.show();

}
void runCallback(cmd* c)
{
  if (motorPositionLeft == 0 and motorPositionRight == 0)
  {
    Serial.println("!!!Please set Motor Positions!!!");
  }
  else
  {
    if (commandBuffer.len() == 0)
    {
      Serial.println("nothing to do");
    }
    else
    {
      Element *p = commandBuffer.pop();
      while (p != NULL)
      {
        print(p);
        p = commandBuffer.pop();
      }      
    }
    
  }
}

Command move;
Command draw;
Command set;
Command help;
Command info;
Command run;

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(5000);
  delay(2000);

  move = cli.addCmd("m/ove", moveCallback);
  draw = cli.addCmd("d/raw", drawCallback);
  set = cli.addCmd("s/et", setCallback);
  help = cli.addCmd("h/elp", helpCallback);
  info = cli.addCmd("i/nfo", infoCallback);
  run = cli.addCmd("r/un", runCallback);


  move.addArg("l", "$");
  move.addArg("r", "$");

  draw.addArg("l", "$");
  draw.addArg("r", "$");

  set.addArg("l", "$");
  set.addArg("r", "$");

  motors.addStepper(motorLeft);
  motors.addStepper(motorRight);
  motorLeft.setMaxSpeed(maxSpeed);
  motorRight.setMaxSpeed(maxSpeed);
  motorRight.setPinsInverted(true, false, false);
}

void loop() {
  if (Serial.available()) 
  {
    String input = Serial.readStringUntil('\n');
    Serial.println("$ " + input);
    cli.parse(input);
  }

  if (cli.errored())
  {
    CommandError e = cli.getError();
    Serial.println("Error: " + e.toString());
    Serial.println();
  }
}