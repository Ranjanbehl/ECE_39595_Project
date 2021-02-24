#include "ItemAction.hpp"

ItemAction::ItemAction(Item* itemOwner,std::string itemName,std::string itemType): owner(itemOwner), Action(itemName,itemType) {
}