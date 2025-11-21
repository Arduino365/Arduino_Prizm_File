#include "Controlib.h"

RobotControl::RobotControl(PRIZM& prizmRef, PS4& ps4Ref) 
  : prizm(prizmRef), ps4(ps4Ref), lastUpdate(0), xControl(NONE), yControl(NONE), dControl(NONE), speedLevel(0), lastShareState(false), speedOn(false) {}

void RobotControl::speedControl() {
  bool currentCrossState = ps4.Button(SHARE);

  if(currentCrossState && !lastCrossState){
    speedLevel++;
    if(speedLevel > 2){
      speedLevel = 0;
    }
    else if(speedLevel == 0){
      speedOn = false;
    }
    else if(0 < speedLevel < 2){
      speedOn = true;
    }
    Serial.print("Speed Level: ");
    Serial.println(speedLevel);
  }
  lastCrossState = currentCrossState;
}

int RobotControl::getSpeedLevel() {
  return speedLevel;
}

float RobotControl::getSpeedMultiplier() {
  switch(speedLevel){
    case 1:
      return 0.5f;  // 50% speed
    case 2:
      return 0.75f; // 75% speed
    default:
      return 1.0f;  // 100% speed
  }
}

bool RobotControl::canUpdate() {
  unsigned long now = millis();
  if (now - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = now;
    return true;
  }
  return false;
}

bool RobotControl::checkConflict(ControlType newControl, char axis) {
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
void RobotControl::xByButtons(int& x) {
  if (checkConflict(BUTTONS, 'x')) return;
  xControl = BUTTONS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(SQUARE)) {
    if(speedOn == false){
      x = constrain(x - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x - change, 0, 180);
    }
  }
  else if (ps4.Button(CIRCLE)) {
    if(speedOn == false){
      x = constrain(x + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x + change, 0, 180);
    }

}

void RobotControl::xByLeftStick(int& x) {
  if (checkConflict(LEFT_STICK, 'x')) return;
  xControl = LEFT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(LX) > 10) {
    if(speedOn == false){
      x = constrain(x + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x + change, 0, 180);
    }

  else if (ps4.Motor(LX) < -10) {
    if(speedOn == false){
      x = constrain(x - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x - change, 0, 180);
    }
}

void RobotControl::xByRightStick(int& x) {
  if (checkConflict(RIGHT_STICK, 'x')) return;
  xControl = RIGHT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(RX) > 10) {
    if(speedOn == false){
      x = constrain(x + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x + change, 0, 180);
    }

  else if (ps4.Motor(RX) < -10) {
    if(speedOn == false){
      x = constrain(x - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x - change, 0, 180);
    }
}

void RobotControl::xByDPAD(int& x) {
  if (checkConflict(DPAD, 'x')) return;
  xControl = DPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(LEFT)) {
    if(speedOn == false){
      x = constrain(x - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x - change, 0, 180);
    }
  else if (ps4.Button(RIGHT)) {
    if(speedOn == false){
      x = constrain(x + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x + change, 0, 180);
    }
}

void RobotControl::xByBumpers(int& x) {
  if (checkConflict(BUMPERS, 'x')) return;
  xControl = BUMPERS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L1)) {
    if(speedOn == false){
      x = constrain(x - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x - change, 0, 180);
    }
  else if (ps4.Button(R1)) {
   if(speedOn == false){
      x = constrain(x + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x + change, 0, 180);
    }
}

void RobotControl::xByTriggers(int& x) {
  if (checkConflict(TRIGGERS, 'x')) return;
  xControl = TRIGGERS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L2)) {
    if(speedOn == false){
      x = constrain(x - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x - change, 0, 180);
    }
  else if (ps4.Button(R2)) {
    if(speedOn == false){
      x = constrain(x + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x + change, 0, 180);
    }
}

void RobotControl::xByJoystickPress(int& x) {
  if (checkConflict(JOYSTICK_PRESS, 'x')) return;
  xControl = JOYSTICK_PRESS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L3)) {
    if(speedOn == false){
      x = constrain(x - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x - change, 0, 180);
    }
  else if (ps4.Button(R3)) {
    if(speedOn == false){
      x = constrain(x + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x + change, 0, 180);
    }
}

void RobotControl::xByTouchpad(int& x) {
  if (checkConflict(TOUCHPAD, 'x')) return;
  xControl = TOUCHPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.Touchpad(TOUCHX) <= 960) {
    if(speedOn == false){
      x = constrain(x - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x - change, 0, 180);
    }
  else if (ps4.Touchpad(TOUCHX) > 960) {
    if(speedOn == false){
      x = constrain(x + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      x = constrain(x + change, 0, 180);
    }
}

// Y-AXIS METHODS
void RobotControl::yByButtons(int& y) {
  if (checkConflict(BUTTONS, 'y')) return;
  yControl = BUTTONS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(CROSS)) {
    if(speedOn == false){
      y = constrain(y - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y - change, 0, 180);
    }

  else if (ps4.Button(TRIANGLE)) {
    if(speedOn == false){
      y = constrain(y + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y + change, 0, 180);
    }
}

void RobotControl::yByLeftStick(int& y) {
  if (checkConflict(LEFT_STICK, 'y')) return;
  yControl = LEFT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(LY) > 10) {
       if(speedOn == false){
      y = constrain(y + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y + change, 0, 180);
    }

  else if (ps4.Motor(LY) < -10) {
    if(speedOn == false){
      y = constrain(y - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y - change, 0, 180);
    }
}

void RobotControl::yByRightStick(int& y) {
  if (checkConflict(RIGHT_STICK, 'y')) return;
  yControl = RIGHT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(RY) > 10) {
    if(speedOn == false){
      y = constrain(y + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y + change, 0, 180);
    }

  else if (ps4.Motor(RY) < -10) {
    if(speedOn == false){
      y = constrain(y - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y - change, 0, 180);
    }
}

void RobotControl::yByDPAD(int& y) {
  if (checkConflict(DPAD, 'y')) return;
  yControl = DPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(DOWN)) {
    if(speedOn == false){
      y = constrain(y - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y - change, 0, 180);
    }
  else if (ps4.Button(UP)) {
    if(speedOn == false){
      y = constrain(y + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y + change, 0, 180);
    }
}

void RobotControl::yByBumpers(int& y) {
  if (checkConflict(BUMPERS, 'y')) return;
  yControl = BUMPERS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L1)) {
       if(speedOn == false){
      y = constrain(y - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y - change, 0, 180);
    }
  else if (ps4.Button(R1)) {
        if(speedOn == false){
      y = constrain(y + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y + change, 0, 180);
    }
}

void RobotControl::yByTriggers(int& y) {
  if (checkConflict(TRIGGERS, 'y')) return;
  yControl = TRIGGERS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L2)) {
    if(speedOn == false){
      y = constrain(y - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y - change, 0, 180);
    }

  else if(ps4.Button(R2)){
    if(speedOn == false){
      y = constrain(y + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y + change, 0, 180);
    }
}

void RobotControl::yByJoystickPress(int& y) {
  if (checkConflict(JOYSTICK_PRESS, 'y')) return;
  yControl = JOYSTICK_PRESS;
  
  if (!canUpdate()) return;
  
  if (ps4.Button(L3)) {
    if(speedOn == false){
      y = constrain(y - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y - change, 0, 180);
    }

  else if(ps4.Button(R3)){
    if(speedOn == false){
      y = constrain(y + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y + change, 0, 180);
    }
}

void RobotControl::yByTouchpad(int& y) {
  if (checkConflict(TOUCHPAD, 'y')) return;
  yControl = TOUCHPAD;
  
  if (!canUpdate()) return;
  
  if (ps4.TOUCHPAD(TOUCHY) > 470){
    if(speedOn == false){
      y = constrain(y + 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y + change, 0, 180);
    }

  else if(ps4.TOUCHPAD(TOUCHY) <= 470){
    if(speedOn == false){
      y = constrain(y - 10, 0, 180);
    }
    else{
      change = 10 * getSpeedMultiplier();
      y = constrain(y - change, 0, 180);
    }
}

// D-AXIS METHODS
void RobotControl::dByButtons(int& d) { //done
  if (checkConflict(BUTTONS, 'd')) return;
  dControl = BUTTONS;
  if (!canUpdate()) return;
  

  if (ps4.Button(TRIANGLE)) {
    if (speedOn == true) {
      d = 50 * getSpeedMultiplier();
      prizm.setMotorPowers(d,d);
    }
    else {
      d = 50;
      prizm.setMotorPowers(d,d);
    }
  }
    
  else if (ps4.Button(CROSS)) {
    if (speedOn == true){
      d = 50 * getSpeedMultiplier();
      prizm.setMotorPowers(-d,-d);
    }
    else {
      d = 50;
      prizm.setMotorPowers(-d,-d);
    }
  }
    
  else if (ps4.Button(SQUARE)) {
    if (speedOn == true){
      d = 50 * getSpeedMultiplier();
      prizm.setMotorPowers(-d,d);
    }
    else {
      d = 50
      prizm.setMotorPowers(-d, d); 
      return;
    }
  }

  else if (ps4.Button(CIRCLE)) {
    if (speedOn == true){
      d = 50 * getSpeedMultiplier();
      prizm.setMotorPowers(d,-d);
    }
    else {
      d = 50;
      prizm.setMotorPowers(d, -d);
      return;
    }
  }
    
  else {
    d = 0;
    prizm.setMotorPowers(d,d);
  }
  
void RobotControl::dByLeftStick(int& d) { //done
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

void RobotControl::dByRightStick(int& d) { //done
  if (checkConflict(RIGHT_STICK, 'd')) return;
  dControl = RIGHT_STICK;
  
  if (!canUpdate()) return;
  
  if (ps4.Motor(RX) > 10) {
    if (speedOn == true){
      d = 50 * getSpeedMultiplier();
      prizm.setMotorPowers(d,-d);
    }
    else {
      d = 50;
      prizm.setMotorPowers(d,-d);
    }
  }
    
  else if (ps4.Motor(RX) < -10) {
    if (speedOn == true){
      d = 50 * getSpeedMultiplier();
      prizm.setMotorPowers(-d,d);
    }
    else {
      d = 50;
      prizm.setMotorPowers(-d,d);
    }
  }
    
  else if (ps4.Motor(RY) > 10){
    if (speedOn == true){
      d = 50 * getSpeedMultiplier();
      prizm.setMotorPowers(d,d);
    }
    else {
      d = 50;
      prizm.setMotorPowers(d,d);
    }
  }
    
  else if (ps4.Motor(RY) < -10){
    if (speedOn == true) {
      d = 50 * getSpeedMultiplier();
      prizm.setMotorPowers(-d,-d);
    }
    else {
      d = 50;
      prizm.setMotorPowers(-d,-d);
    }
  }
    
  else{
    d = 0;
    prizm.setMotorPowers(d,d);
  }
}
w
void RobotControl::dByDPAD(int& d) { //done
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
  
void RobotControl::dByTriggers(int& d) { //done
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


void RobotControl::dByTouchpad(int& d) { //done
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

  
