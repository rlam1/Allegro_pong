#pragma once

#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include "status.h"

class Object
{
    public:
        Object(float X, float Y, int w, int h, 
            float accelerationX, float accelerationY,
            int status, std::string bitmapFileLoc);
            
        virtual ~Object();
    
        virtual void reset() {}
        virtual void update() {}
		virtual void draw();
        
        void getPos(float &x, float &y); //Sends to two variables
        void getSize(float &w, float &h);
        void getAccel(float &accelX, float &accelY);
        int  getStatus();
        
        void setPosition(float x, float y);
        void setAccel(float accelX, float accelY);
        void setStatus(int flag);
        
    private:
        float x, y;
        int   w, h;
        float accelX, accelY;
        int   status; //Bit field that holds status flags for object
        ALLEGRO_BITMAP *bitmap;
		
		ALLEGRO_BITMAP *create_memory_bitmap();
		void generate_error_bitmap();
		
		void setBit(int value);
		bool testBit(int value);
		void clearBit(int value);
};
