
#include <LiquidCrystal.h>
#define RS     2
#define ENABLE 3
#define D4     4
#define D5     5
#define D6     6
#define D7     7
#define BUTTON A0

enum directie { up, down, left, right, none };
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);
boolean gameover;
int scor=0;

boolean x[8][8];
struct s
{
  int row,column,dir;
  struct s *next;
};
typedef s part;
 
part *head, *tail;
int i,j;
long pc,pr;

void newPoint()
{
 
  part *p;
  p = tail;
  boolean newp = true;
  while (newp)
  {
    pr = random(8);
    pc = random(8);
    newp = false;
    while (p->next != NULL && !newp)
    {
      if (p->row == pr && p->column == pc) newp = true;
      p = p->next;
    }
  }
 
  if (scor < 13)
  {
    growSnake();
  }
}

void growSnake()
{
  part *p;
  p = (part*)malloc(sizeof(part));
  p->row = tail->row;
  p->column = tail->column;
  p->dir = tail->dir;
  p->next = tail;
  tail = p;
}
void createSnake(int n) 
{
  for (i=0;i<8;i++)
    for (j=0;j<8;j++)
      x[i][j] = false;
         
  part *p, *q;
  tail = (part*)malloc(sizeof(part));
  tail->row = 7;
  tail->column =  n/2;
  tail->dir = left;
  q = tail;
  x[tail->row][tail->column] = true;
  for (i = 0; i < n-1; i++) 
  {
    p = (part*)malloc(sizeof(part));
    p->row = q->row;
    p->column = q->column - 1;
    x[p->row][p->column] = true;
    p->dir = q->dir;
    q->next = p;
    q = p;
  }
  if (n>1)
  {
    p->next = NULL;
    head  = p;
  }
  else
  {
    tail->next = NULL;
    head = tail;
  }
}
void reset()
{
  delay(1000);
  lcd.clear();
  lcd.home();
  lcd.setCursor(0, 1);
  lcd.print("AtiObtinutScorul:");
  lcd.setCursor(7,0);
  lcd.print(scor);
  delay(4000);
  lcd.clear();
  start();
}

void start()
{
  gameover = false;
  createSnake(3);
  for(int i= 5;i> 0; i--)
  {
    lcd.setCursor(7,0);
    lcd.print(i);
    delay(1000);
  }
  lcd.clear();
}
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  start();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  reset();
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
 
