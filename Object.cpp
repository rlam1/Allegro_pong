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
    this->hitboxFactor = 2.0f;
    name = OBJECT;

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

Object::Object(float X, float Y, int w, int h,
    float accelerationX, float accelerationY,
    int status, float hitBoxFactor, std::string bitmapFileLoc)
{
    x = X;
    y = Y;
    this->w = w;
    this->h = h;
    accelX = accelerationX;
    accelY = accelerationY;
    this->status = status;
    this->hitboxFactor = hitBoxFactor;
    name = OBJECT;

    calcCenter();

    if (al_is_system_installed())
    {
        bitmap = al_load_bitmap(bitmapFileLoc.c_str());

        if (!bitmap)
        {
            setBit(ER_ERROR);
            generate_error_bitmap();
        }
    } else
    {
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
	} else 
    {
        al_draw_bitmap(bitmap, center.x, center.y, 0);
	}

    if (testBit(DRAW_HITBOX))
    {
        al_draw_rectangle(
            x - w / hitboxFactor, y - h / hitboxFactor,
            x + w / hitboxFactor, y + h / hitboxFactor,
            al_map_rgb(255, 0, 0), 0);
    }
}

Point<float> Object::getPos()
{
    Point<float> position;
    position.x = x;
    position.y = y;

    return position;
}

Point<int> Object::getSize()
{
    Point<int> size;
    size.x = w;
    size.y = h;

    return size;
}

Point<float> Object::getAccel()
{
    Point<float> accelerationVector;
    accelerationVector.x = accelX;
    accelerationVector.y = accelY;

    return accelerationVector;
}

int Object::getName()
{
    return name;
}

int Object::getStatus()
{
	return status;
}

float Object::getHitboxFactor()
{
    return hitboxFactor;
}

Point<float> Object::getCenter()
{
    calcCenter();

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

void Object::reverseAcceleration()
{
    accelX *= -1;
    accelY *= -1;
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
    al_draw_filled_triangle(w / 2.0f, h / 4.0f, w, (h * 3.0f) / 4.0f, w / 2.0f, h, shadow);
    al_draw_filled_triangle(w, (h * 3.0f) / 4.0f, w, h, w / 2.0f, h, shadow);
    al_draw_filled_triangle(w / 2.0f, h / 4.0f, w / 2.0f, h, w / 4.0f, (h * 3.0f) / 4.0f, shadow);
	
    // Alert sign triangle
	al_draw_filled_triangle(w / 2.0f, h / 4.0f, ((w * 3.0f) / 4), ((h * 3.0f) / 4.0f), w / 4.0f, ((h * 3.0f) / 4.0f), sign);
		
    // Exclamation point
	al_draw_filled_rectangle((w * 15.0f) / 32.0f, ((h * 14.0f) / 32.0f), ((w * 17.0f) / 32.0f), ((h * 19.0f) / 32.0f), background);
    al_draw_filled_rectangle((w * 15.0f) / 32.0f, (h * 5.0f) / 8.0f, (w * 17.0f) / 32.0f, (h * 11.0f) / 16.0f, background);
		
	al_set_target_backbuffer(al_get_current_display());
}

void Object::calcCenter()
{
    center.x = x - (w / 2.0f);
    center.y = y - (h / 2.0f);
}

void Object::getDisplayData()
{
    ALLEGRO_DISPLAY *display = al_get_current_display();

    displayW = al_get_display_width(display);
    displayH = al_get_display_height(display);
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












