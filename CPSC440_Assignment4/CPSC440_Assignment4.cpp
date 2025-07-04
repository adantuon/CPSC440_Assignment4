//Aiden D'Antuono

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"

int collided(int x, int y);

int main() {
	const int WIDTH = 900;
	const int HEIGHT = 900;
	bool keys[] = { false, false, false, false };
	bool exited = false;
	int mazeNum = 0;
	enum KEYS{UP, DOWN, LEFT, RIGHT};

	bool exit = false;
	bool render = false;
	Sprite player;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_TIMER *timer;

	//program init
	if (!al_init()) {
		return -1;
	}
		
	display = al_create_display(WIDTH, HEIGHT);

	if (!display) {
		return -1;
	}

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_font("PressStart2P.ttf", 48, 0);
	ALLEGRO_FONT *smallFont = al_load_font("PressStart2P.ttf", 16, 0);

	player.InitSprites();

	int xOff = 0;
	int yOff = 0;
	char mapName[12] = "Maze0.FMP";
	if (MapLoad(mapName, 1)) {
		return -5;
	}

	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));

	al_start_timer(timer);
	int mazeTimer = 3600;

	//draw the background tiles
	MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);

	//draw foreground tiles
	MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
	player.DrawSprites(0, 0);

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	while (!exit) {

		ALLEGRO_EVENT event;
		al_wait_for_event(eventQueue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			render = true;
			if (keys[UP]) {
				exited = player.UpdateSprites(UP);
			}
			else if (keys[DOWN]) {
				exited = player.UpdateSprites(DOWN);
			}
			else if (keys[LEFT]) {
				exited = player.UpdateSprites(LEFT);
			}
			else if (keys[RIGHT]) {
				exited = player.UpdateSprites(RIGHT);
			}
			else {
				exited = player.UpdateSprites(-1);
			}
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				exit = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				exit = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			}
		}


		//If the player has reached the end of the current maze
		if (exited) {
			exited = false;

			mazeNum++;
			mazeTimer = 3600;

			//If more mazes to complete
			if (mazeNum < 3) {
				player.setX(176);
				player.setY(0);

				sprintf_s(mapName, "Maze%i.FMP", mazeNum);

				if (MapLoad(mapName, 1)) {
					return -5;
				}
			}
			//If finished all mazes
			else {
				al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 100, ALLEGRO_ALIGN_CENTER, "Congratulations");
				al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "You Escaped the");
				al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTER, "Hedge Mazes!");

				al_flip_display();

				//Freeze game for 5 seconds and then exit
				time_t startTime = time(NULL);
				time_t currTime = time(NULL);
				while (currTime - startTime < 5) {
					currTime = time(NULL);
				}
				exit = true;
				render = false;
			}
		}

		//If ran out of time
		if (mazeTimer == 0) {
			al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 150, ALLEGRO_ALIGN_CENTER, "Game Over");
			al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 50, ALLEGRO_ALIGN_CENTER, "You Failed");
			al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 50, ALLEGRO_ALIGN_CENTER, "to Escape the");
			al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 150, ALLEGRO_ALIGN_CENTER, "Hedge Mazes!");

			al_flip_display();

			//Freeze game for 5 seconds and then exit
			time_t startTime = time(NULL);
			time_t currTime = time(NULL);
			while (currTime - startTime < 5) {
				currTime = time(NULL);
			}
			exit = true;
			render = false;
		}

		if (render && al_is_event_queue_empty(eventQueue)) {
			render = false;

			xOff = player.getX() + player.getWidth() - WIDTH / 2;
			yOff = player.getY() + player.getHeight() - HEIGHT / 2;

			//avoid moving beyond the map edge
			if (xOff < 0) xOff = 0;

			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0)
				yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT))
				yOff = mapheight * mapblockheight - HEIGHT;

			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			player.DrawSprites(xOff, yOff);

			al_draw_textf(smallFont, al_map_rgb(255, 255, 255), 10, HEIGHT - 20, ALLEGRO_ALIGN_LEFT, "Time Left: %.1f", mazeTimer / 60.0);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		mazeTimer--;
	}

	MapFreeMem();
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);

	return 0;
}

int collided(int x, int y) {
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	return blockdata->tl;
}
