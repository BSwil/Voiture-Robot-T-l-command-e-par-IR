#include <IRremote.h>

int Recepteur = 3;

// moteur
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

void setup() {
  IrReceiver.begin(Recepteur);
  Serial.begin(9600);

  // Configurer les pins moteurs en sortie
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stop(); // arrêter le moteur au départ
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;

    switch (code) {
      case 0xFD02BF00: // AVANCE
        Serial.println("AVANCE");
        avance();
        break;

      case 0xFE01BF00: // RECULE
        Serial.println("RECULE");
        recule();
        break;

      case 0xFF00BF00: // STOP
        Serial.println("STOP");
        stop();
        break;

      case 0xF10EBF00: // A GAUCHE
        Serial.println("A GAUCHE");
        gauche();
        break;

      case 0xF20DBF00: // A DROITE
        Serial.println("A DROITE");
        droite();
        break;
    }

    IrReceiver.resume();
  }
}

// ---------------- FONCTIONS MOUVEMENT ----------------

void avance() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void recule() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void gauche() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500);
  avance();
}

void droite() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(500);
  avance();
}
