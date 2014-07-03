#pragma once

#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include "status.h"

template <typename T>
struct Point {
    T x, y;
};

enum Type {
    OBJECT,
    BALL,
    PADDLE0,
    PADDLE1
};

class Object
{
    public:
        Object(float X, float Y, int w, int h, 
            float accelerationX, float accelerationY,
            int status, std::string bitmapFileLoc);

        Object(float X, float Y, int w, int h,
            float accelerationX, float accelerationY,
            int status, float hitBoxFactor, std::string bitmapFileLoc);
            
        virtual ~Object();
    
        virtual void reset() {}
        virtual void update() {}
		void draw();
        
        Point<float> getPos();
        Point<float> getAccel();
        Point<float> getCenter();
        Point<int>  getSize();
        ALLEGRO_BITMAP *getBitmap();
        int getName();
        int   getStatus();
        
        void setPosition(float x, float y);
        void setAccel(float accelX, float accelY);
        void setStatus(int flag);

    protected:
        int name;
        float x, y;
        int   w, h;
        float accelX, accelY;
        Point<float> center;
        float hitboxFactor;     // Size of hitbox compared to bitmap
        int displayW, displayH;

        void calcCenter();
        void getDisplayData();

        void setBit(int value);
        bool testBit(int value);
        void clearBit(int value);
        
    private:
        int   status; //Bit field that holds status flags for object
        ALLEGRO_BITMAP *bitmap;
		
		ALLEGRO_BITMAP *create_memory_bitmap();
		void generate_error_bitmap();
};
