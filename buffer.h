#include <Arduino.h>

class Element
{
    public:
        unsigned long pos[2];
        boolean draw;
        Element *next;

        Element()
        {
            next = NULL;
        }
        Element(unsigned long l, unsigned long r, boolean d)
        {
            pos[0] = l;
            pos[1] = r;
            draw = d;
            next = NULL;
        }
        void repr()
        {
            Serial.print("Left Value: " + String(pos[0]) + " | Right Value: " + String(pos[1]));
            if (draw)
            {
                Serial.print(" Draw");
            }
            Serial.println();
        }
};

class Buffer
{
    public:
        Element *head;
        Element *tail;
        int length;

        Buffer()
        {
            head = NULL;
            tail = NULL;
            length = 0;
        }

        void add(unsigned long l, unsigned long r, boolean d) 
        {
            Element *temp = new Element;
            temp->pos[0] = l;
            temp->pos[1] = r;
            temp->draw = d;
            temp->next = NULL;

            if (head == NULL)
            {
                head = temp;
                tail = temp;
                length++;
            }
            else
            {
                tail->next = temp;
                tail = tail->next;
                length++;
            }
            

        }
        void add(unsigned long l, unsigned long r)
        {
            add(l,r,false);
        }
        Element* pop()
        {
            if (head == NULL)
            {
                Serial.println("List is empty!");
                return NULL;
            }
            else
            {
                Element *temp = head;
                head = head->next;
                length--;
                return temp;
            }
            
            
        }
        void show()
        {
            if (head == NULL)
            {
                Serial.println("List is empty!");
            }
            else
            {
                Element *temp = head;
                Serial.println("+++");
                while (temp!= NULL)
                {
                    temp->repr();
                    temp = temp->next;
                }
                Serial.println("+++");
            }
        }
        int len()
        {
            return length;
        }

};