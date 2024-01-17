#define BUTTON_PIN 11

#define NUM_LEDS 9

#define RED_LED_PIN 10

#define GREEN_LED_PIN 13

#define BLUE_LED_PIN 12


int ledPins[NUM_LEDS] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

int lives = 5;

int level = 1;

int speedDelay = 100;

int score = 0;

int consecutiveHits = 0;


void setup() {

  pinMode(BUTTON_PIN, INPUT); // Botão


  for (int i = 0; i < NUM_LEDS; i++) {

    pinMode(ledPins[i], OUTPUT);

  }


  pinMode(RED_LED_PIN, OUTPUT); // LED vermelho

  pinMode(GREEN_LED_PIN, OUTPUT); // LED verde

  pinMode(BLUE_LED_PIN, OUTPUT); // LED azul


  // Inicializa os LEDS com as cores correspondentes

  digitalWrite(RED_LED_PIN, HIGH);

  digitalWrite(GREEN_LED_PIN, HIGH);

  digitalWrite(BLUE_LED_PIN, HIGH);

}


void loop() {

  int currentLed = NUM_LEDS - 1;


  while (currentLed >= 0) {

    digitalWrite(ledPins[currentLed], HIGH); // Acende o LED "currentLed"

    delay(speedDelay);


    if (currentLed == 4 && digitalRead(BUTTON_PIN) == HIGH) { // Se pausou no LED conectado ao pino 4

      delay(1000); // Debounce para evitar leituras falsas


      if (currentLed == 4 && digitalRead(BUTTON_PIN) == HIGH) { // Ainda pausado no LED conectado ao pino 4

        digitalWrite(ledPins[currentLed], LOW); // Apaga o LED "currentLed"

        currentLed--;


        score++; // Incrementa o score

        consecutiveHits++; // Incrementa o número de acertos consecutivos


        if (consecutiveHits >= 4 && lives > 0) { // Se houver 4 acertos consecutivos e vidas restantes

          level++; // Incrementa o nível

          speedDelay -= 25; // Acelera o jogo


          if (speedDelay < 20) {

            speedDelay = 20; // Define uma velocidade mínima

          }


          consecutiveHits = 0; // Reinicia o contador de acertos consecutivos

        }

      }

    } else if (digitalRead(BUTTON_PIN) == HIGH) { // Se pausou em outro LED

      delay(1000); // Debounce para evitar leituras falsas


      if (digitalRead(BUTTON_PIN) == HIGH) { // Ainda pausado em outro LED

        digitalWrite(ledPins[currentLed], LOW); // Apaga o LED "currentLed"

        currentLed--;


        lives--; // Perde uma vida


        if (lives == 0) { // Se vidas esgotadas, pisca o LED vermelho

          digitalWrite(GREEN_LED_PIN, HIGH); // LED verde desligado

          digitalWrite(BLUE_LED_PIN, HIGH); // LED azul desligado


          // Pisca o LED vermelho

          for (int i = 0; i < 3; i++) {

            digitalWrite(RED_LED_PIN, HIGH); // LED vermelho desligado

            delay(500);

            digitalWrite(RED_LED_PIN, LOW); // LED vermelho ligado

            delay(500);

          }


          // Reinicia o jogo

          level = 1;

          speedDelay = 100;

          lives = 5;

          score = 0;

          consecutiveHits = 0;

          digitalWrite(RED_LED_PIN, HIGH); // LED vermelho desligado

        }

      }

    }


    digitalWrite(ledPins[currentLed], LOW); // Apaga o LED "currentLed"

    currentLed--;


    if (currentLed < 0) {

      // Atualiza a cor dos LEDs com base no número de vidas

      if (lives <= 5 && lives > 3) {

        digitalWrite(RED_LED_PIN, LOW); // LED vermelho desligado

        digitalWrite(GREEN_LED_PIN, HIGH); // LED verde ligado

        digitalWrite(BLUE_LED_PIN, LOW); // LED azul desligado

      } else if (lives <= 3 && lives > 0) {

        digitalWrite(RED_LED_PIN, LOW); // LED vermelho desligado

        digitalWrite(GREEN_LED_PIN, LOW); // LED verde desligado

        digitalWrite(BLUE_LED_PIN, HIGH); // LED azul ligado

      } else if (lives == 0){

        digitalWrite(RED_LED_PIN, HIGH); // LED vermelho ligado

        digitalWrite(GREEN_LED_PIN, LOW); // LED verde desligado

        digitalWrite(BLUE_LED_PIN, LOW); // LED azul desligado

      }


      delay(100); // Aguarda um pequeno intervalo antes de começar o próximo ciclo

    }

  }

}