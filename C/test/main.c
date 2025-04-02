#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>

static float r = 50;
static float g = 98.1;
static int winH = 640;
static int winW = 800;


int main(){
	Vector2 pos,v, a;
	pos = (Vector2){100,100};
	v = (Vector2){0,0};
	a = (Vector2){0,0};
	InitWindow(winW,winH,"BIRD");
	while(!WindowShouldClose()){
		float dt = GetFrameTime();
		if(IsKeyDown(KEY_D)) a = (Vector2){g,0};
		if(IsKeyDown(KEY_A)) a = (Vector2){-g,0};
		if(IsKeyDown(KEY_S)) a = (Vector2){0,g};
		if(IsKeyDown(KEY_W)) a = (Vector2){0,-g};
		if(IsKeyDown(KEY_SPACE)) a = (Vector2){0,0};
		v.x += a.x * dt;
		v.y += a.y * dt;
		if(pos.y < r ){v.y *= -0.10; pos.y = r;}
		if(pos.y > winH-r ){v.y *= -0.10; pos.y = winH-r;}
		if(pos.x < r ){v.x *= -0.10; pos.x = r;}
		if(pos.x > winW-r ){v.x *= -0.10; pos.x = winW-r;}
		pos.x += v.x * dt;
		pos.y += v.y * dt;
		
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawCircleV(pos, r, DARKGREEN);
		EndDrawing();
	}

}
