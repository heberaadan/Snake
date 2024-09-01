#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define V 21
#define H 65
#define N 100

struct snk {
 int x,y;
 int modx,mody;
 char imagen;
}; //representar las partes de la serpiente

struct frt{
 int x,y;
};

struct snk snake [N]; //longitud serpiente
struct frt fruta;

void inicio (int *tam,char campo[V][H]);
void intro_campo (char campo [V][H]);
void intro_datos(char campo [V][H],int tam);
void draw (char campo[V][H],int tam);
int loop (char campo [V][H], int tam);
void input(char campo[V][H],int *tam,int *muerto);
void update(char campo [V][H],int tam);
void intro_datos2(char campo [V][H],int tam);
void pantalla ();
void serpiente ();

int main(){

 int tam,op,r;
 char campo[V][H];
 //imprime el nombre de juego y logo
 system("cls");
 pantalla();
 serpiente ();
 printf("\n\t\t\t\t   ");
 printf("\033[1;32m");
 system("PAUSE");
 printf("\033[0m");
juego:{
 op=0;
 //inicializa las variables
 inicio(&tam,campo);
 //corre el juego
 r=loop(campo,tam);
  }
  retorno:{

  system("cls");
  printf("\033[1;32m");
  printf("\n\n\n\n\t\tSu puntacion fue de: ");
  printf("\033[1;33m");
  printf("%i\n\n\n\n\n\n",r-4);
  printf("\033[0m");
  printf("\033[1;37m");
  printf("\n\n\tQuieres volver a jugar");
  printf("\033[1;32m");
  printf("\n\n\t(1)Si\t");
  printf("\033[1;33m");
  printf("(2)No\n\n\t");

   op = getch();

 if (op=='1')
    {
        goto juego;
    }else if(op=='2')
        {
            system("CLS");
            printf("\033[1;32m");
            printf("\n\n\n\n\n\n\t\t\t\t\tGRACIAS POR JUGAR!!!\n\n\n\n\n\n\n\n");
            printf("\033[0m");
        }else
            {
                printf("\033[0;31m");
                printf("\n\n\tOPCION NO VALIDA\n\n\t");
                printf("\033[1;37m");
                printf("vuelva a intentar\n\n\n");
                system("PAUSE");
                system ("CLS");
                goto retorno;
            }
  }
}

void inicio (int *tam,char campo[V][H]){
    int i;
    //coordenadas de la cabeza
  snake[0].x=32;
  snake[0].y=10;

  //tamaño inicial
  *tam=4;

  srand(time(NULL));

  //coordenadas fruta
  fruta.x = rand()% (H-2);
  fruta.y = rand()% (V-2);

  //para evitar que la fruta se genere sobre el marco del juego
  while (fruta.x == 0){
    fruta.x = rand()% (H-2);
  }

  while (fruta.y==0){
    fruta.y = rand()% (V-2);
  }

   //le damos valores a los mod para que el personaje se mueva en una sola direcion (ariba-abajo o izquierda-derecha)

   for (i=0;i<*tam;i++){
    snake[i].modx=1;
    snake[i].mody=0;
   }

  //crea el campo de juego
  intro_campo(campo);
  //crea la serpiente y la fruta y les asigna sus coordenadas
  intro_datos(campo,*tam);

}

void intro_campo (char campo [V][H]){
int i,j;

 //Caracteres que van a señalar el marco del juego
for (i=0;i<V;i++){
    for (j=0;j<H;j++){
        if (i==0 || i==V-1){
            campo[i][j]='_';
        } else if (j==0 || j==H-1)
            {
                campo[i][j]='|';
            }else
                {
                    campo [i][j]=' ';
                }
    }
}
}

void intro_datos(char campo [V][H],int tam){
 int i;

    //Caracter de la fruta
    campo[fruta.y][fruta.x] = '$';

    //Asigna caracter del cuerpo y posicion del mismo
    for (i=1;i<tam;i++)
    {
      snake[i].x = snake[i-1].x -1;
      snake[i].y = snake[i-1].y;
    //caracter de la cabeza
    snake[0].imagen = 155;

    //en que coordenadas va a impirmir la serpiente en el campo
    for (i=0;i<tam;i++){
        campo[snake[i].y][snake[i].x] = snake[i].imagen;
    }

}

void draw(char campo [V][H],int tam){
 int i,j;
  printf("\n\t\t");

  //imprime el campo en pantalla
 for (i=0;i<V;i++){
    for (j=0;j<H;j++){

    if (campo[i][j] == campo[fruta.y][fruta.x])
        {
            printf("\033[1;33m");
            printf("%c",campo[i][j]);
        }else
            {
                printf("\033[0;32m");
                printf("%c",campo[i][j]);
            }
    }
    printf("\n\t\t");
 }
 printf("\033[1;33m");
 printf("\n\tPulsa 'w' para moverte hacia arriba\n\t");
 printf("Pulsa 's' para moverte hacia abajo");
 printf("\t\tPuntuacion: %i\n\t",tam-4);
 printf("Pulsa 'a' para moverte a la izquierda\n\t");
 printf("Pulsa 'd' para moverte a la derecha\n");
 printf("\033[0m");

}


int loop (char campo [V][H], int tam){
  int muerto,r;
  muerto = 0;
  //verificar si seguimos en el juego (no estamos muertos)
  do{
      system("cls"); //limpia la pantalla
      //crea el campo de juego
      draw(campo,tam);
      //comprubea y verifica los valores
      input(campo,&tam,&muerto);
      //actualiza los datos
      update(campo,tam);
  }while (muerto == 0);
  r=tam;
  return r;
}

void input(char campo[V][H],int *tam,int *muerto){

  int i;
  char key;

  //comprobacion de si hemos muerto

  //chocamos con el marco del campo
  if(snake[0].x == 0 || snake[0].x == (H-1) || snake[0].y == 0 || snake[0].y == (V-1) )
    {
     *muerto = 1;
    }

  //tocamos nuestro propio cuerpo
  for (i=1;i<*tam && *muerto==0;i++){

    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
          *muerto=1;
        }
  }

  //comprobacion de si comemos la fruta
  if (snake[0].x == fruta.x && snake[0].y == fruta.y)
    {

       *tam += 1;
       snake[*tam-1].imagen = 145;

       srand(time(NULL));

       //asigna nuevas coordenadas a la fruta
       fruta.x = rand()% (H-2);
       fruta.y = rand()% (V-2);

     while (fruta.x==0)
    {
        fruta.x = rand()% (H-2);
    }

     while (fruta.y==0)
    {
        fruta.y = rand()% (V-2);
    }
   }

   //comprobacion si presionamos una tecla
   if (*muerto == 0)
    {
      if (kbhit()== 1)
      {
         key = getch();
         //movernos hacia abajo
         if(key == 's')
         {
           snake[0].modx = 0;
           snake[0].mody = 1;
         }
         //movernos hacia arriba
         if (key == 'w' && snake[0].mody != 1)
         {
           snake[0].modx = 0;
           snake[0].mody = -1;
         }
         //movernos hacia la izquierda
         if (key == 'a' && snake[0].modx != 1)
         {
             snake[0].modx = -1;
             snake[0].mody = 0;
         }
          //movernos a la derecha
         if (key == 'd' && snake[0].modx != -1)
         {
             snake[0].modx = 1;
             snake[0].mody = 0;

         }
      }

   }
}

void update(char campo [V][H],int tam){
  //borrar todo los daros de la matriz
  intro_campo(campo);
  //introducir los datos
  intro_datos2(campo,tam);
}

void intro_datos2(char campo [V][H],int tam){
   int i,j;

   //reasignacion de coordenadas de la fruta
   campo [fruta.y][fruta.x] = '$';

  //hacer el estilo de persecucion del cuerpo
  for (i=tam-1;i>0;i--)
    {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }

  //mover a mi serpiente
  snake[0].x += snake[0].modx;
  snake[0].y += snake[0].mody;

  //reasigancion de coordenadas donde se encuntra la serpiente
  for (i=0;i<tam;i++){
    campo[snake[i].y][snake[i].x] = snake[i].imagen;
  }

}

 //Imprime el nombre "SNAKE" del inicio
void pantalla (){
int i,j,k;
 char c[27][26];
 char nombre [5][26];
 char serpiente[19][15];
system("CLS");
 for(i=0;i<27;i++){
  for(j=0;j<26;j++){

     if(i==0)
     {
       if((j>=2 && j<=4)  || (j>=12 && j<=13)  || (j==18)  || (j==19) || (j>=21 && j<=24) )
        {
            nombre [i][j] = '/';
        }else if (j==7)
            {
                nombre [i][j] = '\\';
            }else if (j==6 || j==9 || j==16)
                {
                  nombre [i][j] = '|';
                }else
                    nombre [i][j] = ' ';

        }
      if (i==1)
      {
          if (j==1 || j==2  || (j>=17 && j<=18))
          {
              nombre [i][j] = '/';
          }else if (j==8 || j==7)
            {
                nombre [i][j] = '\\';
            }else if (j==6 || j==9 || j==11 || j==14 || j==21 || j==16)
                {
                  nombre [i][j] = '|';
                }else
                    nombre [i][j] = ' ';
      }
      if (i==2)
      {
       if ((j>=2 && j<=3) || (j>=12 && j<=13)  || (j==17) || (j>=21 && j<=23) )
          {
              nombre [i][j] = '/';
          }else if (j==1 || j==7 || j==4 || j==8)
            {
                nombre [i][j] = '\\';
            }else if (j==6 || j==9 || j==11 || j==14 || (j==16))
                {
                  nombre [i][j] = '|';
                }else
                    nombre [i][j] = ' ';
      }
      if (i==3)
      {
          if (j==3 || j==4)
          {
              nombre [i][j] = '/';
          }else if (j==8 || j==17 || j==18 )
            {
                nombre [i][j] = '\\';
            }else if (j==6 || j==9 || j==21 || j==11 || j==14 || (j==16))
                {
                  nombre [i][j] = '|';
                }else
                    nombre [i][j] = ' ';
      }
      if(i==4)
      {
          if ((j>=1 && j<=3) || (j>=21 && j<=24) )
          {
              nombre [i][j] = '/';
          }else if (  j==18 || j==19)
            {
                nombre [4][j] = '\\';
            }else if (j==6 || j==9 || j==11 || j==14 || (j==16))
                {
                  nombre [i][j] = '|';
                }else
                    nombre [i][j] = ' ';

      }
  }
 }

 printf("\033[1;33m");
 printf("\n\t\t\t\t\t");
    for(i=0;i<5;i++){
            Sleep(200);
     if (i==2)
     {
         printf("\033[1;32m");
     }
        for(j=0;j<26;j++)
        {
            printf("%c",nombre[i][j]);
        }
    printf("\n\t\t\t\t\t");
 }
 printf("\033[0m");

}

 //imprime el dibujo de la serpiente que aparece al iniciar el programa
void serpiente(){
int i,j;
 char serpiente [19][16];
 char a=169;
 for (i=0;i<19;i++){
    for (j=0;j<16;j++)
    {
       if (i==0)
       {
           if (j==7 || (j>=10 && j<=13))
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if(i==1)
       {
           if(j>=7 && j<=14)
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==2 || i==5)
       {
           if((j>=13 && j<=15) || (j>=8 && j<=9))
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==3 || i==4)
       {
           if(j==14 || j==15)
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==5)
       {
           if((j>=4 && j<=9 ) || (j>=13 && j<=15))
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }

       if (i==6)
       {
           if(j>=3 && j<=14)
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==7)
       {
           if((j>=2 && j<=4) || (j>=9 && j<=13))
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==8)
       {
           if(j>=1 && j<=3)
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==9)
       {
           if((j>=1 && j<=2) || (j>=5 && j<=9))
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==10)
       {
           if(j>=1 && j<=10)
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==11)
       {
           if((j>=2 && j<=5) || (j>=9 && j<=11))
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';

       }
       if (i==12)
       {
           if(j>=10 && j<=12)
           {
               serpiente [i][j] = a;
           }else
                serpiente[i][j] = ' ';
       }
       if (i==13)
       {
           if((j>=2 && j<=6) || (j>=11 && j<=13))
           {
               serpiente [i][j] = a;
           }else
                  serpiente[i][j] = ' ';
       }
       if (i==14)
       {
           if((j>=1 && j<=7) || (j>=12 && j<=13))
           {
               serpiente [i][j] = a;
           }else
                  serpiente[i][j] = ' ';
       }
       if (i==15)
       {
           if((j>=1 && j<=4) || (j>=6 && j<=8) || (j>=12 && j<=13) )
           {
               serpiente [i][j] = a;
           }else
                  serpiente[i][j] = ' ';
       }
       if (i==16)
       {
           if((j>=1 && j<=3) || (j>=7 && j<=9) || (j>=11 && j<=13))
           {
               serpiente [i][j] = a;
           }else
                  serpiente[i][j] = ' ';
       }
       if (i==17)
       {
           if(j>=8 && j<=12)
           {
               serpiente [i][j] = a;
           }else
                  serpiente[i][j] = ' ';
       }
       if (i==18)
       {
           if(j>=9 && j<=10)
           {
               serpiente [i][j] = a;
           }else
                  serpiente[i][j] = ' ';
       }




    }
  }
  printf("\n\t\t\t\t\t   ");
  for (i=0;i<19;i++){
        for (j=0;j<16;j++)
        {
            Sleep(10);
            if(i==14)
             {
                 if (j==1)
                  {
                    printf("\033[1;30m");
                    printf("%c",serpiente[i][j]);
                  }else
                    {
                        printf("\033[0;32m");
                        printf("%c",serpiente[i][j]);
                    }
             }else if (i==16)
                    {
                        if (j==3)
                        {
                            printf("\033[1;30m");
                            printf("%c",serpiente[i][j]);
                        }else
                            {
                                printf("\033[0;32m");
                                printf("%c",serpiente[i][j]);
                            }
                    }else
                        {
                            printf("\033[0;32m");
                            printf("%c",serpiente[i][j]);
                        }
     }
        printf("\n\t\t\t\t\t   ");
  }

  printf("\033[0m");

}
