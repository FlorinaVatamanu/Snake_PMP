#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
enum ButtonType { up, down, left, right, none};

boolean gameOver;
boolean mat[16][80]; //matricea jocului va avea dimensiunea de 16 linii : 2 randuri a cate 8 octeti si 80 coloane : 16 coloane a cate 5 octeti
byte character[8];//caracter de afisat
boolean black; //marcheaza faptul ca un pixel din matrice este setat
int btn;
int butLeft =11;//buton care directioneaza sarpele spre stanga
int butRight =10;
int butUp =9;
int butDown =8;
int buttonStateL = 0; //citesc starea butonului buton care directioneaza sarpele spre stanga
int buttonStateR = 0;
int buttonStateU = 0;
int buttonStateD = 0;

struct pct  //structura in care retin randul,coloana,directia sarpelui,pointer la urmatorul element din struct
{
  int row,column,dir;
  struct pct *next;
};
typedef pct point;

int i,j,scor = 0 ;
long col,line; 
point *head, *tail;//capul si coada sarpelui 


void punct()//se creeaza un nou pixel,cel pe care va trebui sa-l manance sarpele,la linia si coloana stabilita de functia random
{
 
  point *p;
  p = tail;
  boolean newPoint = true;
  while (newPoint)
  {
    newPoint = false;
    line = random(16);
    col = random(80);
    
    while (p->next != NULL && !newPoint) //pixelul ramane setat pana cand este mancat de sarpe,apoi apare altul nou
    {
      if (p->row == line && p->column == col) newPoint = true;
      p = p->next;
    }
  }
}

void drawMatrix() //afiseaza jocul pe LCD
{
  int count=0;
  if (!gameOver)
  {
  mat[line][col] = true;//daca pe o anumita linie si coloana din matrice este setat un pixel 

  for(int r=0;r<2;r++)
  {
    for(int c=0;c<16;c++)
    {
      black = false;
      for(int i=0;i<8;i++)
      {
        byte b=B00000;
//se formeaza caracterul de afisat 
//aici se defineste care punct din cei 8 x 5 pixeli care trebuie luminat
//echivalentul binar al fiecarui rand si coloane
        if (mat[r*8+i][c*5+0]!=0) {b+=B10000; black = true;}//cu booleanul black retin ca am de afisat un caracter pe LCD
        if (mat[r*8+i][c*5+1]!=0) {b+=B01000; black = true;}
        if (mat[r*8+i][c*5+2]!=0) {b+=B00100; black = true;}
        if (mat[r*8+i][c*5+3]!=0) {b+=B00010; black = true;}
        if (mat[r*8+i][c*5+4]!=0) {b+=B00001; black = true;}
        character[i] = b; 
      }   
      if (black==true)
      {
        lcd.createChar(count, character);//creeez caracterul character la adresa count si il afisez
        lcd.setCursor(c,r);//setez cursorul la coloana si randul la care trebuie afisat caracterul
        lcd.write(byte(count));//scriu caracterul pe LCD , fac cast la byte
        count++;
      }      
      else
      {
        lcd.setCursor(c,r);
        lcd.print(' '); //altfel nu se afiseaza nimic
      }
    }
  }
  }
}
 void like() { //afiseaza un caracter special in finalul jocului daca se castiga
   //in cazul de fata am setat ca scorul de castig sa fie 3 (in momentul in care sarpele aduna 3 puncte,se castiga jocul)
 byte l1[8] = {B00100,B00011,B00100,B00011,B00100,B00011,B00010,B00001};
 byte l2[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00011};
 byte l3[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00001,B11110};
 byte l4[8] = {B00000,B01100,B10010,B10010,B10001,B01000,B11110,B00000};
 byte l5[8] = {B00010,B00010,B00010,B00010,B00010,B01110,B10000,B00000};
 byte l6[8] = {B00000,B00000,B00000,B00000,B00000,B10000,B01000,B00110};
 lcd.createChar(0, l1); //creez caracterele l1...l6
 lcd.createChar(1, l2);
 lcd.createChar(2, l3);
 lcd.createChar(3, l4);
 lcd.createChar(4, l5);
 lcd.createChar(5, l6);
 lcd.setCursor(4,1); //setez cursorul la coloana 4 ,linia 1
 lcd.write(byte(0)); //afisez caracterul pe LCD, fac cast la byte(returneaza nr de bytes scrisi)
 lcd.setCursor(4,0);
 lcd.write(byte(1));
 lcd.setCursor(5,1);
 lcd.write(byte(2));
 lcd.setCursor(5,0);
 lcd.write(byte(3));
 lcd.setCursor(6,1);
 lcd.write(byte(4));
 lcd.setCursor(6,0);
 lcd.write(byte(5));
}

void game_Over() {//afiseaza un caracter special in finalul jocului daca se pierde
 //se pierde -atunci cand sarpele isi mananca coada (tail=head).
 byte w1[8] = {B00001,B00010,B00011,B00100,B00011,B00100,B00011,B00100};
 byte w2[8] = {B00011,B00000,B00000,B00000,B00000,B00000,B00000,B00000};
 byte w3[8] = {B11110,B00001,B00000,B00000,B00000,B00000,B00000,B00000};
 byte w4[8] = {B00000,B11110,B01000,B10001,B10010,B10010,B01100,B00000};
 byte w5[8] = {B00000,B10000,B01110,B00010,B00010,B00010,B00010,B00010};
 byte w6[8] = {B00110,B01000,B10000,B00000,B00000,B00000,B00000,B00000};
 lcd.createChar(0, w1);
 lcd.createChar(1, w2);
 lcd.createChar(2, w3);
 lcd.createChar(3, w4);
 lcd.createChar(4, w5);
 lcd.createChar(5, w6);
 lcd.setCursor(4,0);
 lcd.write(byte(0));
 lcd.setCursor(4,1);
 lcd.write(byte(1));
 lcd.setCursor(5,0);
 lcd.write(byte(2));
 lcd.setCursor(5,1);
 lcd.write(byte(3));
 lcd.setCursor(6,0);
 lcd.write(byte(4));
 lcd.setCursor(6,1);
 lcd.write(byte(5));
}

void free() //eliberez memoria alocata 
{
  point *p,*q; //pointer către blocul de memorie valid,alocat
  p = tail;
  while (p!=NULL)
  {//dezaloca zona de memorie
    q = p;
    p = p->next;
    free(q); 
  }
  head = tail = NULL;
}
 
void growSnake()//creste dimensiunea sarpelui,
{
  point *p;
  p = (point*)malloc(sizeof(point));//aloca memorie pentru fiecare nou punct din care e format sarpele
  p->row = tail->row;
  p->column = tail->column;
  p->dir = tail->dir;
  p->next = tail;
  tail = p;//initializeaza tail-ul cu coordonatele noului punct : rand,coloana,directie 
}
 
void moveHead()//gestioneaza miscarea sarpelui dupa o directie
{
  if(head->dir == up) head->row--;//directia este UP , atunci randul va scadea , pentru ca sarpele se va deplasa in sus in matricea LCD-ului
  else if (head->dir == down) head->row++;
  else if (head->dir == left) head->column--;
  else if (head->dir == right) head->column++;//daca directia este la dreapta , coloana pe care se afla sarpele va creste
    
  if (head->column >= 80) head->column = 0;//daca sarpele ajunge cu head-ul la coloana maxima a LCD-ului , adica >=80, se va initializa coloana head-ului cu 0
  if (head->column < 0) head->column = 79;
  if (head->row >= 16) head->row = 0;//daca  sarpele ajunge cu head-ul la linia >=16, iarasi se va initializa linia head-ului cu 0.
  if (head->row < 0) head->row = 15;
 
  point *p;
  p = tail;
  while (p != head && !gameOver ) //cat timp continua jocul, adica gameOver==false si tail!=head 
  {
    if (p->row == head->row && p->column == head->column) gameOver = true;//daca sarpele ajunge sa isi atinga tail-ul, se seteaza gameOver la true, ceea ce inseamna ca s-a pierdut jocul
    p = p->next;
    if(scor==3) //am stabilit ca atunci cand jucatorul atinge scorul de 3 puncte, acesta sa castige jocul
    {
      //se va afisa un mesaj si un caracter special,dat de functia like()
      //se va afisa scorul 
    lcd.clear();
    lcd.home();
    lcd.setCursor(2,0);
    lcd.print("Felicitari!");
    lcd.setCursor(2,1);
    lcd.print("Scor: ");
    lcd.setCursor(7,1);
    lcd.print(scor);
    delay(1000);
    lcd.clear();
    lcd.home();
    like();
    delay(2000);
    }    
  }
  //daca sarpele colecteaza un nou pixel(head -ul se afla pe linia si coloana pe care se afla pixelul respectiv), scorul creste si se creeaza un nou punct
  mat[head->row][head->column] = true;
  if (head->row == line && head->column == col) 
  {
    scor++;
    punct();
  }
}
 
void move()//sarpele se deplaseaza 
{
  point *p;
  p = tail;
  mat[p->row][p->column] = false;
  //initializez randul,coloana si directia sarpelui
  while (p->next != NULL)
  {
    p->row = p->next->row;
    p->column = p->next->column;
    p->dir = p->next->dir;
    p = p->next;
  }
  moveHead();//apelez care gestioneaza miscarea sarpelui dupa o directie
}
 
void createSnake(int n) // n = dimensiunea initiala a sarpelui
{
  for (i=0;i<16;i++)
    for (j=0;j<80;j++)
      mat[i][j] = false; //toata matricea jocului este initial libera
         
  point *p, *q;
  tail = (point*)malloc(sizeof(point));//aloc dinamic memorie pentru sizeof(point) octeti
  //se initializeaza coordonatele cozii sarpelui 
  //acesta va aparea initial pe randul 0 ,coloana 60
  //daca setez coloana la 0,se va pierde jocul, va aparea mesajul de final, pentru ca head=tail
  tail->row = 0; 
  tail->column =60;
  tail->dir = left;
  q = tail;
  mat[tail->row][tail->column] = true;//setez pe true punctul pe care se afla coada in matrice 
  //pentru fiecare punct din care este format sarpele aloc memorie
  for (i = 0; i < n-1; i++) 
  {
    p = (point*)malloc(sizeof(point));
    p->row = q->row;
    p->column = q->column - 1;
    mat[p->row][p->column] = true;
    p->dir = q->dir;
    q->next = p;
    q = p;
  }
  //daca dimensiunea acestuia e mai mare decat 1, se initializeaza head-ul ca primul pixel 
  if (n>1)
  {
    p->next = NULL;
    head  = p;
  }
  else //daca sarpele are dimensiunea 1-> head = tail
  {
    tail->next = NULL;
    head = tail;
  }
}
 
void start() //inceputul jocului 
{
  gameOver = false;
  free();//elibereaza memoria alocata
  createSnake(6);//se creeaza un sarpe de dimensiune initiala 6
  //apar mesajele de inceput si un caracter special smiley
  byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
  //numaratoare inversa de la 5
  for(int i = 5; i >0; i--){
    lcd.setCursor(7,0);
    lcd.print(i);
    delay(700);
  }
  if(gameOver != true){
  lcd.setCursor(2,0);
  lcd.print("Start Joc!");
  lcd.setCursor(2,1);
  lcd.print("Succes!");
  lcd.createChar(0, smiley);  
  lcd.setCursor(10,1);
  lcd.write(byte(0));
  delay(2000);
  lcd.clear();
  }
}


int getButtonPress(int butLeft ,int butRight,int butUp ,int butDown )//verific care buton este apasat
{
 buttonStateL = digitalRead(butLeft); //citesc starea butoanelor(input)
 buttonStateR = digitalRead(butRight);
 buttonStateU = digitalRead(butUp);
 buttonStateD = digitalRead(butDown);
 ButtonType btn = none;
 
 //daca sunt apasate butoanele ,directia se schimba
   if( buttonStateU == HIGH){
   btn = up;
   
  }
  else if( buttonStateD == HIGH){
   btn = down;
  
  }
  else if( buttonStateR == HIGH){
   btn = right;
    
  }
  else if( buttonStateL == HIGH){
   btn = left;
  }
  return btn;//returneaza directia in care va merge sarpele
}

void setup()//initializeaza pinii la care sunt legati butoanele ca pini de intrare
{
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  lcd.begin(16, 2);
  start();
}


void loop()
{

  btn = getButtonPress(butLeft ,butRight,butUp , butDown);
  if( btn != none )//verific care buton este apasat
  {
    switch(btn){
      case up: if(head->dir != down  ) {//daca capul sarpelui nu este in jos,acesta isi modifica directia in sus
        head ->dir = up; 
        break;}
      case down: if(head->dir != up ){
        head ->dir = down;
        break;}
      case right: if(head->dir != left ){//daca capul sarpelui nu este in stanga,acesta isi modifica directia in dreapta
        head ->dir = right;
        break;}
      case left: if(head->dir != right){
        head ->dir = left; 
        break;}
      default: 
        break;
    }
   
  }
  move();//sarpele se deplaseaza in continuare
  drawMatrix();//afiseaza jocul
  
  if(gameOver){ //daca s-a pierdut jocul,se afiseaza scorul,caracterul special si mesajul date de functia  game_Over()
    
    lcd.begin(16,2);
    delay(1000);
    lcd.clear();
    lcd.home();
    lcd.setCursor(2,0);
    lcd.print("GameOver");
    delay(700);
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Scor: ");
    lcd.setCursor(8,1);
    lcd.print(scor);
    delay(2000);
    lcd.begin(16,2);
    lcd.clear();
    game_Over();
    delay(1000);
    
  }
  
     
}

 
 
