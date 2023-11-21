#include "./sprite.hpp"
#include "./items.hpp"
#include "./character.hpp"
#include "./decode_img.hpp"
#include "../utils/utils.hpp"

Items::Items() : item_map{
                     0,
                 }
{
}

void Items::add_item(byte x, byte y)
{
    byte seed = Rand::get();
    // 0 ~ 256

    if (seed < 50)
        item_map[x + (y - 1) * 8] = ITEM_HEAL;
    else if (seed < 100)
        item_map[x + (y - 1) * 8] = ITEM_SHLD;
    else if (seed < 150)
        item_map[x + (y - 1) * 8] = ITEM_DASH;
    else if (seed < 200)
        item_map[x + (y - 1) * 8] = ITEM_SPED;
    else if (seed < 250)
        item_map[x + (y - 1) * 8] = ITEM_DAMG;
}

void Items::delete_item(byte x, byte y)
{
    item_map[x / TILE_SIZE + (y / TILE_SIZE - 1) * 8] = 0;
}

byte Items::at(byte x, byte y)
{
    return item_map[x / TILE_SIZE + (y / TILE_SIZE - 1) * 8];
}

void Items::render()
{
    for (byte y = 0; y < 5; y++)
    {
        for (byte x = 0; x < 8; x++)
        {
            if (item_map[x + y * 8])
                DecodeItem(item_map[x + y * 8], x * 16, (y + 1) * 16);
        }
    }
}