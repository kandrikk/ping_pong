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
    draw_pong();
    return 0;
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
            } else if (x == W_DIV && y == H_DIV) {
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
        char c;
        scanf("%c", c);
        if (c == 'A' || c == 'a') {
            l_racket += 1;
        } else if (c == 'Z' || c == 'z') {
            l_racket -= 1;
        } else if (c == 'K' || c == 'k') {
            r_racket += 1;
        } else if (c == 'M' || c == 'm') {
            r_racket -= 1;
        }
    }
}