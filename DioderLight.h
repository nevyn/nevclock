
typedef struct {
  int rPin, gPin, bPin;
  int r, g, b;
} DioderLight;

void DioderLight_init(DioderLight *light, int rPin, int gPin, int bPin) {
  light->rPin = rPin;
  light->gPin = gPin;
  light->bPin = bPin;
  light->r = light->g = light->b = 0;
}

int DioderLight_redPin(DioderLight *light) {
  return light->rPin; 
}
int DioderLight_greenPin(DioderLight *light) {
  return light->gPin; 
}
int DioderLight_bluePin(DioderLight *light) {
  return light->bPin;
}

void DioderLight_setRed(DioderLight *light, int red) {
  if(light->r == red) return;
  light->r = red;
  analogWrite(DioderLight_redPin(light), red);
}
void DioderLight_setGreen(DioderLight *light, int green) {
  if(light->g == green) return;
  light->g = green;
  analogWrite(DioderLight_greenPin(light), green);
}
void DioderLight_setBlue(DioderLight *light, int blue) {
  if(light->b == blue) return;
  light->b = blue;
  analogWrite(DioderLight_bluePin(light), blue);
}
void DioderLight_setRGB(DioderLight *light, int red, int green, int blue) {
  DioderLight_setRed(light, red);
  DioderLight_setGreen(light, green);
  DioderLight_setBlue(light, blue);
}
void DioderLight_setWhite(DioderLight *light, float white) {
  DioderLight_setRGB(light, white, white, white);
}
