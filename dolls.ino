// потенциометр: левый - плюс; центральный - логика; правый - минус

class Doll {
  private:
    uint8_t pin;
    int minWeight;
    int maxWeight;
    String name;
    int startVal;
    int minVal;
    int maxVal;
    
  public:
    Doll(uint8_t pinPotentiometer, int minWeightVal, int maxWeightVal, String nameVal) {
      pin = pinPotentiometer;
      minWeight = minWeightVal;
      maxWeight = maxWeightVal;
      name = nameVal;
    }

    void init() {
      pinMode(pin, INPUT);
      delay(200);
      startVal = analogRead(pin);
      minVal = startVal + minWeight;
      maxVal = startVal + maxWeight;
    }

    bool isOpen() {
      int currentVal = analogRead(pin);
      // Serial.println(name + " startVal: " + startVal + " current: " + currentVal);
      if (currentVal >= minVal && currentVal <= maxVal) {
        return true;
      }
      else return false;
    }
};

Doll I_AM(A0, 19, 24, "I_AM");
Doll VOODOO(A2, 14, 19, "VOODOO");
Doll BEAR(A4, 20, 25, "BEAR");
Doll CLOWN(A6, 15, 23, "CLOWN");
Doll GIRL(A7, -38, -32, "GIRL");

bool lock = HIGH; // HIGH - lock активен, ящик закрыт
#define PIN_LOCK 4

void setup() {
  pinMode(PIN_LOCK, OUTPUT);
  I_AM.init();
  VOODOO.init();
  BEAR.init();
  CLOWN.init();
  GIRL.init();
  delay(100);
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
