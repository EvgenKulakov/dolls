// потенциометр: левый - плюс; центральный - логика; правый - минус

class Doll {
  private:
    int minVal;
    int maxVal;
    uint8_t pin;
    String name;

  public:
    Doll(int minimumVal, int maximumVal, uint8_t pinPotentiometer, String nameVal) {
      minVal = minimumVal;
      maxVal = maximumVal;
      pin = pinPotentiometer;
      name = nameVal;

      pinMode(pin, INPUT);
    }

    bool isOpen() {
      int currentVal = analogRead(pin);
      // Serial.println(name + currentVal);
      if (currentVal >= minVal && currentVal <= maxVal) {
        return true;
      }
      else return false;
    }
};

Doll I_AM(122, 132, A0, "I_AM");
Doll VOODOO(780, 790, A2, "VOODOO");
Doll BEAR(560, 570, A4, "BEAR");
Doll CLOWN(460, 470, A6, "CLOWN");
Doll GIRL(984, 994, A7, "GIRL");

bool lock = HIGH; // HIGH - lock активен, ящик закрыт
#define PIN_LOCK 4

void setup() {
  pinMode(PIN_LOCK, OUTPUT);
  digitalWrite(PIN_LOCK, lock);
  // Serial.begin(9600);
}

void loop() {
  delay(100);
  bool open = I_AM.isOpen() && VOODOO.isOpen() && BEAR.isOpen() && CLOWN.isOpen() && GIRL.isOpen();
  if (open == lock) {
    delay(800);
    bool openAfterPaused = I_AM.isOpen() && VOODOO.isOpen() && BEAR.isOpen() && CLOWN.isOpen() && GIRL.isOpen();
    if (openAfterPaused == lock) {
      lock = !lock;
      digitalWrite(PIN_LOCK, lock);
    }
  }
}
