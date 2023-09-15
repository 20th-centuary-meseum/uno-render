#include "./sprite.hpp"
#include "./items.hpp"
#include "./decode_img.hpp"
#include "../utils/utils.hpp"

#define ITEM_1 128

Item::Item(byte _item_id, byte _x, byte _y) : Sprite(_item_id, _x, _y)
{
    face_id <<= 2;
}

void Item::render()
{
    DecodeItem(face_id, x, y);
}

Items::Items() : items{
                     0,
                 }
{
    item_cnt = 0;
}

Item *Items::operator[](byte i)
{
    return items[i];
}

void Items::add_item(byte x, byte y)
{
    if (item_cnt >= MAX_ITEM_NUM - 1)
        return;

    Item *new_item = nullptr;
    if (Rand::get() < ITEM_1)
    {
        new_item = new Item(0, x * TILE_SIZE, y * TILE_SIZE);
    }

    if (new_item == nullptr)
        return;

    items[item_cnt] = new_item;
    item_cnt++;
}

void Items::delete_item(byte idx)
{
    delete items[idx];
    items[idx] = nullptr;
}

void Items::render()
{
    for (byte i = 0; i < 5; i++)
    {
        if (items[i])
            items[i]->render();
    }
}