typedef int BOOL;

typedef struct {
  int pin;
  BOOL last_state;
  int state_change_at;
  BOOL sent_pressed;
} Button;



void Button_init(Button *b, int pin) {
  b->pin = pin;
  pinMode(b->pin, INPUT);
  
  b->last_state = false;
  b->state_change_at = millis();
  b->sent_pressed = false;
};

BOOL Button_wasPressedNow(Button *b) {
  BOOL ret = false;
  
  BOOL pressedNow = digitalRead(b->pin);
  
  if(pressedNow != b->last_state) {
    b->state_change_at = millis();
  }
  
  if((millis() - b->state_change_at) > 50) {
    ret = pressedNow && !b->sent_pressed;
    b->sent_pressed = pressedNow;
  }
  
  b->last_state = pressedNow;
  
  return ret;
}
