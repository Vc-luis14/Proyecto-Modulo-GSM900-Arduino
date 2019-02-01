void setup() {
  //  Serial.begin(9600);

  mySerial.begin(9600);
  inicializarPines();

  lcd.begin();
  lcd.setCursor(3, 0);
  lcd.print("BIENVENIDO");
  lcd.setCursor(0, 1);
  lcd.print("INICIANDO MODULO");

  delay(500);
  mySerial.println("AT+CMGF=1"); // configura SMS en modo de texto.

  delay(500);
  Send_Initial_message();

  mySerial.println("AT+CMGD=1,4"); // eliminar todos los mensajes
  delay(500);

  Comment_Room_1 = "Habitacion 1 Desactivado.";
  Send_State_System();
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("SECURITY SYSTEM");
  if (Cell_Number != "") { //imprimo el número telefónico en la LCD.
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("N");
    lcd.write(byte(0));
    lcd.print(":");
    lcd.print(Cell_Number);
  }


  while (mySerial.available() > 0) {
    Receive_Messages();
  }

  if (keys == "Act ha1") {     // activa cuarto 1
    keys = "";
    State_Room_1 = true;
    Comment_Room_1 = "Habitacion 1 Activado.";
  }
  else if (keys == "Des ha1") { // desactiva cuarto 1
    keys = "";
    State_Room_1 = false;
    Comment_Room_1 = "Habitacion 1 Desactivado.";
  }
  else if (keys == "Des ala") { // desactiva alarma
    keys = "";
    digitalWrite(Alarm, LOW);
  }
  else if (keys == "Estados") { // Petición "Estados"
    keys = "";
    Send_State_System();
  }
  else;

    if (State_Room_1 == true) {
    // Sistema de seguridad de puertas y ventanas activadas.
    State_Door_1  = analogRead(Door_1);
    State_Door_2  = analogRead(Door_2);
    State_Win_1   = analogRead(Win_1);
    State_Win_2   = analogRead(Win_2);
    if ((State_Door_1 >= 1010) || (State_Door_2 >= 1010) ||
        (State_Win_1 >= 1010 ) || (State_Win_2 >= 1010)) {
      Count_Room_1 ++;
      digitalWrite(Alarm, HIGH);
      if (Count_Room_1 == 1) {
        Send_Security_Alert();
      }
    }
    else Count_Room_1 = 0;
    // Alarma de luces.
  }

  delay(500);
}
