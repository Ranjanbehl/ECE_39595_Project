#include "CreatureAction.hpp"
#include "Creature.hpp"

CreatureAction::CreatureAction(Creature* creatureOwner,std::string creatureName,std::string creatureType): owner(creatureOwner), Action(creatureName,creatureType) {
   
}