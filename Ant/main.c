#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <antlibery.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#define TRUE 1
#define FALS 0

#define hCon GetStdHandle(STD_OUTPUT_HANDLE)

typedef struct {
    COORD new_Position;
    int x;
    int y;
    unsigned count;
}NextAnt;

struct ListCordinats{
    unsigned count;
    unsigned X_position;
    unsigned Y_position;
    struct ListCordinats *next,*prev;
};

typedef struct ListCordinats *PNode;

typedef struct {
    PNode Head;
    PNode Tail;
}Stack;

void PUSH(unsigned count,unsigned X, unsigned Y, Stack *p){
    PNode NewNode;
    NewNode = (PNode)malloc(sizeof(struct ListCordinats));
    NewNode->count=count;
    NewNode->X_position = X;
    NewNode->Y_position = Y;
    NewNode->next = p->Head;
    NewNode->prev = NULL;
    if(p->Head)
       p->Head->prev = NewNode;
    p->Head = NewNode;
    if(!p->Tail) p->Tail = p->Head;

}

int Serch_in_Stack(NextAnt *x,Stack *p, PNode Tail, int count){
   PNode Tamp;
   Tamp = Tail;
   if(count!=1){
   while(Tamp!=NULL){
       if((x->x==Tamp->X_position)&&(x->y==Tamp->Y_position)&&Tamp->count==count-1){
           return TRUE;
       }
       else if ((x->x==Tamp->X_position)&&(x->y==Tamp->Y_position)){
           PUSH(count,x->x,x->y,p);
           move_ant_for_Stack(x,Tail,Tamp);
           return 0;
       }
       Tamp=Tamp->prev;
   }
   }
   return FALS;
}

int Serch_in_function_move_ant(NextAnt*x, PNode Tail, PNode Tamp){
   PNode BoofTemp;
   BoofTemp = Tail;
   while(BoofTemp!=NULL){
       if((x->x==BoofTemp->X_position)&&(x->y==BoofTemp->Y_position)){
           Tamp=BoofTemp;
           break;
       }
       BoofTemp=BoofTemp->prev;

   }
}

void move_ant_for_Stack(NextAnt*x, PNode Tail, PNode Tamp){
    while(!(MAP[x->y][x->x]==3)){
         x->x=x->new_Position.X = Tamp->X_position;
         x->y=x->new_Position.Y = Tamp->Y_position;
         Tamp=Serch_in_function_move_ant(x,Tail,Tamp);
         draw_ant(x);
         Sleep(30);
         Tamp=Tamp->prev;
         if(Tamp==NULL){
             Tamp=Tail;
         }
         clear_ant(x);
       }
     }


void POP_element(Stack *p){
    p->Head= p->Head->next;
}

void Printlist(Stack *p){
    PNode Tail = p->Tail;
    printf("\n");
    while(Tail->prev!=NULL){
        printf("cordinat %i = [%i][%i], ", Tail->count, Tail->X_position, Tail->Y_position);
        Tail = Tail->prev;
    }
}

void display(){
    system("mode con cols=540 lines=500");
}


void func_labyrinth (const int map[41][41]){
    int x,y;
    for(x=0;x<41;x++){
        for(y=0;y<41;y++){
          switch (map[x][y]){
          case 0:
            printf("%c", 32);
            break;
          case 1:
            printf("%c", 178);
            break;
          case 3:
            printf("%c", 32);
            break;
        }
       }
        printf("\n");
    }
}
void Randfunction(NextAnt *p, const int map[41][41]){
    int x,y;
    time_t t;
    unsigned s = 2;
    srand((unsigned) time(&t));
    while(s!=0){
      p->x = rand()%41;
      p->y = rand()%41;
      x = p->x;
      y = p->y;
      s = map[y][x];
    }
}

void move_Ant_LEFT(int count,NextAnt *x,Stack *p){
    int TRUE_or_FALSE = 0;
    while(!(MAP[x->y][x->x]==3)){
        clear_ant(x);
        x->new_Position.X -= 1;
        x->x-=1;
        TRUE_or_FALSE = Serch_in_Stack(x,p,p->Tail,count);
        if(TRUE_or_FALSE==TRUE){
            POP_element(p);
            count--;
        }
        else if(TRUE_or_FALSE==FALSE){
            count++;
            PUSH(count,x->x, x->y,p);
        }
        draw_ant(x);
        Sleep(30);
        if(MAP[x->y+1][x->x]==0){
           move_Ant_DOWN(count,x,p);
        }
        else if(MAP[x->y][x->x-1]==1&&MAP[x->y-1][x->x]==0){
           move_Ant_UP(count,x,p);
        }
        else if(MAP[x->y][x->x-1]==1){
            move_Ant_RIGHT(count,x,p);
         }
    }

}
void move_Ant_RIGHT(int count,NextAnt *x,Stack *p){
    int TRUE_or_FALSE = 0;
     while(!(MAP[x->y][x->x]==3)){
        clear_ant(x);
        x->new_Position.X += 1;
        x->x+=1;
        TRUE_or_FALSE = Serch_in_Stack(x,p,p->Tail,count);
        if(TRUE_or_FALSE==TRUE){
           POP_element(p);
           count--;
         }
        else if(TRUE_or_FALSE==FALSE){
           count++;
           PUSH(count,x->x, x->y,p);
         }
        draw_ant(x);
        Sleep(30);
        if(MAP[x->y-1][x->x]==0){
           move_Ant_UP(count,x,p);
         }
        else if(MAP[x->y][x->x+1]==1&&MAP[x->y+1][x->x]==0){
           move_Ant_DOWN(count,x,p);
           }
        else if(MAP[x->y][x->x+1]==1){
            move_Ant_LEFT(count,x,p);
           }

       }
}
void move_Ant_UP(int count,NextAnt *x,Stack *p){
    int TRUE_or_FALSE = 0;
    while(!(MAP[x->y][x->x]==3)){
        clear_ant(x);
        x->new_Position.Y-= 1;
        x->y-=1;
        TRUE_or_FALSE = Serch_in_Stack(x,p,p->Tail,count);
        if(TRUE_or_FALSE==TRUE){
            POP_element(p);
            count--;
        }
        else if(TRUE_or_FALSE==FALSE){
            count++;
            PUSH(count,x->x,x->y,p);
        }
        draw_ant(x);
        Sleep(30);
        if(MAP[x->y][x->x-1]==0){
           move_Ant_LEFT(count,x,p);
        }
        else if(MAP[x->y-1][x->x]==1&&MAP[x->y][x->x+1]==0){
           move_Ant_RIGHT(count,x,p);
        }
        else if(MAP[x->y-1][x->x]==1){
           move_Ant_DOWN(count,x,p);
        }
    }

}
void move_Ant_DOWN(int count,NextAnt *x,Stack *p){
    int TRUE_or_FALSE = 0;
    while(!(MAP[x->y][x->x]==3)){
        clear_ant(x);
        x->new_Position.Y+= 1;
        x->y+=1;
        TRUE_or_FALSE = Serch_in_Stack(x,p,p->Tail,count);
        if(TRUE_or_FALSE==TRUE){
            POP_element(p);
            count--;
        }
        else if(TRUE_or_FALSE==FALSE){
            count++;
            PUSH(count,x->x, x->y,p);
        }
        draw_ant(x);
        Sleep(30);
        if(MAP[x->y][x->x+1]==0){
            move_Ant_RIGHT(count,x,p);
        }
        else if(MAP[x->y+1][x->x]==1&&MAP[x->y][x->x-1]==0){
            move_Ant_LEFT(count,x,p);
        }
        else if(MAP[x->y+1][x->x]==1){
             move_Ant_UP(count,x,p);
        }
    }

}

void draw_ant(NextAnt *nextAnt){
    SetConsoleCursorPosition(hCon,nextAnt->new_Position);
    printf("%c", 15);
}
void clear_ant(NextAnt *nextAnt){
    SetConsoleCursorPosition(hCon,nextAnt->new_Position);
    printf("%c", 0);
}
int main()
{
  display();
  NextAnt nextAnt;
  Stack stack;
  stack.Head = NULL;
  stack.Tail = NULL;
  unsigned count = 0;
  func_labyrinth(MAP);
  while (1){
    clear_ant(&nextAnt);
    Randfunction(&nextAnt, MAP);
    nextAnt.new_Position.X = nextAnt.x;
    nextAnt.new_Position.Y = nextAnt.y;
    if(MAP[nextAnt.y-1][nextAnt.x]==0){
        move_Ant_UP(count,&nextAnt,&stack);
    }
    else if(MAP[nextAnt.y][nextAnt.x+1]==0){
        move_Ant_RIGHT(count,&nextAnt,&stack);
    }
    else if(MAP[nextAnt.y+1][nextAnt.x]==0){
        move_Ant_DOWN(count,&nextAnt,&stack);
    }
    else if(MAP[nextAnt.y][nextAnt.x-1]==0){
        move_Ant_LEFT(count,&nextAnt,&stack);
    }
}
  return 0;
}
