#ifndef ITEMS_H
#define ITEMS_H

#include "./sprite.hpp"

class Item : public Sprite
{
public:
    Item(byte _item_id, byte _x, byte _y);
    void render();
};

Item *spawn_item(byte key, byte x, byte y);

#endif ITEMS_H