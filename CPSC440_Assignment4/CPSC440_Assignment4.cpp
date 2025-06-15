//Aiden D'Antuono

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "mappy_A5.h"

int main() {
	const int WIDTH = 900;
	const int HEIGHT = 900;
	bool keys[] = { false, false, false, false };
	enum KEYS{UP, DOWN, LEFT, RIGHT};

	bool exit = false;
	bool render = false;



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

	int xOff = 0;
	int yOff = 0;
	char mapName[12] = "Maze1.FMP";

	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));

	al_start_timer(timer);

	while (!exit) {

		ALLEGRO_EVENT event;
		al_wait_for_event(eventQueue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {

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

		if (render && al_is_event_queue_empty(eventQueue)) {
			render = false;
		}
	}

	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);

	return 0;
}
