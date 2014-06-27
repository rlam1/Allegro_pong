#include <iostream>

#include <allegro5/allegro5.h>
#include <allegro5/display.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

int main(int argc, char **argv)
{
    al_init();
    
    al_init_font_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    
    int displayFlags = al_get_new_display_flags();
    al_set_new_display_flags(displayFlags | ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY *display = al_create_display(1024, 600);
    al_clear_to_color(al_map_rgb(13, 13, 13));
    al_flip_display();
    
    ALLEGRO_FONT *sysFont = al_create_builtin_font();
    ALLEGRO_TIMER *timer = al_create_timer(1 / 60.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    
    return EXIT_SUCCESS;
}

