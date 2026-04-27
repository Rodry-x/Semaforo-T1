// <---- Definición de pines ---->

//Prioridad de paso peatonal A
const int BOTON_PEA_A = 2;

// Semáforo Carro A
const int SEM_CAR_A_VERDE = 3;
const int SEM_CAR_A_AMBAR = 4;
const int SEM_CAR_A_ROJO = 5;

// Semáforo Peatonal A
const int SEM_PEA_A_VERDE = 6;
const int SEM_PEA_A_ROJO = 7;

//Prioridad de paso peatonal B
const int BOTON_PEA_B = 8;

// Semáforo Carro B
const int SEM_CAR_B_VERDE = 9;
const int SEM_CAR_B_AMBAR = 10;
const int SEM_CAR_B_ROJO = 11;

// Semáforo Peatonal B
const int SEM_PEA_B_VERDE = 12;
const int SEM_PEA_B_ROJO = 13;

// Variables de control
bool botonPeaA_presionado = false;
bool botonPeaB_presionado = false;

void setup() {

  // --- Configuración de pines ---

  // Configuracion de los botones
  pinMode(BOTON_PEA_A, INPUT_PULLUP);
  pinMode(BOTON_PEA_B, INPUT_PULLUP);

  // --- Configuración de los semáforos ---

  // Semáforo Carro A
  pinMode(SEM_CAR_A_VERDE, OUTPUT);
  pinMode(SEM_CAR_A_AMBAR, OUTPUT);
  pinMode(SEM_CAR_A_ROJO, OUTPUT);

  // Semáforo Peatonal A
  pinMode(SEM_PEA_A_VERDE, OUTPUT);
  pinMode(SEM_PEA_A_ROJO, OUTPUT);

  // Semáforo Carro B
  pinMode(SEM_CAR_B_VERDE, OUTPUT);
  pinMode(SEM_CAR_B_AMBAR, OUTPUT);
  pinMode(SEM_CAR_B_ROJO, OUTPUT);

  // Semáforo Peatonal B
  pinMode(SEM_PEA_B_VERDE, OUTPUT);
  pinMode(SEM_PEA_B_ROJO, OUTPUT);

}

// Función para detectar botones durante un delay
bool esperarConDeteccionBoton(unsigned long duracion) {
  unsigned long inicio = millis();
  while (millis() - inicio < duracion) {
    if (digitalRead(BOTON_PEA_A) == LOW && !botonPeaA_presionado) {
      botonPeaA_presionado = true;
      return true; // Botón A presionado
    }
    if (digitalRead(BOTON_PEA_B) == LOW && !botonPeaB_presionado) {
      botonPeaB_presionado = true;
      return true; // Botón B presionado
    }
  }
  return false; // No se presionó ningún botón
}

// Función para ejecutar el ciclo de prioridad peatonal A
void cicloPrioridadPeatonalA() {
  // Verde fijo de 1 segundo
  digitalWrite(SEM_CAR_A_VERDE, HIGH);
  delay(1000);
  digitalWrite(SEM_CAR_A_VERDE, LOW);
  
  // 3 parpadeos verde (1.5 segundos)
  for(int i = 0; i < 3; i++) {
    digitalWrite(SEM_CAR_A_VERDE, LOW);
    delay(250);
    digitalWrite(SEM_CAR_A_VERDE, HIGH);
    delay(250);
  }
  digitalWrite(SEM_CAR_A_VERDE, LOW);
  
  // Amarillo fijo 1.5 segundos
  digitalWrite(SEM_CAR_A_AMBAR, HIGH);
  delay(1500);
  
  // 2 parpadeos amarillo (1 segundo)
  for(int i = 0; i < 2; i++) {
    digitalWrite(SEM_CAR_A_AMBAR, LOW);
    delay(250);
    digitalWrite(SEM_CAR_A_AMBAR, HIGH);
    delay(250);
  }
  digitalWrite(SEM_CAR_A_AMBAR, LOW);
  
  // Rojo fijo 5 segundos - Peatón A cruza
  digitalWrite(SEM_CAR_A_ROJO, HIGH);
  digitalWrite(SEM_PEA_A_ROJO, LOW);
  digitalWrite(SEM_PEA_A_VERDE, HIGH);
  delay(5000);
  
  // Peatón A termina
  digitalWrite(SEM_PEA_A_VERDE, LOW);
  digitalWrite(SEM_PEA_A_ROJO, HIGH);
  delay(500);
  
  // Resetear bandera
  botonPeaA_presionado = false;
}

// Función para ejecutar el ciclo de prioridad peatonal B
void cicloPrioridadPeatonalB() {
  // Verde fijo de 1 segundo
  digitalWrite(SEM_CAR_B_VERDE, HIGH);
  delay(1000);
  digitalWrite(SEM_CAR_B_VERDE, LOW);
  
  // 3 parpadeos verde (1.5 segundos)
  for(int i = 0; i < 3; i++) {
    digitalWrite(SEM_CAR_B_VERDE, LOW);
    delay(250);
    digitalWrite(SEM_CAR_B_VERDE, HIGH);
    delay(250);
  }
  digitalWrite(SEM_CAR_B_VERDE, LOW);
  
  // Amarillo fijo 1.5 segundos
  digitalWrite(SEM_CAR_B_AMBAR, HIGH);
  delay(1500);
  
  // 2 parpadeos amarillo (1 segundo)
  for(int i = 0; i < 2; i++) {
    digitalWrite(SEM_CAR_B_AMBAR, LOW);
    delay(250);
    digitalWrite(SEM_CAR_B_AMBAR, HIGH);
    delay(250);
  }
  digitalWrite(SEM_CAR_B_AMBAR, LOW);
  
  // Rojo fijo 5 segundos - Peatón B cruza
  digitalWrite(SEM_CAR_B_ROJO, HIGH);
  digitalWrite(SEM_PEA_B_ROJO, LOW);
  digitalWrite(SEM_PEA_B_VERDE, HIGH);
  delay(5000);
  
  // Peatón B termina
  digitalWrite(SEM_PEA_B_VERDE, LOW);
  digitalWrite(SEM_PEA_B_ROJO, HIGH);
  delay(500);
  
  // Resetear bandera
  botonPeaB_presionado = false;
}

void loop() {
  
  // ==================== FASE 1: CARRO A VERDE, CARRO B ROJO ====================
  // Carro A: VERDE | Carro B: ROJO | Peatón A: ROJO | Peatón B: VERDE
  
  digitalWrite(SEM_CAR_A_VERDE, HIGH);
  digitalWrite(SEM_CAR_A_AMBAR, LOW);
  digitalWrite(SEM_CAR_A_ROJO, LOW);
  
  digitalWrite(SEM_CAR_B_VERDE, LOW);
  digitalWrite(SEM_CAR_B_AMBAR, LOW);
  digitalWrite(SEM_CAR_B_ROJO, HIGH);
  
  digitalWrite(SEM_PEA_A_ROJO, HIGH);
  digitalWrite(SEM_PEA_A_VERDE, LOW);
  
  digitalWrite(SEM_PEA_B_ROJO, LOW);
  digitalWrite(SEM_PEA_B_VERDE, HIGH);

  // Esperar 4 segundos detectando botones
  if (esperarConDeteccionBoton(4000)) {
    // Si se presionó botón A durante verde A, ejecutar prioridad peatonal A
    if (botonPeaA_presionado) {
      cicloPrioridadPeatonalA();
      // Continuar con fase 2
      digitalWrite(SEM_PEA_B_VERDE, LOW);
      digitalWrite(SEM_PEA_B_ROJO, HIGH);
      digitalWrite(SEM_CAR_A_ROJO, HIGH);
      delay(500);
      // Saltar directamente a fase 2
      goto fase2;
    }
    // Si se presionó botón B durante verde A, ignorar (ya está en verde peatonal B)
    if (botonPeaB_presionado) {
      botonPeaB_presionado = false; // Ignorar porque peatón B ya puede cruzar
    }
  }

  // --- 3 Parpadeos del semáforo verde A (1.5 segundos) ---
  for(int i = 0; i < 3; i++) {
    digitalWrite(SEM_CAR_A_VERDE, LOW);
    delay(250);
    digitalWrite(SEM_CAR_A_VERDE, HIGH);
    delay(250);
  }
  digitalWrite(SEM_CAR_A_VERDE, LOW);

  // --- Semáforo A en amarillo por 1.5 segundos ---
  digitalWrite(SEM_CAR_A_AMBAR, HIGH);
  delay(1500);

  // --- 2 parpadeos del semáforo amarillo A (1 segundo) ---
  for(int i = 0; i < 2; i++) {
    digitalWrite(SEM_CAR_A_AMBAR, LOW);
    delay(250);
    digitalWrite(SEM_CAR_A_AMBAR, HIGH);
    delay(250);
  }
  digitalWrite(SEM_CAR_A_AMBAR, LOW);

  // --- Peatón B termina de cruzar antes del cambio ---
  digitalWrite(SEM_PEA_B_VERDE, LOW);
  digitalWrite(SEM_PEA_B_ROJO, HIGH);
  delay(500);

  fase2:
  // ==================== FASE 2: CARRO A ROJO, CARRO B VERDE ====================
  // Carro A: ROJO | Carro B: VERDE | Peatón A: VERDE | Peatón B: ROJO
  
  digitalWrite(SEM_CAR_A_ROJO, HIGH);
  
  digitalWrite(SEM_CAR_B_ROJO, LOW);
  digitalWrite(SEM_CAR_B_VERDE, HIGH);
  
  digitalWrite(SEM_PEA_A_ROJO, LOW);
  digitalWrite(SEM_PEA_A_VERDE, HIGH);

  // Esperar 4 segundos detectando botones
  if (esperarConDeteccionBoton(4000)) {
    // Si se presionó botón B durante verde B, ejecutar prioridad peatonal B
    if (botonPeaB_presionado) {
      cicloPrioridadPeatonalB();
      // Continuar con fin de ciclo
      digitalWrite(SEM_PEA_A_VERDE, LOW);
      digitalWrite(SEM_PEA_A_ROJO, HIGH);
      digitalWrite(SEM_CAR_B_ROJO, HIGH);
      delay(500);
      return; // Reiniciar loop
    }
    // Si se presionó botón A durante verde B, ignorar (ya está en verde peatonal A)
    if (botonPeaA_presionado) {
      botonPeaA_presionado = false; // Ignorar porque peatón A ya puede cruzar
    }
  }

  // --- 3 Parpadeos del semáforo verde B (1.5 segundos) ---
  for(int i = 0; i < 3; i++) {
    digitalWrite(SEM_CAR_B_VERDE, LOW);
    delay(250);
    digitalWrite(SEM_CAR_B_VERDE, HIGH);
    delay(250);
  }
  digitalWrite(SEM_CAR_B_VERDE, LOW);

  // --- Semáforo B en amarillo por 1.5 segundos ---
  digitalWrite(SEM_CAR_B_AMBAR, HIGH);
  delay(1500);

  // --- 2 parpadeos del semáforo amarillo B (1 segundo) ---
  for(int i = 0; i < 2; i++) {
    digitalWrite(SEM_CAR_B_AMBAR, LOW);
    delay(250);
    digitalWrite(SEM_CAR_B_AMBAR, HIGH);
    delay(250);
  }
  digitalWrite(SEM_CAR_B_AMBAR, LOW);

  // --- Peatón A termina de cruzar antes del cambio ---
  digitalWrite(SEM_PEA_A_VERDE, LOW);
  digitalWrite(SEM_PEA_A_ROJO, HIGH);
  delay(500);

  // Carro B pasa a rojo para reiniciar el ciclo
  digitalWrite(SEM_CAR_B_ROJO, HIGH);
}