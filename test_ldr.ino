// LDR's only read 0=light or 1=NO light 
#define BL_PIN    A1
#define BR_PIN    A4
#define TL_PIN    A0
#define TR_PIN    A3

void setup() {
  Serial.begin(9600);
  pinMode(BL_PIN, INPUT);
  pinMode(BR_PIN, INPUT);
  pinMode(TL_PIN, INPUT);
  pinMode(TR_PIN, INPUT);
}

void loop() {
  int BL_val = analogRead(BL_PIN);
  int BR_val = analogRead(BR_PIN);
  int TL_val = analogRead(TL_PIN);
  int TR_val = analogRead(TR_PIN);

  Serial.println("BL\tBR\tTL\tTR\t");
  Serial.print(BL_val);
  Serial.print("\t");
  Serial.print(BR_val);
  Serial.print("\t");
  Serial.print(TL_val);
  Serial.print("\t");
  Serial.print(TL_val);
  Serial.println("\t");
  delay(100);
}
