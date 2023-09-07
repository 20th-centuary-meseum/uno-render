#include "./sprite.hpp"
#include "./items.hpp"
#include "./decode_img.hpp"

#define ITEM_1 128

Item::Item(byte _item_id, byte _x, byte _y) : Sprite(_item_id, _x, _y)
{
    face_id <<= 2;
}

void Item::render()
{
    DecodeItem(face_id, x, y);
}

Item *spawn_item(byte key, byte x, byte y)
{
    if (key < ITEM_1)
    {
        return new Item(2, x * TILE_SIZE, y * TILE_SIZE);
    }
    else
    {
        return nullptr;
    }
}