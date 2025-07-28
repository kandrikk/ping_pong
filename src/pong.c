#include <stdio.h>
#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25

int x_ball = WIDTH/2;
int y_ball = HEIGHT/2;
int r_racket = 11;
int l_racket = 11;

int dx = -1;
int dy = -1;

int l_res = 0;
int r_res = 0;

void draw_pong();
void series();
void pong();
void ball_move();
int racket_move();
void instruction(int l, int r);

int main() {
    pong();
    return 0;
}

void pong() {
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_YELLOW); // поле верх низ право лево
    init_pair(2, COLOR_RED, COLOR_RED);  // ракетки left
    init_pair(22, COLOR_BLUE, COLOR_BLUE); //  right
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // мячик
    init_pair(4, COLOR_BLACK, COLOR_BLACK); // бек

    init_pair(5, COLOR_GREEN, COLOR_GREEN);

    
    noecho();
    cbreak();

    series();
    clear();

    endwin(); 
    clear();
}

void draw_pong() {
    clear();
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (y == 0 || y == HEIGHT - 1) {
                attron(COLOR_PAIR(1));  // поле
                mvaddch(y, x, ' ');
                attroff(COLOR_PAIR(1));
            } else if (x == 0 || x == WIDTH - 1) {
                attron(COLOR_PAIR(1));
                mvaddch(y, x, ' ');
                attroff(COLOR_PAIR(1));
            } else if (x == 3 && (y >= l_racket &&  y <= l_racket + 2)) { // ракетки
                attron(COLOR_PAIR(2));
                mvaddch(y, x, ' ');
                attroff(COLOR_PAIR(2));
            } else if (x == WIDTH - 4 && (y >= r_racket &&  y <= r_racket + 2)) {
                attron(COLOR_PAIR(22));
                mvaddch(y, x, ' ');
                attroff(COLOR_PAIR(22));
            } else if (x == x_ball && y == y_ball) { // мяч
                mvaddch(y, x, 'o');
            } else if (x == WIDTH/2) {
                mvaddch(y, x, '|');
            } else { 
                attron(COLOR_PAIR(4));
                printw(" ");
                attroff(COLOR_PAIR(4));
            }

        }
    }
    printw("\n");
} 

void series() {
    while(!(l_res >= 5 || r_res >= 5)) {
        draw_pong();
        instruction(l_res, r_res);        
        ball_move();

        if(!(racket_move())) {
        break;
        }
        mvaddstr(87, 6, "==ИНСТРУКЦИЯ==");
    }
}

int racket_move() {
    char c = getch();
    if (c == 'A' || c == 'a') {
        --l_racket;
        return 1;
    } else if (c == 'Z' || c == 'z') {
        ++l_racket;
        return 1;
    } else if (c == 'K' || c == 'k') {
        --r_racket;
        return 1;
    } else if (c == 'M' || c == 'm') {
        ++r_racket;
        return 1;
    } else if (c == 'Q' || c == 'q') {
        return 0;
    }
}

void ball_move() {
    x_ball += dx;
    y_ball += dy;

    if (y_ball <= 1) dy = 1;
    if (y_ball >= HEIGHT - 2) dy = -1;

    if (x_ball == 4) {
        if (y_ball >= l_racket - 1 && y_ball <= l_racket + 3) {
            dx = 1;
        }
    }

    if (x_ball == WIDTH - 5) {
        if (y_ball >= r_racket - 1 && y_ball <= r_racket + 3) {
            dx = -1;
        }
    }

    if (x_ball <= 1) {
        x_ball = WIDTH/2;
        y_ball = HEIGHT/2;
        r_res += 1;
    }
    
    if (x_ball >= WIDTH -2) {
        x_ball = WIDTH/2;
        y_ball = HEIGHT/2;
        l_res += 1;
    }

}

void instruction(int l, int r) {
    int x = 85;
    int y = 4;
    int u = 7;
    int b = 5;
    attron(COLOR_PAIR(5)); // верх
    mvhline(y, x, ' ', 40);
    mvvline(y + 1, x, ' ', 17);
    
    mvhline(HEIGHT - y, x, ' ', 40);
    mvvline(y + 1, x + 40 - 1, ' ', 17);
    attroff(COLOR_PAIR(5));

mvaddstr(6 , 87 + u,  "====================");
mvaddstr(7 , 87 + u,  "       SCORE:       ");
mvaddstr(8 , 87 + u,  "====================");
mvprintw(9 , 87 + u,  "=LEFT PLAYER+=== %d =", l);
mvprintw(10 , 87 + u, "= %d ==RIGHT PLAYER=", r);

mvaddstr(9 + b, 87 + u,  "");
mvaddstr(10 + b, 87 + u, "CONTROL:");
mvaddstr(11 + b, 87 + u, "  A / Z   AND   K / M");
mvaddstr(12 + b, 87 + u, "");
mvaddstr(13 + b, 87 + u, "Press 'Q' to EXIT");


}