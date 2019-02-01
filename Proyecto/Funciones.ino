void inicializarPines() {
  pinMode(Alarm,   OUTPUT);
  pinMode(Door_1,  INPUT);
  pinMode(Door_2,  INPUT);
  pinMode(Win_1,   INPUT);
  pinMode(Win_2,   INPUT);

}


//////////////  Salida de mensajes de bienvenida  /////////////////////
void Send_Initial_message() {
  mySerial.println("AT+CMGS=\"" + Number_One + "\"");
  delay(500);
  mySerial.println("BIENVENIDOS!");
  delay(100);
  mySerial.println("Iniciando Sistema de Seguridad...");
  delay(500);
  mySerial.write(0x1a); //ctrl+z
  delay(100);
  mySerial.write(0x1a); //ctrl+z
  delay(1000);
}

//////////////  Salida de mensajes de estados  /////////////////////
void Send_State_System() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENVIANDO...");
  lcd.setCursor(0, 1);
  lcd.print("SOLICITUD ESTADO");
  delay(1000);
  mySerial.println("AT+CMGS=\"" + Number_One + "\"");
  delay(500);
  mySerial.println(Comment_Room_1);
  delay(500);
  mySerial.write(0x1a); //ctrl+z
  delay(1000);
  mySerial.write(0x1a); //ctrl+z
  delay(1000);
}

//////////////  Salida de mensajes de alertas  /////////////////////
void Send_Security_Alert() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALERTA!!!");
  lcd.setCursor(0, 1);
  lcd.print("SISTEMA VIOLADO");
  delay(1000);
  mySerial.println("AT+CMGS=\"" + Number_One + "\"");
  delay(500);
  mySerial.println("ALERTA!!!\n");
  delay(500);
  mySerial.println("Violacion al Sistema de Seguridad.");
  delay(500);
  mySerial.write(0x1a); //ctrl+z
  delay(1000);
  mySerial.write(0x1a); //ctrl+z
  delay(1000);
}

//////////////  Llegada mensajes de texto  /////////////////////
void Receive_Messages() {
  incoming_char = mySerial.read();
  Serial.print(incoming_char);
  if ((Find_Chars == 0) && (incoming_char == '+')) {
    Find_Chars = 1;
    Cell_Number = "";
    keys = "";
  }
  if ((Find_Chars == 1) && (incoming_char == 'C')) {
    Find_Chars = 2;
  }
  if ((Find_Chars == 2) && (incoming_char == 'M')) {
    Find_Chars = 3;
  }
  if ((Find_Chars == 3) && (incoming_char == 'T')) {
    Find_Chars = 4;
  }
  if ((Find_Chars == 4) && (incoming_char == ':')) {
    Find_Chars = 5;
  }
    if ((Find_Chars == 5) && (incoming_char == ' ')) {
    Find_Chars = 6;
  }
  if ((Find_Chars == 6) && (incoming_char == '"')) {
    Find_Chars = 7;
    for (int i = 0; i <= 8; i++) {
      Digits = mySerial.read();
      if (Digits == '"') break;
      else Cell_Number += Digits;  // Obtengo todo el número telefónico.
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RECIBIENDO");
    lcd.setCursor(0, 1);
    lcd.print("MENSAJE...");
    delay(3000);

  }
  // la clave va seguido del caracter Numeral "\n".
  if ((Find_Chars == 7) && (incoming_char == '\n')) {
    Find_Chars = 0;
    // Todas las claves están comprendidas en un tamaño de 7 caracteres.
    Character1 = mySerial.read();
    Character2 = mySerial.read();
    Character3 = mySerial.read();
    Character4 = mySerial.read();
    Character5 = mySerial.read();
    Character6 = mySerial.read();
    Character7 = mySerial.read();
    keys += Character1;
    keys += Character2;
    keys += Character3;
    keys += Character4;
    keys += Character5;
    keys += Character6;
    keys += Character7;
  }
  
  delay(100);
}
