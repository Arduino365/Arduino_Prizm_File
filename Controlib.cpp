#include "Controlib.h"

ServoControl::ServoControl(PRIZM& prizmRef, PS4& ps4Ref) 
  : prizm(prizmRef), ps4(ps4Ref), lastUpdate(0), xControl(NONE), yControl(NONE), dControl(NONE), speedLevel(0), lastCrossState(false) {}

void ServoControl::speedControl() {
  bool currentCrossState = ps4.Button(CROSS);

  if(currentCrossState && !lastCrossState){
    speedLevel++;
    if(speedLevel > 2){
      speedLevel = 0;
    }
    
    Serial.print("Speed Level: ");
    Serial.println(speedLevel);
  }
  lastCrossState = currentCrossState;
}

int ServoControl::getSpeedLevel() {
  return speedLevel;
}

float ServoControl::getSpeedMultiplier() {
  switch(speedLevel){
    case 1:
      return 0.5f;  // 50% speed
    case 2:
      return 0.75f; // 75% speed
    default:
      return 1.0f;  // 100% speed
  }
}

bool ServoControl::canUpdate() {
  unsigned long now = millis();
  if (now - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = now;
    return true;
  }
  return false;
}

bool ServoControl::checkConflict(ControlType newControl, char axis) {
  if (newControl == NONE) return false;
  
  // Check if this control is already used by other axes
  if ((axis != 'x' && xControl == newControl) ||
      (axis != 'y' && yControl == newControl) ||
      (axis != 'd' && dControl == newControl)) {
    
    Serial.print("ERROR: Control type already assigned to another axis! ");
    Serial.print("Cannot assign to '");
    Serial.print(axis);
    Serial.println("' axis.");
    return true;
  }
  return false;
}

// X-AXIS METHODS
void ServoControl::xByButtons(int& x) {
  if (checkConflict(BUTTONS, 'x')) return;
  xControl = BUTTONS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(SQUARE)) {
    x = constrain(x - 10, 0, 180);
  }
  else if (ps4.Button(CIRCLE)) {
    x = constrain(x + 10, 0, 180);
  }
}

void ServoControl::xByLeftStick(int& x) {
  if (checkConflict(LEFT_STICK, 'x')) return;
  xControl = LEFT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(LX) > 10) {
    x = constrain(x + 10, 0, 180);
  }
  else if (ps4.Motor(LX) < -10) {
    x = constrain(x - 10, 0, 180);
  }
}

void ServoControl::xByRightStick(int& x) {
  if (checkConflict(RIGHT_STICK, 'x')) return;
  xControl = RIGHT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(RX) > 10) {
    x = constrain(x + 10, 0, 180);
  }
  else if (ps4.Motor(RX) < -10) {
    x = constrain(x - 10, 0, 180);
  }
}

void ServoControl::xByDPAD(int& x) {
  if (checkConflict(DPAD, 'x')) return;
  xControl = DPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(LEFT)) {
    x = constrain(x - 10, 0, 180);
  }
  else if (ps4.Button(RIGHT)) {
    x = constrain(x + 10, 0, 180);
  }
}

void ServoControl::xByBumpers(int& x) {
  if (checkConflict(BUMPERS, 'x')) return;
  xControl = BUMPERS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L1)) {
    x = constrain(x - 10, 0, 180);
  }
  else if (ps4.Button(R1)) {
    x = constrain(x + 10, 0, 180);
  }
}

void ServoControl::xByTriggers(int& x) {
  if (checkConflict(TRIGGERS, 'x')) return;
  xControl = TRIGGERS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L2)) {
    x = constrain(x - 10, 0, 180);
  }
  else if (ps4.Button(R2)) {
    x = constrain(x + 10, 0, 180);
  }
}

void ServoControl::xByJoystickPress(int& x) {
  if (checkConflict(JOYSTICK_PRESS, 'x')) return;
  xControl = JOYSTICK_PRESS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L3)) {
    x = constrain(x - 10, 0, 180);
  }
  else if (ps4.Button(R3)) {
    x = constrain(x + 10, 0, 180);
  }
}

void ServoControl::xByTouchpad(int& x) {
  if (checkConflict(TOUCHPAD, 'x')) return;
  xControl = TOUCHPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.Touchpad(TOUCHX) <= 960) {
    x = constrain(x - 10, 0, 180);
  }
  else if (ps4.Touchpad(TOUCHX) > 960) {
    x = constrain(x + 10, 0, 180);
  }
}

// Y-AXIS METHODS
void ServoControl::yByButtons(int& y) {
  if (checkConflict(BUTTONS, 'y')) return;
  yControl = BUTTONS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(CROSS)) {
    y = constrain(y - 10, 0, 180);
  }
  else if (ps4.Button(TRIANGLE)) {
    y = constrain(y + 10, 0, 180);
  }
}

void ServoControl::yByLeftStick(int& y) {
  if (checkConflict(LEFT_STICK, 'y')) return;
  yControl = LEFT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(LY) > 10) {
    y = constrain(y + 10, 0, 180);
  }
  else if (ps4.Motor(LY) < -10) {
    y = constrain(y - 10, 0, 180);
  }
}

void ServoControl::yByRightStick(int& y) {
  if (checkConflict(RIGHT_STICK, 'y')) return;
  yControl = RIGHT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(RY) > 10) {
    y = constrain(y + 10, 0, 180);
  }
  else if (ps4.Motor(RY) < -10) {
    y = constrain(y - 10, 0, 180);
  }
}

void ServoControl::yByDPAD(int& y) {
  if (checkConflict(DPAD, 'y')) return;
  yControl = DPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(DOWN)) {
    y = constrain(y - 10, 0, 180);
  }
  else if (ps4.Button(UP)) {
    y = constrain(y + 10, 0, 180);
  }
}

void ServoControl::yByBumpers(int& y) {
  if (checkConflict(BUMPERS, 'y')) return;
  yControl = BUMPERS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L1)) {
    y = constrain(y - 10, 0, 180);
  }
  else if (ps4.Button(R1)) {
    y = constrain(y + 10, 0, 180);
  }
}

void ServoControl::yByTriggers(int& y) {
  if (checkConflict(TRIGGERS, 'y')) return;
  yControl = TRIGGERS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L2)) {
    y = constrain(y - 10, 0, 180);
  }
  else if(ps4.Button(R2)){
    y = constrain(y + 10, 0, 180);
  }
}

void ServoControl::yByJoystickPress(int& y) {
  if (checkConflict(JOYSTICK_PRESS, 'y')) return;
  yControl = JOYSTICK_PRESS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L3)) {
    y = constrain(y - 10, 0, 180);
  }
  else if(ps4.Button(L3)){
    y = contrain(y+10, 0, 180);
  }
}

void ServoControl::yByTouchpad(int& y) {
  if (checkConflict(TOUCHPAD, 'y')) return;
  yControl = TOUCHPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.TOUCHPAD(TOUCHY) > 470){
    y = constrain(y + 10, 0, 180);
  }
  else if(ps4.TOUCHPAD(TOUCHY) <= 470){
    y = constrain(y - 10, 0, 180);
  }
}

// D-AXIS METHODS
void ServoControl::dByButtons(int& d) { //done
  if (checkConflict(BUTTONS, 'd')) return;
  dControl = BUTTONS;
  
  if (!canUpdate()) return;
  

  if (ps4.Button(TRIANGLE)) {
    prizm.setMotorPowers(50,50);
  }
 
  else if (ps4.Button(CROSS)) {
    prizm.setMotorPowers(-50,-50);
  }
  
  else if (ps4.Button(SQUARE)) {
    prizm.setMotorPowers(-50, 50); 
    return;
  }

  else if (ps4.Button(CIRCLE)) {
    prizm.setMotorPowers(50, -50);
    return;
  }

  else {
    prizm.setMotorPowers(0,0);
  }
  
void ServoControl::dByLeftStick(int& d) { //done
  if (checkConflict(LEFT_STICK, 'd')) return;
  dControl = LEFT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(LX) > 10) {
    prizm.setMotorPowers(50,-50);
  }
  else if (ps4.Motor(LX) < -10) {
    prizm.setMotorPowers(-50,50);
  }
  else if (ps4.Motor(LY) > 10){
    prizm.setMotorPowers(50,50);
  }
  else if (ps4.Motor(LY) < -10){
    prizm.setMotorPowers(-50,-50);
  }
  else{
    prizm.setMotorPowers(0,0);
  }
}

void ServoControl::dByRightStick(int& d) { //done
  if (checkConflict(RIGHT_STICK, 'd')) return;
  dControl = RIGHT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(RX) > 10) {
    prizm.setMotorPowers(50,-50);
  }
  else if (ps4.Motor(RX) < -10) {
    prizm.setMotorPowers(-50,50);
  }
  else if (ps4.Motor(RY) > 10){
    prizm.setMotorPowers(50,50);
  }
  else if (ps4.Motor(RY) < -10){
    prizm.setMotorPowers(-50,-50);
  }
  else{
    prizm.setMotorPowers(0,0);
  }
}

void ServoControl::dByDPAD(int& d) { //done
  if (checkConflict(DPAD, 'd')) return;
  dControl = DPAD;
  
  if (!canUpdate()) return;
  
 
  if (ps4.Button(UP)) {
    prizm.setMotorPowers(50,50)
  }
  
  else if (ps4.Button(DOWN)) {
    prizm.setMotorPowers(-50,-50)
  }

  else if (ps4.Button(RIGHT)) {
    prizm.setMotorPowers(-50, 50); 
    return; 
  }
  
  else if (ps4.Button(LEFT)) {
    prizm.setMotorPowers(50, -50);
    return;
  }

  else {
    prizm.setMotorPowers(0,0);
  }
  
void ServoControl::dByTriggers(int& d) { //done
  if (checkConflict(TRIGGERS, 'd')) return;
  dControl = TRIGGERS;

  if (!canUpdate()) return;
  
  if (ps4.Button(L2)) {
    prizm.setMotorPowers(50,50);
  }
  else if (ps4.Button(R2)) {
    prizm.setMotorPowers(-50,-50);
  }
  else if (ps4.Button(L1)){
    prizm.setMotorPowers(-50,50);
  }
  else if (ps4.Button(R1)){
    prizm.setMotorPowers(50,-50);
  }
  else{
    prizm.setMotorPowers(0,0);
  }
}


void ServoControl::dByTouchpad(int& d) { //done
  if (checkConflict(TOUCHPAD, 'd')) return;
  dControl = TOUCHPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.Touchpad(TOUCHX) <= 960) {
    prizm.setMotorPowers(-50,50);
  }
  else if (ps4.Touchpad(TOUCHX) > 960) {
    prizm.setMotorPowers(50,-50);
  }
  else if (ps4.Touchpad(TOUCHY) > 470){
    prizm.setMotorPowers(50,50);
  }
  else if (ps4.Touchpad(TOUCHY) < 470){
    prizm.setMotorPowers(-50,-50);
  }
}

  