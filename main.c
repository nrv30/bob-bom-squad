#include "raylib.h"
#include <stdlib.h>
#include <math.h>


typedef struct Circle {
    float r;
    struct Vector2 pos;
}Circle;

int main(void)
{
    
    const float screenWidth = 800;
    const float screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
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

    Vector2 vel = {0};
    bool checked = false;
    const int speed = 10;
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        Vector2 mspos = GetMousePosition();
        if (CheckCollisionPointCircle(mspos, zone.pos, zone.r) && !checked) {
            checked = true;
            Vector2 pos = {mspos.x-zone.pos.x, mspos.y-zone.pos.y};
            float mag = sqrt(pos.x*pos.x + pos.y*pos.y);

            if (mag > 0) {
                vel.x = pos.x/mag;
                vel.y = pos.y/mag;
            } else {
                vel.x = 0;
                vel.y = 0;
            }
            // TraceLog(LOG_DEBUG, TextFormat("X:%f, Y:%f", norm.x, norm.y));
            
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            
            DrawCircleLines(zone.pos.x, zone.pos.y, zone.r, BLACK);
            if(checked) {
                ball.pos.x += vel.x * GetFrameTime() * 100;
                ball.pos.y += vel.y * GetFrameTime() * 100;
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