#include "items.hpp"
#include <string>

DropItem::DropItem(Vector2 Position, ItemType Type, int Ammount) {
    position = Position;
    type = Type;
    ammount = Ammount;
    size = 30;
    
    hitbox = {position.x, position.y, size, (size - 10)};
    active = true;
}
Rectangle DropItem::getRectangle() {
    return hitbox;
}
void DropItem::draw() {
    if(!active) {
        return ;
    }
    if(type == ItemType::AMMO) {
        DrawRectangleRec( hitbox, DARKGREEN);
        std::string text = std::to_string(ammount);

        DrawText(text.c_str(), position.x , position.y , 15, WHITE);
    } else {
        DrawRectangleRec( hitbox, RED);
        std::string text = std::to_string(ammount);

        DrawText(text.c_str(), position.x , position.y , 15, WHITE);
    }
}
ItemType DropItem::getType() {
    return type;
}
int DropItem::getAmmount() {
    return ammount;
}
void DropItem::itemDestroy() {
    active = false;
}
bool DropItem::isActive() {
    return active;
}
