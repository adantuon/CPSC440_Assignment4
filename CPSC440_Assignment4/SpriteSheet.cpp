//Aiden D'Antuono

#include "SpriteSheet.h"

Sprite::Sprite() {
	image = NULL;
}

Sprite::~Sprite() {
	al_destroy_bitmap(image);
}

void Sprite::InitSprites() {
	x = 176;
	y = 0;

	maxFrame = 14;
	curFrame = 5;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 48;
	animationColumns = 5;
	direction = 1;
	speed = 8;

	image = al_load_bitmap("SpriteSheet.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
}

bool Sprite::UpdateSprites(int dir) {
	
	bool exited = false;
	int oldx = x;
	int oldy = y;

	//Movement Up
	if (dir == 0) {
		if (direction != 0) {
			direction = 0;
			curFrame = 11;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 14)
				curFrame = 11;
		}

		y -= speed;
	}
	//Movement Down
	else if (dir == 1) {
		if (direction != 1) {
			direction = 1;
			curFrame = 6;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 9)
				curFrame = 6;
		}

		y += speed;
	}
	//Movement Left
	else if (dir == 2) {
		if (direction != 2) {
			direction = 2;
			curFrame = 1;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 4)
				curFrame = 1;
		}

		x -= speed;
	}
	//Movement Right
	else if (dir == 3) {
		if (direction != 3) {
			direction = 3;
			curFrame = 1;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 4)
				curFrame = 1;
		}

		x += speed;
	}
	//If stopped
	else {
		//reset frameCount
		frameCount = 0;
		//set correct stopped frame
		if (direction == 0) {
			curFrame = 10;
		}
		else if (direction == 1) {
			curFrame = 5;
		}
		else if (direction == 2 || direction == 3) {
			curFrame = 0;
		}
	}

	//Map Edge Collision
	//Top edge has no exits
	if (y <= 0) {
		x = oldx;
		y = oldy;
	}
	//potential exit edges
	else if (x <= 0 || x >= 2560 - frameWidth || y >= 2560 - frameHeight) {
		x = oldx;
		y = oldy;
		exited = true;
	}

	//Collision Detection
	if (collided(x, y) || collided(x + frameWidth, y + frameHeight) || collided(x + frameWidth, y) || collided (x, y + frameHeight)) {
		x = oldx;
		y = oldy;
	}

	return exited;
}

void Sprite::DrawSprites(int xoffset, int yoffset) {
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	if (direction == 3) {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}
	else {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
}