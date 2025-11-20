#ifndef Controlib_h
#define Controlib_h

#include <Arduino.h>
#include <PRIZM.h>
#include <TELEOP.h>

enum ControlType {
  BUTTONS,
  LEFT_STICK, 
  RIGHT_STICK,
  DPAD,
  BUMPERS,
  TRIGGERS,
  JOYSTICK_PRESS,
  TOUCHPAD,
  NONE
};

class ServoControl {
  public:
    ServoControl(PRIZM& prizmRef, PS4& ps4Ref);
    
    // X-axis methods
    void xByButtons(int& x);
    void xByLeftStick(int& x);
    void xByRightStick(int& x);
    void xByDPAD(int& x);
    void xByBumpers(int& x);
    void xByTriggers(int& x);
    void xByJoystickPress(int& x);
    void xByTouchpad(int& x);
    
    // Y-axis methods
    void yByButtons(int& y);
    void yByLeftStick(int& y);
    void yByRightStick(int& y);
    void yByDPAD(int& y);
    void yByBumpers(int& y);
    void yByTriggers(int& y);
    void yByJoystickPress(int& y);
    void yByTouchpad(int& y);
    
    //Drive methods
    void dByButtons(int& d);
    void dByLeftStick(int& d);
    void dByRightStick(int& d);
    void dByDPAD(int& d);
    void dByTriggers(int& d);
    void dByTouchpad(int& d);
    
  private:
    PRIZM& prizm;
    PS4& ps4;
    unsigned long lastUpdate;
    static const unsigned long UPDATE_INTERVAL = 50;
    
    ControlType xControl;
    ControlType yControl;
    ControlType dControl;
    
    bool canUpdate();
    bool checkConflict(ControlType newControl, char axis);
};

#endif