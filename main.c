#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


typedef struct Circle {
    float r;
    struct Vector2 pos;
}Circle;

typedef struct Timer {
    float time;
    float length;
    bool on;
} Timer;

// true if the timer is up
bool update_timer(Timer* timer, float dt) {
    timer->time += dt;
    if (timer->time >= timer->length) return true; 
    else return false; 
}

void reset_timer(Timer* timer, float length) {
    timer->length = length;
    timer->time = 0;
};

int main(void)
{
    
    const float screenWidth = 800;
    const float screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    float dt;
    SetTraceLogLevel(LOG_DEBUG);

    Vector2 origin = {screenWidth/2.0f, screenHeight/2.0f};
    Circle zone = { 
        .pos = origin,
        .r = 100,
    };

    Circle ball = {
        .pos = origin,
        .r = 25,
    };

    Vector2 ball_vel = {0};
    const int speed_multiplyer = 10;

    const float shoot_cooldown_length = .3;
    bool click = false;
    bool shot = false;
    bool computed_vel = false;
    Timer shoot_cooldown = {0};
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        dt = GetFrameTime();
        Vector2 mspos = GetMousePosition();
        if (!shot && !click) {
            if (checkCollisionPointCircle(ball.pos.x, ball.pos.y, ball.r) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                click = true;
            }
        } else {
            if (!shot && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                shot = true;
            }

            if (shot && !computed_vel) {
                compute_velocity(&ball_vel, mspos, zone);
                computed_vel = true;
            }
            if (CheckCollisionPointCircle(mspos, zone.pos, zone.r) && !checked) {
                checked = true;
                
                // TraceLog(LOG_DEBUG, TextFormat("X:%f, Y:%f", norm.x, norm.y)); 
            }
        }

        if (shot) {
            reset_timer(&shoot_cooldown, shoot_cooldown_length);
        }
        if (shoot_cooldown.on) {
            shot = !(update_timer(&shoot_cooldown, dt));
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (click && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawLine(ball.pos.x, ball.pos.y, mspos.x, mspos.y, GREEN);
            }

            DrawCircleLines(zone.pos.x, zone.pos.y, zone.r, BLACK);
            if(checked) {
                ball.pos.x += ball_vel.x * GetFrameTime() * 100;
                ball.pos.y += ball_vel.y * GetFrameTime() * 100;
            }
            DrawCircle(ball.pos.x, ball.pos.y, ball.r, RED);
            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();

    return 0;
}

void compute_velocity(Vector2* ball_vel, Vector2 mspos, Circle zone) {
    Vector2 pos = {mspos.x-zone.pos.x, mspos.y-zone.pos.y};
    float mag = sqrt(pos.x*pos.x + pos.y*pos.y);

    if (mag > 0) {
        ball_vel->x = pos.x/mag;
        ball_vel->y = pos.y/mag;
    } else {
        ball_vel->x = 0;
        ball_vel->y = 0;
    }
}