#include "./sprite.hpp"
#include "./items.hpp"

#define ITEM_1 128

Item::Item(byte _item_id, byte _x, byte _y) : Sprite(_item_id, _x, _y)
{
}

void Item::render()
{
    Sprite::render();
}

Item *spawn_item(byte x, byte y, byte key)
{
    if (key < ITEM_1)
    {
        return new Item(17, x, y);
    }
    else
    {
        return nullptr;
    }
}