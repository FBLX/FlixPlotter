#include <Arduino.h>

class Element
{
    public:
        unsigned long pos[2];
        boolean draw;
        Element *next;

        Element();
        Element(unsigned long l, unsigned long r, boolean d);
        ~Element();
        void repr();
};

class Buffer
{
    public:
        Element *head;
        Element *tail;
        int length;

        Buffer();
        void add(unsigned long l, unsigned long r, boolean d);
        void add(unsigned long l, unsigned long r);
        Element* pop();
        void show();
        int len();

};