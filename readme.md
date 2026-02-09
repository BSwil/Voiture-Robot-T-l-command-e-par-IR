# Projet Voiture Robot Télécommandée par IR

Ce projet permet de contrôler une **voiture robot** équipée de **4 moteurs à courant continu (CC)** et d’un **châssis**, à l’aide d’une **télécommande infrarouge (IR)** et d’un microcontrôleur (Arduino). La voiture peut **avancer, reculer, tourner à gauche, tourner à droite** et s’arrêter selon les commandes envoyées par la télécommande.

---

## Matériel requis

- Arduino (Uno, Nano, Mega, etc.)
- Module récepteur IR (ex. TSOP38238)
- Télécommande IR compatible
- Module moteur L298N pour contrôler 4 moteurs CC
- 4 moteurs à courant continu
- Châssis de voiture robot
- Fils de connexion
- Source d’alimentation adaptée

---

## Schéma de connexion

| Composant    | Pin Arduino |
| ------------ | ----------- |
| Récepteur IR | D3          |
| IN1          | D4          |
| IN2          | D5          |
| IN3          | D6          |
| IN4          | D7          |

> Le L298N permet de contrôler 4 moteurs CC. Assurez-vous que le module moteur reçoit une alimentation correcte selon les moteurs utilisés.

---

## Fonctionnalités

- **AVANCE** : fait avancer la voiture.
- **RECULE** : fait reculer la voiture.
- **STOP** : arrête la voiture.
- **A GAUCHE** : tourne la voiture vers la gauche puis avance.
- **A DROITE** : tourne la voiture vers la droite puis avance.

---

## Codes IR utilisés

| Action   | Code IR (Hex) |
| -------- | ------------- |
| AVANCE   | 0xFD02BF00    |
| RECULE   | 0xFE01BF00    |
| STOP     | 0xFF00BF00    |
| A GAUCHE | 0xF10EBF00    |
| A DROITE | 0xF20DBF00    |

> ⚠️Ces codes sont spécifiques à la télécommande utilisée. Vous pouvez les modifier selon votre télécommande.

---

## Installation

1. Brancher les composants selon le schéma ci-dessus.
2. Installer la bibliothèque [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) via le gestionnaire de bibliothèques Arduino.
3. Copier le code source dans l’IDE Arduino.
4. Téléverser le programme sur l’Arduino.
5. Utiliser la télécommande pour contrôler la voiture robot.

---

## Code source

Le code complet est fourni dans le fichier `VOITURE_IR.ino`. Il inclut :

- Initialisation du récepteur IR
- Définition des pins moteurs
- Fonctions pour chaque mouvement (`avance()`, `recule()`, `stop()`, `gauche()`, `droite()`)
- Boucle principale qui lit les signaux IR et déclenche les mouvements correspondants.



````Cpp
```
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


```
````

##
