int SW=3;
int xpin=A0;
int ypin=A1;
int rf=6;
int rb=3;
int lf=9;
int lb=11;
int ledR, ledL, X;
void setup() {
    Serial.begin(9600);
    pinMode(SW, OUTPUT);
    digitalWrite(SW, HIGH);
    pinMode(xpin, INPUT);
    pinMode(ypin, INPUT);
    pinMode(rf, OUTPUT);
    pinMode(rb, OUTPUT);
    pinMode(lf, OUTPUT);
    pinMode(lb, OUTPUT);
}

void loop() 
{
        int x=analogRead(xpin);
        int y=analogRead(ypin);
        y=constrain(y,0,1023);
        x=constrain(x,0,1023);
        if(y>522)
        {
          ledR = map(y, 522, 1023, 0, 255);
          ledL = map(y, 522, 1023, 0, 255);
        }
        else if(y<502)
        {
          ledR = map(y, 502, 0, 0, -255);
          ledL = map(y, 502, 0, 0, -255);
        }
        else
        {
          ledR = 0;
          ledL = 0;
        }
        if(x>522)
        {
          X= map(x, 522, 1023, 0, 255);
          ledR = ledR - X;
          ledL = ledL + X;
          if (ledL > 255) 
          {
            ledL = 255;
          }
          if (ledR < -255) 
          {
            ledR = -255;
          }
        }
        else if(x<502)
        {
          X= map(x, 502, 0, 0, 255);
          ledR = ledR + X;
          ledL = ledL - X;
          if (ledR > 255) 
          {
            ledR = 255;
          }
          if (ledL < -255) 
          {
            ledL = -255;
          }
        }
        Serial.print(ledL);
        Serial.print('\t');
        Serial.println(ledR);
        if(ledL<0)
        {
          ledL=-ledL;
          analogWrite(lb,ledL);
          digitalWrite(lf, LOW);
        }
        else
        {
          analogWrite(lf,ledL);
          digitalWrite(lb, LOW);
        }
        if(ledR<0)
        {
          ledR=-ledR;
          analogWrite(rb,ledR);
          digitalWrite(rf, LOW);
        }
        else
        {
          analogWrite(rf,ledR);
          digitalWrite(rb, LOW);
        }
    }
