#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define max_x  80
#define max_y  25
#define color_border COLOR_RED
#define color_field COLOR_GREEN

enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=27};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};



// Здесь храним коды управления змейкой
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
}control_buttons;

struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct tail_t
{
    int x;
    int y;
} tail_t;

void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t={0,0};
    for(size_t i=0; i<size; i++)
    {
        t[i]=init_t;
    }
}
void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail;                              // прикрепляем к голове хвост
    head->tsize = size+1;
    head->controls = default_controls;
}


 //Разметка поля игры
 void print_color_border(int y, int x)
{
    start_color();
    init_pair(1, COLOR_WHITE, color_border);
    attron(COLOR_PAIR(1));
    mvprintw (y,x," ");
    attroff(COLOR_PAIR(1));
}

void print_color_field (int y, int x)
{
    start_color();
    init_pair(2, COLOR_WHITE, color_field);
    attron(COLOR_PAIR(2));
    mvprintw (y,x," ");
    attroff(COLOR_PAIR(2));
}

void print_game_field ()
{
    int y = 1, x = 0;
    for (x = 0; x < max_x; x++)
    {
        print_color_border (y, x);
    }
    for (y = 2; y < max_y; y++)
    {
        x = 0;
        print_color_border (y, x);
        for (x = 1; x < max_x-1; x++)
        {
            print_color_field (y,x);
        }
        print_color_border (y, x);
    }
    for (x = 0; x < max_x; x++)
        print_color_border (y, x);
}
/*
 Движение головы с учетом текущего направления движения
 */
 
void print_head_snake (int y, int x)
{
    start_color();
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(3));
    mvprintw (y,x,"@");
    attroff(COLOR_PAIR(3));
}

void go(struct snake_t *head)
{
    switch (head->direction)
    {
        case LEFT:
            if(head->x <= 1)                            // Циклическое движение, чтобы не уходить за пределы игрового поля
                head->x = max_x-1;
            print_head_snake (head->y,--(head->x));
        break;
        case RIGHT:
            if(head->x >= max_x-2)                      // Циклическое движение, чтобы не уходить за пределы игрового поля
                head->x = max_x-(head->x+2);
            print_head_snake(head->y, ++(head->x));
        break;
        case UP:
        if(head->y <= 2)                                 // Циклическое движение, чтобы не уходить за пределы игрового поля
                head->y = max_y;
            print_head_snake(--(head->y), head->x);
        break;
        case DOWN:      
        if(head->y >= max_y-1)                            // Циклическое движение, чтобы не уходить за пределы игрового поля
                head->y = max_y-(head->y);
            print_head_snake(++(head->y), head->x);
        break;
        default:
        break;
    }
    refresh();
}



void changeDirection(struct snake_t* snake, const int32_t key)
{
    if (key == snake->controls.down)
        snake->direction = DOWN;
    else if (key == snake->controls.up)
        snake->direction = UP;
    else if (key == snake->controls.right)
        snake->direction = RIGHT;
    else if (key == snake->controls.left)
        snake->direction = LEFT;
}

/*
 Движение хвоста с учетом движения головы
 */
 
void print_color_tail (int y, int x)
{
    start_color();
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(4));
    mvprintw (y,x," ");
    attroff(COLOR_PAIR(4));
}
    
void goTail(struct snake_t *head)
{
    print_color_field (head->tail[head->tsize-1].y, head->tail[head->tsize-1].x);
    for(size_t i = head->tsize-1; i>0; i--)
    {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            print_color_tail (head->tail[i].y, head->tail[i].x);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}
/*
 *  Проверка на врезание в себя
 */
int check_damage (struct snake_t *head)
{
    for (int i = 1; i <= head->tsize; i++)
    {
        if (head->x == head->tail[i].x && head->y == head->tail[i].y)
            return 1;
    }
    return 0;
}

/*
 * Задежка через clock
*/

void delay (double DELAY)
{
    clock_t begin = clock();
    while ((double)(clock()-begin)/CLOCKS_PER_SEC < DELAY){}
}

int main()
{
start:
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake,START_TAIL_SIZE,max_x/2,max_y/2);
    initscr();
    keypad(stdscr, TRUE);                                // Включаем F1, F2, стрелки и т.д.
    raw();                                               // Откдючаем line buffering
    noecho();                                            // Отключаем echo() режим при вызове getch
    curs_set(FALSE);                                     //Отключаем курсор
    mvprintw(0, 0," Use arrows for control. Press 'ESC' for EXIT");
    timeout(0);                                          //Отключаем таймаут после нажатия клавиши в цикле
    print_game_field();
    int key_pressed=0, damaged = 0;
    while( key_pressed != STOP_GAME && damaged != 1)
    {
        key_pressed = getch();                           // Считываем клавишу
        go(snake);
        goTail(snake);
        timeout(100); // Задержка при отрисовке
        //delay (0.1);
        changeDirection(snake, key_pressed);
        damaged = check_damage (snake);
    }
    if (damaged == 1)
    {
        wclear(stdscr);
        mvprintw((max_y/2), max_x/2-5,"GAME OVER");
        mvprintw((max_y/2)+1, max_x/2-15,"ESC to exit, Anny key NEW GAME");
        timeout(2000);
        if ((key_pressed = getch()) == STOP_GAME || NULL)
            goto end;
        else
        {
            free(snake->tail);
            goto start;
        }
    }
end:
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
