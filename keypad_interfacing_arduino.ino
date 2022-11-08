#define datapin 5
#define latchpin 4
#define clkpin 3
#define r1 13
#define r2 12
#define r3 11
#define r4 10
#define c1 9
#define c2 8
#define c3 7
#define c4 6
char arr[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
//debouncing
unsigned long lastdebounce=0;
unsigned long debouncedelay=5;
char state='\0';
char laststate='\0';
char presentstate='\0';
String s="11000000111110011010010010110000100110011001001010000010111110001000000010010000";
void reset_col(){
digitalWrite(c1,0);
  digitalWrite(c2,0);
  digitalWrite(c3,0);
  digitalWrite(c4,0);
}
void reset_row(){
 digitalWrite(r1,0);
  digitalWrite(r2,0);
  digitalWrite(r3,0);
  digitalWrite(r4,0);
}
int row_inp(){
  digitalWrite(c1,HIGH);
  digitalWrite(c2,HIGH);
  digitalWrite(c3,HIGH);
  digitalWrite(c4,HIGH);
  if(digitalRead(r1)==HIGH){
  reset_col();
  return 1;
  }
  else if(digitalRead(r2)==HIGH){
    reset_col();
  return 2;
  }
  else if(digitalRead(r3)==HIGH){
    reset_col();
  return 3;
  }
  else if(digitalRead(r4)==HIGH){
   reset_col();
  return 4;
  }
 reset_col();
  return -1;
 }
int col_inp(){
  digitalWrite(r1,HIGH);
  digitalWrite(r2,HIGH);
  digitalWrite(r3,HIGH);
  digitalWrite(r4,HIGH);
  if(digitalRead(c1)==HIGH){
    reset_row();
  return 1;
  }
  else if(digitalRead(c2)==HIGH){
     reset_row();
  return 2;
  }
  else if(digitalRead(c3)==HIGH){
    reset_row();
  return 3;
  }
  else if(digitalRead(c4)==HIGH){
     reset_row();
  return 4;
  }
   reset_row();
  return -1;
 }

char custom_input(){
int rin=row_inp();
int col=col_inp();
  if(rin!=-1 && col!=-1){
  return arr[rin-1][col-1];
  }
  else{
  return '\0';
  }
}
void inpPos(){
digitalWrite(datapin,1);
 
  digitalWrite(clkpin,1);
  
  digitalWrite(clkpin,0);
  
  digitalWrite(datapin,0);
}
void inpNeg(){
  digitalWrite(datapin,0);
  
  digitalWrite(clkpin,1);
 
  digitalWrite(clkpin,0);
 
  digitalWrite(datapin,1);
}
void print_i(int i){
   digitalWrite(latchpin,0);
  for(int j=0;j<8;j++){
    if(s[i*8+j]-'0'){
     inpPos();
    }
    else{
    inpNeg();
    }
  }
  digitalWrite(latchpin,1);
}
void setup(){
  pinMode(datapin,OUTPUT);
  pinMode(latchpin,OUTPUT);
  pinMode(clkpin,OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(c3, OUTPUT);
  pinMode(c4, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  presentstate=custom_input();
  if(presentstate!=laststate){
  lastdebounce=millis();
  }
  if(millis()-lastdebounce>debouncedelay){
    if(state!=presentstate){
    state=presentstate;
      if(state!='\0'){
  Serial.print(state);
  Serial.println(" is being printed");
        print_i(state-'0');
  }
    }
  }
  laststate=presentstate;
  
}
