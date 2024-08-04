// потенциометр: левый - плюс; центральный - логика; правый - минус

class Doll {
  private:
    int minVal;
    int maxVal;
    uint8_t pin;

  public:
    Doll(int minimumVal, uint8_t pinPotentiometer) {
      minVal = minimumVal;
      maxVal = minimumVal + 20;
      pin = pinPotentiometer;

      pinMode(pin, INPUT);
    }

    bool isOpen() {
      int currentVal = analogRead(pin);
      Serial.println(currentVal);
      if (currentVal >= minVal && currentVal <= maxVal) {
        return true;
      }
      else return false;
    }
};

Doll I_AM(300, A0);
Doll VOODOO(400, A1);
Doll BEAVER(500, A2);
Doll CLOWN(600, A3);
Doll GIRL(700, A4);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(100);
  if (I_AM.isOpen() && VOODOO.isOpen() && BEAVER.isOpen() && CLOWN.isOpen() && GIRL.isOpen()) {
    // открыть ящик
  }
}
