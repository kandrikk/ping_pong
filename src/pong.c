#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define MIDDLE 25 

#define W_DIV 40
#define H_DIV 25/2

int x_ball = W_DIV;
int y_ball = H_DIV;
int r_racket = H_DIV;
int l_racket = H_DIV;
int dx = -1;
int dy = -1;

void draw_pong();
void series();
void pong();
void clear();
void move();

int main() {
    pong();
    return 0;
}

void pong() {
    series();
}

void draw_pong() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (y == 0 || y == HEIGHT - 1) {
                printf("*");
            } else if (x == 0 || x == WIDTH - 1) {
                printf("#");
            } else if (x == 3 && (y == l_racket || y == l_racket - 1 || y == l_racket + 1)) {
                printf("\x1b[32m]\x1b[0m");
            } else if (x == WIDTH - 4 && (y == r_racket || y == r_racket - 1 || y == r_racket + 1)) {
                printf("\x1b[32m[\x1b[0m"); 
            } else if (x == x_ball && y == y_ball) {
                printf("\x1b[32m@\x1b[0m");
            } else if (x == W_DIV) {
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}  

void series() {
    while(1) {
        clear();
        draw_pong();
        char c;
        if (scanf("%c", &c) == 1) {
            if (c == 'A' || c == 'a') ++l_racket;
            if (c == 'Z' || c == 'z') --l_racket;
            if (c == 'K' || c == 'k') ++r_racket;
            if (c == 'M' || c == 'm') --r_racket;
            if (c == 'Q' || c == 'q') break;
        }
        move();
    }
}

void move() {
    x_ball += dx;
    y_ball += dy;

    if (y_ball <= 2) dy = 1;
    if (y_ball >= HEIGHT -2) dy = -1;

}

void clear() {
    for (int i = 0; i < 3; ++i) printf("\n");
}