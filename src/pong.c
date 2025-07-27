#include <stdio.h>
#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25
#define MIDDLE 25 

int x_ball = WIDTH/2;
int y_ball = HEIGHT/2;
int r_racket = HEIGHT/2;
int l_racket = HEIGHT/2;

int dx = 1;
int dy = -1;

int l_res = 0;
int r_res = 0;

void draw_pong();
void series();
void pong();
void _move();
void gameover();
void p_win();

int main() {
    initscr();
    noecho();
    cbreak();
    pong();
    return 0;
}

void pong() {
    series();
    gameover();
}

void draw_pong() {
    clear();

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (y == 0 || y == HEIGHT - 1) {
                mvaddch(y, x, '*');
            } else if (x == 0 || x == WIDTH - 1) {
                mvaddch(y, x, '#');
            } else if (x == 3 && (y == l_racket || y == l_racket - 1 || y == l_racket + 1)) {
                mvaddch(y, x, ']');
            } else if (x == WIDTH - 4 && (y == r_racket || y == r_racket - 1 || y == r_racket + 1)) {
                mvaddch(y, x, '[');
            } else if (x == x_ball && y == y_ball) {
                mvaddch(y, x, '@');
            } else if (x == WIDTH/2) {
                mvaddch(y, x, '.');
            }
        }
    }
}  

void series() {
    while(!(l_res >= 5 || r_res >= 5)) {
        draw_pong();
        char c = getch();
        if (c == 'A' || c == 'a') --l_racket;
        if (c == 'Z' || c == 'z') ++l_racket;
        if (c == 'K' || c == 'k') --r_racket;
        if (c == 'M' || c == 'm') ++r_racket;
        if (c == 'Q' || c == 'q') break;
        _move();
    }
}

void _move() {
    x_ball += dx;
    y_ball += dy;

    if (y_ball <= 1) dy = 1;
    if (y_ball >= HEIGHT -2) dy = -1;

    if (x_ball == 4) {
        if (y_ball == l_racket || y_ball == l_racket-1 || y_ball == l_racket +1) {
            dx = 1;
        }
    }

    if (x_ball == WIDTH - 6) {
        if (y_ball == r_racket || y_ball == r_racket-1 || y_ball == r_racket +1) {
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

void gameover() {
    p_win(l_res, r_res);
}

void p_win(int a , int b) {
    if (a > b) {
        printf("\x1b[32m------------------------LEFT PLAYERS WIN!!!!-------------------------\x1b[0m\n\n");
    } else {
        printf("\x1b[32m------------------------RIGHT PLAYERS WIN!!!!-------------------------\x1b[0m\n\n");
    }
}