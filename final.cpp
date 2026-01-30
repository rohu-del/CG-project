#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 640
#define HEIGHT 480
#define BIRD_WIDTH 20
#define BIRD_HEIGHT 20
#define PIPE_WIDTH 60
#define PIPE_GAP 200

/* Draw the static scenery */
void draw_background() {
    // Draw Sky
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, WIDTH, HEIGHT);

    // Draw a Sun
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(550, 50, 30, 30);

    // Draw some simple Clouds
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(100, 60, 30, 20);
    fillellipse(130, 60, 40, 25);
    fillellipse(160, 60, 30, 20);

    // Draw Grass/Ground
    setfillstyle(SOLID_FILL, GREEN);
    bar(0, HEIGHT - 20, WIDTH, HEIGHT);
}

void draw_bird(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x, y, BIRD_WIDTH / 2, BIRD_HEIGHT / 2);
    // Add a small eye
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x + 5, y - 3, 2, 2);
}

void draw_pipe(int x, int y) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, GREEN);

    // Top Pipe
    bar(x, 0, x + PIPE_WIDTH, y);
    rectangle(x, 0, x + PIPE_WIDTH, y);

    // Bottom Pipe
    bar(x, y + PIPE_GAP, x + PIPE_WIDTH, HEIGHT - 20);
    rectangle(x, y + PIPE_GAP, x + PIPE_WIDTH, HEIGHT - 20);
}

void update_bird(int &y, int &speed) {
    y += speed;
    speed += 1; // gravity
    if (y > HEIGHT - 30) { y = HEIGHT - 30; speed = 0; }
    if (y < 0) { y = 0; speed = 0; }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    srand(time(0));
    int bird_x = 100, bird_y = HEIGHT / 2, bird_speed = 0;
    int pipe_x = WIDTH;
    int pipe_y = rand() % (HEIGHT - PIPE_GAP - 120) + 50;
    int score = 0;

    int page = 0; // Toggle for double buffering

    while (1) {
        // --- DOUBLE BUFFERING START ---
        setactivepage(page);        // Draw on the hidden page
        setvisualpage(1 - page);    // Show the previous finished page
        cleardevice();              // Clear the hidden page
        // ------------------------------

        draw_background();
        draw_pipe(pipe_x, pipe_y);
        draw_bird(bird_x, bird_y);

        /* Score Display Overlay */
        setfillstyle(SOLID_FILL, BLACK);
        bar(5, 5, 130, 35);
        setcolor(WHITE);
        rectangle(5, 5, 130, 35);
        char score_str[30];
        sprintf(score_str, "SCORE: %d", score);
        outtextxy(15, 15, score_str);

        if (kbhit()) {
            char ch = getch();
            if (ch == ' ') bird_speed = -8;
            if (ch == 27) break;
        }

        update_bird(bird_y, bird_speed);
        pipe_x -= 8;

        if (pipe_x + PIPE_WIDTH < 0) {
            pipe_x = WIDTH;
            pipe_y = rand() % (HEIGHT - PIPE_GAP - 120) + 50;
            score++;
        }

        /* Collision detection */
        if (bird_x + 10 > pipe_x && bird_x - 10 < pipe_x + PIPE_WIDTH) {
            if (bird_y - 10 < pipe_y || bird_y + 10 > pipe_y + PIPE_GAP) {
                setactivepage(page); // Ensure "Game Over" draws on the current page
                setcolor(RED);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(WIDTH / 2 - 100, HEIGHT / 2, "GAME OVER");
                setvisualpage(page); // Show the game over screen
                break;
            }
        }

        // Flip the pages for the next frame
        page = 1 - page;

        delay(20);
    }

    getch();
    closegraph();
    return 0;
}
