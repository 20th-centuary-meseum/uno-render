#ifndef ITEMS_H
#define ITEMS_H

#define MAX_ITEM_NUM 5
#include "./sprite.hpp"

class Item : public Sprite
{
public:
    Item(byte _item_id, byte _x, byte _y);
    void render();
};

class Items
{
public:
    Items();
    Item *items[MAX_ITEM_NUM];
    byte item_cnt;
    void add_item(byte x, byte y);
    void render();
};

Item *spawn_item(byte key, byte x, byte y);

#endif ITEMS_H