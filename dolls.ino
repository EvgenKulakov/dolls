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
Doll BEAR(500, A2);
Doll CLOWN(600, A3);
Doll GIRL(700, A4);

bool lock = HIGH; // HIGH - lock активен, ящик закрыт
#define PIN_LOCK 4

void setup() {
  pinMode(PIN_LOCK, OUTPUT);
  digitalWrite(PIN_LOCK, lock);
  Serial.begin(9600);
}

void loop() {
  delay(100);
  bool open = I_AM.isOpen() && VOODOO.isOpen() && BEAR.isOpen() && CLOWN.isOpen() && GIRL.isOpen();
  Serial.println(open);
  Serial.println(lock);
  if (open == true && lock == HIGH || open == false && lock == LOW) {
    lock = !lock;
    digitalWrite(PIN_LOCK, lock);
  }
}
