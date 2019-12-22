#include "buffer.h"

Element::Element()
{
    next = NULL;
}
Element::Element(unsigned long l, unsigned long r, boolean d)
{
    pos[0] = l;
    pos[1] = r;
    draw = d;
    next = NULL;
}
Element::~Element()
{
    // Serial.println("Element deleted");
}
void Element::repr()
{
    Serial.print("Left Value: " + String(pos[0]) + " | Right Value: " + String(pos[1]));
    if (draw)
    {
        Serial.print(" Draw");
    }
    Serial.println();
}


Buffer::Buffer()
{
    head = NULL;
    tail = NULL;
    length = 0;
}

void Buffer::add(unsigned long l, unsigned long r, boolean d) 
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
void Buffer::add(unsigned long l, unsigned long r)
        {
            add(l,r,false);
        }
Element* Buffer::pop()
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
void Buffer::show()
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
int Buffer::len()
{
    return length;
}
