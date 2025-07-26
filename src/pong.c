#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define MIDDLE 25 

#define W_DIV 40
#define H_DIV 25/2

int res1 = 0;
int res2 = 0;

int x_ball;
int y_ball;
int r_racket = H_DIV;
int l_racket = H_DIV;

void draw_pong();
void series();
void pong();
void clear();

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
                printf("]");
            } else if (x == WIDTH - 4 && (y == r_racket || y == r_racket - 1 || y == r_racket + 1)) {
                printf("["); 
            } else if (x == x_ball && y == y_ball) {
                printf("@");
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
    while(res1 < 21 || res2 < 21) {
        draw_pong();
        char c;
        if (scanf("%c", c) == 1) {
            if (c == 'A' || c == 'a') ++l_racket;
            else if (c == 'Z' || c == 'z') --l_racket;
            else if (c == 'K' || c == 'k') ++r_racket;
            else if (c == 'M' || c == 'm') --r_racket;
            clear();
        }
    }
}

void clear() {
    for (int i = 0; i < 50; ++i) printf("\n");
}