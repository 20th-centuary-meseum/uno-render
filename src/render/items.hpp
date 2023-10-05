#ifndef ITEMS_H
#define ITEMS_H

#define MAX_ITEM_NUM 5
#include "./sprite.hpp"

class Character;

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
    Item *operator[](byte i);
    Item *items[MAX_ITEM_NUM];
    byte item_cnt;
    void add_item(byte x, byte y);
    void delete_item(byte idx);
    void render();
};

Item *spawn_item(byte key, byte x, byte y);

#endif