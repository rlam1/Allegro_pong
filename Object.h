#pragma once

#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

class Object
{
    public:
        Object(float X, float Y, int w, int h, 
            float accelerationX, float accelerationY,
            int status, std::string bitmapFileLoc);
            
        ~Object();
    
        virtual void reset();
        virtual void update();
        
        void getPos(float &x, float &y); //Sends to two variables
        void getsize(float &w, float &h);
        void getAccel(float &accelX, float &accelY);
        int  getStatus();
        
        void setPosition(float x, float y);
        void setAccel(float accelX, accelY);
        void setStatus(int flag);
        
    private:
        float x, y;
        int   w, h;
        float accelX, accelY;
        int   status; //Bit field that holds status flags for object
        ALLEGRO_BITMAP *bitmap;
};
