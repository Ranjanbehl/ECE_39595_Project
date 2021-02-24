#include "Player.hpp"

Player::Player(){
    //set inital Score to ZERO
    this->score = 0;
    this->moves = 0;
    this->hallucinateTerm = 0;
}

void Player::setID(int room, int serial) {
    this->Id = serial;
    this->roomId = room;
}

int Player::getScore(){
    return this->score;
}

void Player::setScore(){
    (this->score)++;
}

bool Player::countMoves(){
    (this->moves)++;
    if (moves >= this->getHpMoves()){
        (this->hitPoint)++;
        this->moves = 0;
        return true;
    }
    return false;
}

void Player::setHallucinate(int term) {
    this->hallucinateTerm = term;
}

bool Player::getHallucinateTerms() {
    if (hallucinateTerm > 0){
        hallucinateTerm--;
        if(hallucinateTerm == 0){
            return true;
        }
        return true;
    }
    return false;
}

int Player::getHallucinateCounter(){
    return hallucinateTerm;
}