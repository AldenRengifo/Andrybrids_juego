// Pines
const int potPin = A0;
const int buttonPin = 2;
const int ledPin = 13;

void setup() {
  Serial.begin(9600); // Iniciar comunicación serial
  
  pinMode(buttonPin, INPUT_PULLUP); // Activar resistencia interna
  pinMode(ledPin, OUTPUT);
  
  // Estado inicial del LED (Encendido = Listo para disparar)
  digitalWrite(ledPin, HIGH);
}

void loop() {
  // 1. Leer Potenciómetro (mapear de 0-1023 a 0-180 grados)
  int angle = map(analogRead(potPin), 0, 1023, 0, 90);

  // 2. Leer Botón (Con PULLUP es LOW al presionar, HIGH al soltar)
  // Invertimos la lógica para enviar un 1 si se presiona
  int isPressed = (digitalRead(buttonPin) == LOW) ? 1 : 0;

  // 3. Enviar datos a Unity en formato: "Angulo,Boton"
  // Ejemplo: "90,0" o "45,1"
  Serial.print(angle);
  Serial.print(",");
  Serial.println(isPressed);

  // 4. Recibir orden de Unity para el LED
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    if (command == '1') {
      digitalWrite(ledPin, HIGH); // Encender (Puedes disparar)
    } else if (command == '0') {
      digitalWrite(ledPin, LOW);  // Apagar (Esperando impacto)
    }
  }

  delay(20); // Pequeña pausa para no saturar el buffer serial
}