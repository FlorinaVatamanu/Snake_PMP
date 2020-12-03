
int snakeLinie, snakeCol;
int foodLinie, foodCol;
int scor = 0;
int dimSnake = 1;
const int latimeMatrice = 8;
const int inaltimeMatrice = 8;
int directie=0;//sarpele nu se misca initial
int coadaLinie[100], coadaCol[100];
bool pierdut = false;
bool castigat = false;
//pentru a manevra directia sarpelui
const short up     = 1;
const short right  = 2;
const short down   = 3;
const short left   = 4;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  genereazaMancarea();//creeaza un nou punct alimentar in cazul in care nu exista
  miscareJoystick(); //directioneaza snake-ul
  parametri(); //calculeaza daca se incadreaza sarpele in 8x8 Matrix Display
  stariJoc();

}



void mananca() {
  if (snakeCol == foodCol && snakeLinie == foodLinie) {
    scor+=1;
    dimSnake++;
    FoodPosition();
  }
}

void genereazaMancarea(){
  foodLinie=random(8);
  foodCol=random(8);
}
void parametri(){
  switch(directie)
  {
    case up:snakeLinie--;
    case right:snakeCol++;
    case down:snakeLinie++;
    case left:snakeCol--;
    default: return;
    
}}
void SnakeInafaraMatricii() {
  if (snakeCol >= latimeMatrice) {
    snakeCol = 0;
  } else if (snakeCol < 0) {
    snakeCol = latimeMatrice - 1;
  }
  if (snakeLinie >= inaltimeMatrice) {
    snakeLinie = 0;
  } else if (snakeLinie < 0) {
    snakeLinie = inaltimeMatrice - 1;
  }
}
}
