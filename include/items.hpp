#pragma once
#include <raylib.h>

enum class ItemType {AMMO, HEALTH};

class DropItem {
    public:
        DropItem(Vector2 Position, ItemType Type, int Ammount);
        
        Rectangle getRectangle();
        void draw();

        ItemType getType();
        int getAmmount();
        bool isActive();
        void itemDestroy();
    private:
        Vector2 position;
        ItemType type;
        int ammount;
        float size;
        Rectangle hitbox;
        bool active;
};