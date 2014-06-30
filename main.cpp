#include <iostream>

#include <allegro5/allegro5.h>
#include <allegro5/display.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include "Object.h"
#include "Ball.h"

const float FPS = 1.0 / 60.0;

int main(int argc, char **argv)
{
    al_init();
    
    al_init_font_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    
    int displayFlags = al_get_new_display_flags();
#ifdef _WIN32
    al_set_new_bitmap_flags(displayFlags | ALLEGRO_FULLSCREEN);
#else
    al_set_new_display_flags(displayFlags | ALLEGRO_FULLSCREEN_WINDOW);
#endif
    ALLEGRO_DISPLAY *display = al_create_display(1024, 600);
    Object iconObject(0, 0, 100, 100, 0, 0, 0, "This only hold the icon for the game, that is, the error image! :)");
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
	
	al_start_timer(timer);
	
	bool done = false;
	bool redraw = false;
	
	Ball obj1(512, 300, 50, 50, 2.0, 0, "Error Image loaded here!");
    obj1.reset();
	
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
                obj1.update();
				redraw = true;
				break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    done = true;
                }
                break;
            default:
                break;
		}
		
		if(al_is_event_queue_empty(queue) && redraw)
		{
            al_clear_to_color(al_color_html("#212121"));

			obj1.draw();
            al_flip_display();

			redraw = false;
		}
	}
    
    return EXIT_SUCCESS;
}

