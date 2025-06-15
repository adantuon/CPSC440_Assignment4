//Aiden D'Antuono

#include "SpriteSheet.h"

Sprite::Sprite() {
	image = NULL;
}

Sprite::~Sprite() {
	al_destroy_bitmap(image);
}

void Sprite::InitSprites() {
	x = 192;
	y = 64;

	maxFrame = 14;
	curFrame = 5;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 48;
	animationColumns = 5;
	direction = 1;

	image = al_load_bitmap("SpriteSheet.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
}

void Sprite::UpdateSprites(int dir) {

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