/*******************************************************************************************
*
*   raylib gamejam template
*
*   Code licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2026 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>      // Emscripten library
#endif

#include <stdio.h>                          // Required for: printf()
#include <stdlib.h>                         // Required for: 
#include <string.h>                         // Required for:
// #include <math.h>
#include <cmath>

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
// Simple log system to avoid printf() calls if required
// NOTE: Avoiding those calls, also avoids const strings memory usage
#define SUPPORT_LOG_INFO
#if defined(SUPPORT_LOG_INFO)
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...)
#endif

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum { 
    SCREEN_LOGO = 0, 
    SCREEN_TITLE, 
    SCREEN_GAMEPLAY, 
    SCREEN_ENDING
} GameScreen;

// TODO: Define your custom data types here

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static const int screenWidth = 720;
static const int screenHeight = 720;

static RenderTexture2D target = { 0 };  // Render texture to render our game
static int frameCounter = 0;

// TODO: Define global variables here, recommended to make them static

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);      // Update and Draw one frame

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
#if !defined(_DEBUG)
    SetTraceLogLevel(LOG_NONE);         // Disable raylib trace log messages
#endif

    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib gamejam template");
    
    // TODO: Load resources / Initialize variables at this point
    
    // Render texture to draw, enables screen scaling
    // NOTE: If screen is scaled, mouse input should be scaled proportionally
    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);     // Set our game frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);
    
    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

class Hexagon
{
private:
    /* data */
public:
    float xcenter;
    float ycenter;
    float xorigin;
    float yorigin;
    float radius = 80;
    float angle = 60 * 3.142 / 180;
    int tebal = 6;
    int array[6] = {0, 0, 0, 0, 0, 0};
    bool isClicked;
    int randomList[13] = {1, 2, 3, 4, 5, 6, -1, -2, -3, -4, -5, -6, 0};

    Hexagon(int index) {

        float tile_spot = screenWidth/4.0f;
        set_values();
        xcenter = index * tile_spot;
        ycenter = 550;
        xorigin = xcenter;
        yorigin = ycenter;
    }

    void draw() {

        DrawPoly((Vector2){ xcenter, ycenter }, 6, radius, 0.0f, SKYBLUE);
        DrawPolyLinesEx((Vector2){ xcenter, ycenter }, 6, radius, 0.0f, tebal, GOLD);

        for (int i = 0; i < 6; i++) {
            DrawLineEx((Vector2){ xcenter, ycenter }, (Vector2){ xcenter + (radius - 3) * cos(i * angle), ycenter + (radius - 3) * sin(i * angle) }, tebal, GOLD);
        }

        float temp_angle = (angle / 2);
        
        for (int i = 0; i < 6; i++) {
            DrawText(TextFormat("%d", array[i]), (xcenter - 10) + (radius - 33) * cos(temp_angle + i * angle), (ycenter - 10) + (radius - 33) * sin(temp_angle + i * angle), 27, BLACK);
        }
    }

    void set_values() {

        for (int i = 0; i < 6; i++) {

            array[i] = randomList[rand() % 13];

        }
    }

    void update(Vector2 mouse_pos, float dt) {

        float ease = 0.1;

        if (isClicked && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            xcenter += (mouse_pos.x - xcenter) * ease;
            ycenter += (mouse_pos.y - ycenter) * ease;
        } else {
            isClicked = false;
            xcenter += (xorigin - xcenter) * ease;
            ycenter += (yorigin - ycenter) * ease;
        }

        bool isInside = CheckCollisionPointCircle(mouse_pos, (Vector2){ xcenter, ycenter }, radius - 3);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isInside) {
            isClicked = true;
        }
    }
};

//--------------------------------------------------------------------------------------------
// Module Functions Definition
//--------------------------------------------------------------------------------------------
// Update and draw frame
Hexagon hex1(1);
Hexagon hex2(2);
Hexagon hex3(3);

class MainHexagon
{
public:
    float xcenter;
    float ycenter;
    float radius = 80;
    float angle = 60 * 3.142 / 180;
    int tebal = 6;
    int array[6] = {0, 0, 0, 0, 0, 0};
    bool isClicked;

    MainHexagon() {

        xcenter = screenWidth/2.0f;
        ycenter = 350;
    }

    void draw() {

        DrawPoly((Vector2){ xcenter, ycenter }, 6, radius, 0.0f, SKYBLUE);
        DrawPolyLinesEx((Vector2){ xcenter, ycenter }, 6, radius, 0.0f, tebal, GOLD);

        for (int i = 0; i < 6; i++) {
            DrawLineEx((Vector2){ xcenter, ycenter }, (Vector2){ xcenter + (radius - 3) * cos(i * angle), ycenter + (radius - 3) * sin(i * angle) }, tebal, GOLD);
        }

        float temp_angle = (angle / 2);
        
        for (int i = 0; i < 6; i++) {
            DrawText(TextFormat("%d", array[i]), (xcenter - 10) + (radius - 33) * cos(temp_angle + i * angle), (ycenter - 10) + (radius - 33) * sin(temp_angle + i * angle), 27, BLACK);
        }
    }

    void update_values(Hexagon *chosen_hex) {

        for (int i = 0; i < 6; i++) {
            
            array[i] += chosen_hex->array[i];
        }

        chosen_hex->set_values();

        hex1.set_values();
        hex2.set_values();
        hex3.set_values();
    }

    void update() {

        if (!IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            return;
        }

        if (CheckCollisionCircles((Vector2){ xcenter, ycenter }, radius - 3, (Vector2){ hex1.xcenter, hex1.ycenter }, hex1.radius - 3)) {

            update_values(&hex1);
        }

        if (CheckCollisionCircles((Vector2){ xcenter, ycenter }, radius - 3, (Vector2){ hex2.xcenter, hex2.ycenter }, hex2.radius - 3)) {

            update_values(&hex2);
        }

        if (CheckCollisionCircles((Vector2){ xcenter, ycenter }, radius - 3, (Vector2){ hex3.xcenter, hex3.ycenter }, hex3.radius - 3)) {

            update_values(&hex3);
        }
    }
};

MainHexagon mainHex;

void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update variables / Implement example logic at this point
   
    frameCounter++;
    float dt = GetFrameTime();
    Vector2 mouse_pos = GetMousePosition();

    mainHex.update();
    hex1.update(mouse_pos, dt);
    hex2.update(mouse_pos, dt);
    hex3.update(mouse_pos, dt);

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    // Render game screen to a texture, 
    // it could be useful for scaling or further shader postprocessing

    BeginTextureMode(target);
        ClearBackground(LIGHTGRAY);

        mainHex.draw();

        if (hex1.isClicked) {
            hex2.draw();
            hex3.draw();
            hex1.draw();
        }
        else if (hex2.isClicked) {
            hex1.draw();
            hex3.draw();
            hex2.draw();
        }
        else {
            hex1.draw();
            hex2.draw();
            hex3.draw();
        }
        
        // TODO: Draw your game screen here

        // DrawRectangle(70, 90, 200, 200, BLACK);
        // DrawRectangle(70 + 16, 90 + 16, 200 - 32, 200 - 32, RAYWHITE);
        // DrawText("raylib", 70 + 200 - MeasureText("raylib", 40) - 32, 90 + 200 - 40 - 24, 40, BLACK);

        // DrawText("6.x", 290, 90 - 26, 280, BLACK);
        // DrawText("GAMEJAM", 70, 90 + 210, 120, MAROON);

        // if ((frameCounter/20)%2) DrawText("are you ready?", 160, 500, 50, BLACK);
        
        // DrawRectangleLinesEx((Rectangle){ 0, 0, screenWidth, screenHeight }, 16, BLACK);

        //DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
        // float xcenter = 330;
        // float ycenter = 330;
        // DrawPolyLinesEx((Vector2){ xcenter, ycenter }, 6, 85, 0.0f, 6, BEIGE);
        // DrawLineEx((Vector2){ screenWidth/4.0f*3, 330 }, (Vector2){ screenWidth/4.0f*3+83, 330 }, 6, BEIGE);
        
    EndTextureMode();
    
    // Render to screen (main framebuffer)
    BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw render texture to screen, scaled if required
        DrawTexturePro(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height }, 
            (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height }, (Vector2){ 0, 0 }, 0.0f, WHITE);

        // TODO: Draw everything that requires to be drawn at this point, maybe UI?

    EndDrawing();
    //----------------------------------------------------------------------------------  
}
