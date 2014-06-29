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

    calcCenter();
    
    if(al_is_system_installed())
    {
        bitmap = al_load_bitmap(bitmapFileLoc.c_str());
        
        if(!bitmap)
        {
			setBit(ER_ERROR);
            generate_error_bitmap();
        }
    } else {
		setBit(ER_ERROR);
		setBit(ER_INVALID_STATE);
        bitmap = NULL;
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
		al_draw_bitmap(bitmap, center.x, center.y, 0);
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

Point Object::getCenter()
{
    return center;
}

ALLEGRO_BITMAP *Object::getBitmap()
{
    if (testBit(ER_INVALID_STATE))
    {
        return NULL;
    } else
    {
        return bitmap;
    }
}

void Object::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;

    calcCenter();
}

void Object::setAccel(float accelX, float accelY)
{
	this->accelX = accelX;
	this->accelY = accelY;
}

void Object::setStatus(int flag)
{
	setBit(flag);
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

    ALLEGRO_COLOR background = al_color_html("#3f51b5");
    ALLEGRO_COLOR shadow = al_color_html("#1a237e");
    ALLEGRO_COLOR sign = al_color_html("#ffeb3b");
	
	al_set_target_bitmap(bitmap);
    al_clear_to_color(background);

    // Shadow (3 triangles)
    al_draw_filled_triangle(w / 2.0, h / 4.0, w, (h * 3.0) / 4.0, w / 2.0, h, shadow);
    al_draw_filled_triangle(w, (h * 3.0) / 4.0, w, h, w / 2.0, h, shadow);
    al_draw_filled_triangle(w / 2.0, h / 4.0, w / 2.0, h, w / 4.0, (h * 3.0) / 4.0, shadow);
	
    // Alert sign triangle
	al_draw_filled_triangle(w / 2.0, h / 4.0, ((w * 3.0) / 4), ((h * 3.0) / 4.0), w / 4.0, ((h * 3.0) / 4.0), sign);
		
    // Exclamation point
	al_draw_filled_rectangle((w * 15.0) / 32.0, ((h * 14.0) / 32.0), ((w * 17.0) / 32.0), ((h * 19.0) / 32.0), background);
    al_draw_filled_rectangle((w * 15.0) / 32.0, (h * 5.0) / 8, (w * 17.0) / 32.0, (h * 11.0) / 16.0, background);
		
	al_set_target_backbuffer(al_get_current_display());
}

void Object::calcCenter()
{
    center.x = x - (w / 2.0);
    center.y = y - (h / 2.0);
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

void Object::clearBit(int value)
{
	status &= ~value;
}












