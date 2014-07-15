#include <iostream>
#include <vector>

#include <allegro5/allegro5.h>
#include <allegro5/display.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include "Game.h"

const float FPS = 1.0f / 60.0f;
Point<int> screenSize;

int main(int argc, char **argv)
{
    al_init();
    
    al_init_font_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    
    screenSize.x = 1024;
    screenSize.y = 600;
    int displayFlags = al_get_new_display_flags();
#ifdef _WIN32
    al_set_new_bitmap_flags(displayFlags | ALLEGRO_FULLSCREEN);
#else
    al_set_new_display_flags(displayFlags | ALLEGRO_FULLSCREEN_WINDOW);
#endif
    ALLEGRO_DISPLAY *display = al_create_display(screenSize.x, screenSize.y);
    Object iconObject(0, 0, 100, 100, 0, 0, 0, "PATH");
    al_set_window_title(display, "Pong Clone");
    al_set_display_icon(display, iconObject.getBitmap());
    al_clear_to_color(al_map_rgb(13, 13, 13));
    al_flip_display();
    
    ALLEGRO_FONT *sysFont = al_create_builtin_font();
    ALLEGRO_TIMER *timer = al_create_timer(FPS);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
	
	al_start_timer(timer);
	
	bool done = false;
	bool redraw = false;

    Game game;
    game.addObject(new Ball(512, 300, 50, 50, 8.0f, DRAW_HITBOX, "PATH"));
    game.addObject(new Paddle(10, 12, 10, 150, DRAW_HITBOX, PADDLE0, "PATH"));
    game.addObject(new Paddle(screenSize.x - 10, 12, 10, 150, DRAW_HITBOX, PADDLE1, "PATH"));
    game.init();

#ifdef _DEBUG
    std::cout << "Size of Object: " << sizeof(Object) << " bytes" << std::endl
        << "Size of Paddle:  " << sizeof(Paddle) << " bytes" << std::endl
        << "Size of Ball:    " << sizeof(Ball) << " bytes" << std::endl
        << "Size of Game:    " << sizeof(Game) << " bytes" << std::endl;
#endif

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);
		
		switch(ev.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
			case ALLEGRO_EVENT_TIMER:
                game.update();
				redraw = true;
				break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    done = true;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
                al_grab_mouse(display);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (ev.mouse.button == 2)   // Right Mouse button
                {
                    al_ungrab_mouse();
                }
                break;
            default:
                break;
		}
		
		if(al_is_event_queue_empty(queue) && redraw)
		{
            al_clear_to_color(al_color_html("#000000"));

            game.draw();
            al_flip_display();

			redraw = false;
		}
	}

    al_destroy_display(display);
    al_destroy_font(sysFont);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    return EXIT_SUCCESS;
}

