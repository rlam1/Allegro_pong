#include "Object.h"

Object::Object(float X, float Y, int w, int h,
            float accelerationX, float accelerationY,
            int status, std::string bitmapFileLoc)
{
    x = X;
    y = Y;
    this->w = w;
    this->h = h;
    accelX = accelerationX;
    accelY = accelerationY;
    this->status = status;
    
    if(al_is_system_installed())
    {
        bitmap = al_load_bitmap(bitmapFileLoc.c_str());
        
        if(!bitmap)
        {
            bitmap = al_create_bitmap(w, h);
            
            al_set_target_bitmap(bitmap);
            al_clear_to_color(al_color_html("#e51c23")); // Nice red
            
            al_draw_filled_triangle(w / 2.0, h / 4.0, /* p1(x,y) */
                ((w * 3.0) / 4), ((h * 3.0) / 4.0),   /* p2(x,y) */
                w / 4.0, ((h * 3.0) / 4.0),           /* p3(x,y) */
                al_color_html("#ffeb3b"));
        }
    }
}
