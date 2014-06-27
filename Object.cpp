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
			setBit(ERROR);
            generate_error_bitmap();
        }
    } else {
		setBit(ERROR);
		setBit(ER_INVALID_STATE);
		bitmap = std::nullptr;
	}
}

Object::~Object()
{
	al_destroy_bitmap(bitmap);
}

void Object::draw()
{
	if(testBit(ER_INVALID_STATE))
	{
		return;
	} else {
		al_draw_bitmap(bitmap, x - (w / 2.0), y - (h / 2.0), 0);
	}
}

void Object::getPos(float &x, float &y)
{
	x = this->x;
	y = this->y;
}

void Object::getSize(float &w, float &h)
{
	w = this->w;
	h = this->h;
}

void Object::getAccel(float &accelX, float &accelY)
{
	accelX = this->accelX;
	accelY = this->accelY;
}

int Object::getStatus()
{
	return status;
}

void Object::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Object::setAccel(float accelX, accelY)
{
	this->accelX = accelX;
	this->accelY = accelY;
}

void Object::setStatus(int flag)
{
	setBit(flags);
}

ALLEGRO_BITMAP *Object::create_memory_bitmap()
{
	setBit(ER_BITMAP);
	setBit(ISMEM_BITMAP);
	
    int flags = al_get_new_bitmap_flags();
    al_set_new_bitmap_flags(flags | ALLEGRO_MEMORY_BITMAP);
	
	ALLEGRO_BITMAP *bmp;
    bmp = al_create_bitmap(w, h);
	
    al_set_new_bitmap_flags(flags);
	
    return bmp;
}

void Object::generate_error_bitmap()
{
	if(testBit(ISMEM_BITMAP))
	{
		bitmap = create_memory_bitmap();
	} else {
		bitmap = al_create_bitmap(w, h);
	}
	
	al_set_target_bitmap(bitmap);
	al_clear_to_color(al_color_html("#e51c23")); // Nice red
	
	al_draw_filled_triangle(w / 2.0, h / 4.0, /* p1(x,y) */
		((w * 3.0) / 4), ((h * 3.0) / 4.0),   /* p2(x,y) */
		w / 4.0, ((h * 3.0) / 4.0),           /* p3(x,y) */
		al_color_html("#ffeb3b"));
		
	al_draw_filled_rectangle((w * 15.0) / 32.0, ((h * 14.0) / 32.0),
		((w * 17.0) / 32.0), ((h * 19.0) / 32.0),
		al_color_html("#e51c23"));
		
	al_draw_filled_circle((w * 16.0) / 32.0, (h * 21.0) / 32.0,
		1/32.0, al_color_html("e51c23"));
		
	al_set_target_backbuffer(al_get_current_display());
}

void Object::setBit(int value)
{
	status |= value;
}

bool Object::testBit(int value)
{
	if( (status & value) != 0)
	{
		return true;
	} else {
		return false;
	}
}

void clearBit(int value)
{
	status &= ~value;
}












