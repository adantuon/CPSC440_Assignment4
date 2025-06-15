//Aiden D'Antuono

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Sprite {
	public:
		Sprite();
		~Sprite();
		void InitSprites();
		void UpdateSprites(int dir); //dir 0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT
		void DrawSprites(int xoffset, int yoffset);
		float getX() { return x; }
		float getY() { return y; }
		int getWidth() { return frameWidth; }
		int getHeight() { return frameHeight; }

	private:
		float x;
		float y;
		int maxFrame;
		int curFrame;
		int frameCount;
		int frameDelay;
		int frameWidth;
		int frameHeight;
		int animationColumns;
		int direction;

		ALLEGRO_BITMAP *image;
};