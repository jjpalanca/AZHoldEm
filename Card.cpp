/*
 * Card.cpp
 * Programmer: Jessmer John Palanca
 * This class creates an object of a card. It instantiates
 * the Rank and Suit of a particular card.
 */
#ifndef CARD_CPP
#define CARD_CPP

#include <string>

using namespace std;
// Model the Suit of a Poker Card
enum class Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
};
enum class Rank {
    DEUCE = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};

class Card {
private:
    Suit suit;
    Rank rank;
public:
    Card(Rank _rank, Suit _suit) {
        this->suit = _suit;
        this->rank = _rank;
    }

    Suit getSuit() const {
        return suit;
    }

    Rank getRank() const {
        return rank;
    }

    int getValue() const {
        return int(rank);
    }

    string toString() {

        string value;
        string const Club = "\u2663";//"\xe2\x99\xa3";
        string const Diamond = "\u2666";//"\xe2\x99\xa6";
        string const Heart = "\u2665";//"\xe2\x99\xa5";
        string const Spade = "\u2660";//"\xe2\x99\xa0";

        if (this->getValue() <= 10) {
            value = to_string(this->getValue());
        } else {
            if (this->getValue() == 11) {
                value = "J";
            } else if (this->getValue() == 12) {
                value = "Q";
            } else if (this->getValue() == 13) {
                value = "K";
            } else if (this->getValue() == 14) {
                value = "A";
            }
        }

        if (suit == Suit::CLUBS) {
            return value + Club;
        } else if (suit == Suit::DIAMONDS) {
            return value + Diamond;
        } else if (suit == Suit::HEARTS) {
            return value + Heart;
        } else if (suit == Suit::SPADES) {
            return value + Spade;
        }
    }

    bool operator==(const Card &newCard) {
        return this->getValue() == newCard.getValue();
    }

    bool operator>(const Card &newCard) {
        return this->getValue() > newCard.getValue();
    }

    bool operator<(const Card &newCard) {
        return this->getValue() < newCard.getValue();
    }

};

#endif