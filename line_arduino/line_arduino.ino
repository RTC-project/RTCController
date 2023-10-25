#define BUF_SIZE 10
#define MEAN_POWER 250

int n_buf = 0;
byte rx_buf[BUF_SIZE];

union ArrayToInteger {
  byte array[2];
  int integer;
}ati;

int m1 = 0, m2 = 0, m3 = 0, m4 = 0;

void setup() {
  Serial.begin(57600);
  Serial3.begin(57600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  for(int i = 0; i < BUF_SIZE; i++){
    rx_buf[i] = 0;
  }
}

void loop() {
  if (Serial3.available()){
    byte b = Serial3.read();
    if (b != 10){
      rx_buf[n_buf] = b;
      n_buf++;
    }
    else if (n_buf == 8){
      ati.array[0] = rx_buf[0];
      ati.array[1] = rx_buf[1];
      m1 = ati.integer;
      ati.array[0] = rx_buf[2];
      ati.array[1] = rx_buf[3];
      m2 = ati.integer;
      ati.array[0] = rx_buf[4];
      ati.array[1] = rx_buf[5];
      m3 = ati.integer;
      ati.array[0] = rx_buf[6];
      ati.array[1] = rx_buf[7];
      m4 = ati.integer;
      for(int i = 0; i < BUF_SIZE; i++){
        rx_buf[i] = 0;
      }
      n_buf = 0;

      m1 -= MEAN_POWER;
      m2 -= MEAN_POWER;
      m3 -= MEAN_POWER;
      m4 -= MEAN_POWER;
      int dm1 = m1 < 0 ? 0 : 1;
      int dm2 = m2 < 0 ? 1 : 0;
      int dm3 = m3 < 0 ? 1 : 0;
      int dm4 = m4 < 0 ? 0 : 1;
      analogWrite(6, abs(m1));
      analogWrite(7, abs(m2));
      analogWrite(8, abs(m3));
      analogWrite(9, abs(m4));
      digitalWrite(10, dm1);
      digitalWrite(11, dm2);
      digitalWrite(12, dm3);
      digitalWrite(13, dm4);
      //Serial.print(m1);
      //Serial.print(" ");
      //Serial.print(m2);
      //Serial.print(" ");
      //Serial.print(m3);
      //Serial.print(" ");
      //Serial.println(m4);
    }
    else if (n_buf < 8){
      rx_buf[n_buf] = b;
      n_buf++;
    }
    else{
      for(int i = 0; i < BUF_SIZE; i++){
        rx_buf[i] = 0;
      }
      n_buf = 0;
    }
  }
}