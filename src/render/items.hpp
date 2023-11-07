#ifndef ITEMS_H
#define ITEMS_H

class Items
{
public:
    byte item_map[40];

    Items();
    byte at(byte x, byte y);
    void add_item(byte x, byte y);
    void delete_item(byte x, byte y);
    void render();
};

#endif