#include <iostream>//Библиотека ввода/вывода
#include <time.h> //случайные числа
#include <windows.h> // для HANDLE, курсора, цвета
#include <conio.h>  //для kbhit

#define START 0
#define NEED 30//Необходимое колличаство очков для перехода на следующий

using namespace std;

HANDLE hConsole;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

//Функция для перемещения курсора
void gotoXY(int X, int Y){
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}

struct Snake{// структура змейка
      COORD *t; //точки
      int PCount; //количество сегментов змеи
};

struct Game{ //даные-точности: змейки, яблок, передвижение по X и Y, задержка, направление
    public:
      Snake snake; //змейка
      COORD apple; //яблоко
      int dx,dy; //передвижение
      int pause; //задержка
      int dir; //направление
      int lvl;//Уровень
};

enum ConsoleColor{//Перечисление цветов
        Black         = 0,
        Blue          = 1,
        Green         = 2,
        Cyan          = 3,
        Red           = 4,
        Magenta       = 5,
        Brown         = 6,
        LightGray     = 7,
        DarkGray      = 8,
        LightBlue     = 9,
        LightGreen    = 10,
        LightCyan     = 11,
        LightRed      = 12,
        LightMagenta  = 13,
        Yellow        = 14,
        White         = 15
};

void setColor(ConsoleColor text, ConsoleColor background){//Выбор цвета для символа
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

//Перечисление направлений змейки
enum dirOfSnake{LEFT,UP,RIGHT,DOWN};
//Перечисление уровней змейки
enum level{ONE, TWO, THREE};

void levelOne(){
  setColor(DarkGray, Black);//Устанавливаю цвет стен
  gotoXY(2,2); //Рисуем верхнюю горизонтальную линию-стенку
  for(int i = 0; i < 60; i++){
    cout<<"#";
  }
  gotoXY(2,24); //Рисуем нижнюю горизонтальную линию-стенку
  for(int i = 0; i < 60;i++){
    cout<<"#";
  }
  for(int i = 3; i < 24;i++){//Рисуем левую вертикальную линию-стенку
    gotoXY(2, i);
    cout<<"#";
  }
  for(int i = 3; i < 24;i++){//Рисуем правую вертикальную линию-стенку
    gotoXY(61, i);
    cout<<"#";
  }
}

void levelTwo(){//Отрисовывою второй уровень
  setColor(DarkGray, Black);//Устанавливаю цвет стен
  gotoXY(26,10); //Рисуем верхнюю горизонтальную линию-стенку
  for(int i = 0; i < 11; i++){
    cout<<"#";
  }
  gotoXY(26,16); //Рисуем нижнюю горизонтальную линию-стенку
  for(int i = 0; i < 11;i++){
    cout<<"#";
  }
  for(int i = 11; i < 16;i++){//Рисуем левую вертикальную линию-стенку
    gotoXY(26, i);
    cout<<"#";
  }
  for(int i = 11; i < 16;i++){//Рисуем правую вертикальную линию-стенку
    gotoXY(36, i);
    cout<<"#";
  }
}

void levelThree(){//Отрисовывою второй уровень
  setColor(DarkGray, Black);//Устанавливаю цвет стен
    //Рисуем первый квадрат
  gotoXY(12,6); //Рисуем верхнюю горизонтальную линию-стенку
  for(int i = 0; i < 11; i++){
    cout<<"#";
  }
  gotoXY(12,12); //Рисуем нижнюю горизонтальную линию-стенку
  for(int i = 0; i < 11;i++){
    cout<<"#";
  }
  for(int i = 7; i < 12;i++){//Рисуем левую вертикальную линию-стенку
    gotoXY(12, i);
    cout<<"#";
  }
  for(int i = 7; i < 12;i++){//Рисуем правую вертикальную линию-стенку
    gotoXY(22, i);
    cout<<"#";
  }
    //Второй квадрат
  gotoXY(41,14); //Рисуем верхнюю горизонтальную линию-стенку
  for(int i = 0; i < 11; i++){
    cout<<"#";
  }
  gotoXY(41,20); //Рисуем нижнюю горизонтальную линию-стенку
  for(int i = 0; i < 11;i++){
    cout<<"#";
  }
  for(int i = 15; i < 20;i++){//Рисуем левую вертикальную линию-стенку
    gotoXY(41, i);
    cout<<"#";
  }
  for(int i = 15; i < 20;i++){//Рисуем правую вертикальную линию-стенку
    gotoXY(51, i);
    cout<<"#";
  }
}

//Функция разброски яблок
void addApple(Game &g){
    int i, x, y;
    int n = g.snake.PCount;
    do
    {
        x = rand() % 56+3; //кординаты яблока
        y = rand() % 19+3; //

        for(i = 0; i < n; i++){
            if(x == g.snake.t[i].X && y == g.snake.t[i].Y) // проверка чтоб яблоко не бросить на змею
                break;
        }
        switch (g.lvl) {
          case THREE:
              if((x >= 12 && x <=22)&&(y>=6&&y<=12)||(x >= 41 && x <=51)&&(y>=14&&y<=20))
                i=0;
          case TWO:
              if((x >= 26 && x <=36)&&(y>=10&&y<=16))
                i=0;
          case ONE:
          break;
        }

    }
    while(i < n);

    g.apple.X = x; //запоминаем позицию яблока
    g.apple.Y = y; //

    SetConsoleCursorPosition(hConsole, g.apple); //переносим курсор в эту позицию
    SetConsoleTextAttribute(hConsole,0x0c); //цвет яблока

    cout<<"ó"; //рисуем яблоко
}

// Функцыя старта змейки ее координат и скорости
void gameStart(Game &g, int l){
    system("cls");//Очищаем терминал
    setColor(LightBlue , Black);
    gotoXY(72,2); cout <<l + 1<< endl ;
    g.snake.PCount = 3; //сколько точек в змейке
    g.snake.t = new COORD [3];//создали точки

    for(int i = 0; i < 3; i++){//Начальное положение змеи
        g.snake.t[i].X = 20 + i;
        g.snake.t[i].Y = 20;
    }
    g.dx = 1;
    g.dy = 0;
    g.pause = 100;//скорость передвижение змеи
    g.dir = RIGHT;//Изначально направление вправо
    g.lvl = l;

    switch (l) {//Отрисовываем уровни
    case THREE:
        levelThree();
    case TWO:
        levelTwo();
    case ONE:
        levelOne();
    break;
    }
    srand(time(0));
    addApple(g);//рисуем яблоко
}

void interfaseOfGame() //Вся информация и стены
{
    setColor(LightBlue , Black);
    gotoXY(64,2);cout <<  "Уровень:" << endl ; //Данные
    gotoXY(64,3);cout <<  "Яблок:0     " << endl ; //Яблок
    gotoXY(64,4); cout <<  "Длинна:3     "<< endl; //Длина
    gotoXY(64,5); cout <<  "Скорость:0     " << endl; //Скорость

    gotoXY(64,7); cout << "Управление:" <<  endl; //Управление
    gotoXY(64,8); cout << "Esc:Выход" <<  endl; //Выход
    gotoXY(64,9); cout << "P:Пауза" <<  endl; //Пауза
}

//Перечисление игровых состояний
enum {END, WALL, PLUS, MOVE};

//Функция для отрисовки движения змеи
int move(Game &g){
    int & n = g.snake.PCount;
    COORD head = g.snake.t[n - 1]; //голова
    COORD tail = g.snake.t[0]; //хвост
    COORD next;
    next.X = head.X + g.dx;//проверка следующей точки по направлению
    next.Y = head.Y + g.dy;

    switch (g.lvl) {//не уперлась ли в стену?
      case THREE:
          if((next.X >= 12 && next.X <=22)&&(next.Y>=6&&next.Y<=12)||(next.X >= 41 && next.X <=51)&&(next.Y>=14&&next.Y<=20))
            return WALL;
      case TWO:
          if((next.X >= 26 && next.X <=36)&&(next.Y>=10&&next.Y<=16))
            return WALL;
      case ONE:
          if(next.X < 3 || next.Y < 3 || next.X > 60 || next.Y > 23)
            return WALL;
      break;
    }

    if(n > 4){//Если змейка имеет больше 4-х сегментов
        for(int i = 0; i < n; i++)
            if(next.X == g.snake.t[i].X && next.Y == g.snake.t[i].Y) //не наехали ли на себя?
                return END;
    }

    if(next.X == g.apple.X && next.Y == g.apple.Y){
        COORD*temp = new COORD[ ++n ]; //новый масив больший на 1
        for(int i = 0; i < n; i++)
            temp[i] = g.snake.t[i]; //перекопируем
        temp[n - 1] = next; //добавляем одну
        delete [] g.snake.t;
        g.snake.t = temp;

        SetConsoleCursorPosition(hConsole, head);
        SetConsoleTextAttribute(hConsole, 0x0a); //закрашываем яблоко которое сели
        cout<<"o";

        SetConsoleCursorPosition(hConsole, next);//Меняем цвет головы змеи при познятии яблока
        SetConsoleTextAttribute(hConsole,0x0a);
        cout<<"O";

        addApple(g);//Добавляем яблоко
        return PLUS;
    }

    for(int i = 0; i < n - 1; i++)
        g.snake.t[i] = g.snake.t[i + 1];
    g.snake.t[n - 1] = next;
    SetConsoleCursorPosition(hConsole, tail);//закрашиваем хвостик
    cout<<" ";

    SetConsoleCursorPosition(hConsole, head);
    SetConsoleTextAttribute(hConsole, 0x0a);//красим хвост змеи в зелений цвет
    cout<<"o";

    SetConsoleCursorPosition(hConsole, next);
    SetConsoleTextAttribute(hConsole,0x0f); //красим курсор в белый цвет (голову змеи)
    cout<<"O";
    return MOVE;
}

//Вывод интро
void intro(){
    system("cls");
    gotoXY(16,10);
    cout<<"Это игра змейка. Чтобы выиграть необходимо собрать змейкой 30 яблок. В каждом уровне.";
    gotoXY(16,11);
    cout<<" Всего уровней 3. Скорость игры постоянно увеличивается, с каждым собранным яблоком.";
    gotoXY(16,12);
    cout<<"           Управление в игре производится стрелочками на клавиатуре.";
    gotoXY(16,13);
    cout<<"        ВНИМАНИЕ! Кнопки кроме стрелок не работают на русской раскладке!";
    gotoXY(50,14);
    cout<<"Удачи :D";
    gotoXY(16,15);
    cout<<"              (Чтобы начать игру нажмите на любую клавишу)";
    getch();
    Sleep(300);
}

void blinking(){// Скрываю курсор
  void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO structCursorInfo;
  GetConsoleCursorInfo(handle,&structCursorInfo);
  structCursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo( handle, &structCursorInfo );
}

int main(void){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //получаем дескриптор консоли
    system("chcp 65001");//Переключаю консоль в UTF-8
    blinking();//Скрываем курсор для комфортной игры
    intro();
    int key = 0, count = 0, lvl = START;
    Game g;
    bool pause = false;

    gameStart(g, lvl);
    interfaseOfGame();

    while(key != 27){//Пока не нажат Esc
      Sleep(5);
        while(!kbhit()){ //ждет пока нажмем

            if(pause){//Проверка флага паузы
                Sleep(1);
                continue;
            }

            switch (move(g)){//движение
            case PLUS:
                ++count;
                g.pause-=1;
                //Вывод информации
                setColor(LightBlue , Black);
                gotoXY(70,3); cout <<count<< endl ; //Яблок
                gotoXY(71,4); cout <<g.snake.PCount<< endl; //Длина
                gotoXY(73,5); cout  <<(-1 * (g.pause - 100))<< endl; //Скорость

                if (count == NEED){//Проверка количества съеденных яблок
                    setColor(White , Black);
                    gotoXY(27,10); cout << "Победа!!!" << endl; //Вы прошли уровень
                    if(g.lvl == THREE){
                      gotoXY(15,11); cout << "Вы прошли всю игру! Вы не человек!" << endl;//Прошли игру
                      getch();
                      system("cls");
                      return 0;
                    }
                    lvl++;//Увеличиваем уровен
                    gotoXY(21,11); cout << "Следующий уровень: " <<lvl+1<< endl;
                    gotoXY(11,12); cout << "(Нажмите на любую клавишу, чтобы начать)"<< endl;
                    getch();
                    Sleep(300);
                    gameStart(g, lvl);
                    interfaseOfGame();
                    count = 0;
                    pause = false;
                    continue;
                }
                break;

            case WALL:
            case END:
                setColor(White , Black);
                gotoXY(13,10); cout <<"            Вы проиграли."; //Вы проиграли
                gotoXY(13,11); cout <<"Если хотите начать сначала, нажмите S.";
                gotoXY(13,12); cout <<"Если хотите выйти из игры нажмите Esc.";
                while(true){
                  key = getch();
                  Sleep(300);
                  if(key == 27){//Если нажали Esc
                    delete [] g.snake.t;//Очищайм память
                    system("cls");//Очищаем экран
                    return 0;
                  }
                  else if(key == 's' || key == 'S'){
                    delete[] g.snake.t;//Очищаем память
                    count = 0;
                    lvl = START;
                    gameStart(g, lvl);
                    interfaseOfGame();
                    pause = false;
                    break;
                  }
                }
                  continue;
            }
            Sleep(g.pause); //Задержка
        }

        key = getch();
        if(key=='P' || key=='p')
            pause=!pause;
        else if(key==0||key==224){
            key = getch();//Очищаем буфер для kbhit
            if(key == 72 && g.dir != DOWN){
                g.dir = UP;
                g.dx = 0;
                g.dy = -1;
            }
            else if(key == 80 && g.dir != UP){
                g.dir = DOWN;
                g.dx = 0;
                g.dy = 1;
            }
            else if(key == 75 && g.dir != RIGHT){
                g.dir = LEFT;
                g.dx = -1;
                g.dy = 0;
            }
            else if(key == 77 && g.dir != LEFT){
                g.dir = RIGHT;
                g.dx = 1;
                g.dy = 0;
            }
        }
    }
    delete [] g.snake.t;//Очищайм память
    system("cls");//Очищаем экран
    return(0);
}
