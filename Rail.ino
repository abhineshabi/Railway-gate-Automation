int sensor1=2;
int sensor2=3;
int motor1=4;
int motor2=5;

void setup(){
pinMode(sensor1,INPUT);
pinMode(sensor2,INPUT);
pinMode(motor1,OUTPUT);
pinMode(motor2,OUTPUT);
}

void loop(){
C:
if(sensor1==LOW){
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
delay(500);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,HIGH);
A:
if(sensor2==LOW){
digitalWrite(motor1,LOW);
digitalWrite(motor2,HIGH);
delay(500);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,HIGH); 
delay(1000);
goto C;
}goto A;
if(sensor2==LOW){
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
delay(500);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,HIGH);
B:
if(sensor1==LOW){
digitalWrite(motor1,LOW);
digitalWrite(motor2,HIGH);
delay(500);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,HIGH); 
delay(1000);
goto C; 
}
goto B;
}
}
}
