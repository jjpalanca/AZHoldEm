/*
 * PokerHand.hpp
 * Programmer: Jessmer John Palanca
 * Description: This class creates an object of a pokerhand.
 *              It instantiates a vector of a sorted poker hand (Phand),
 *              the besthand of the pokerhand, a vector of Highcard that
 *              stores the high cards of the pokerhand in a descending order
 *              i.e. {K, J, 9, 8, 4}, and a string that stores the name of the
 *              best hand.
 */

#ifndef POKERHAND_HPP_
#define POKERHAND_HPP_

#include <vector>
#include <algorithm>
#include <iostream>
#include "52Cards.hpp"

using namespace std;

enum class HandRank {
    HIGHCARD = 1, ONEPAIR = 2, TWOPAIR = 3, THREEOFAKIND = 4, STRAIGHT = 5, FLUSH = 6,
    FULLHOUSE = 7, FOUROFAKIND = 8, STRAIGHTFLUSH = 9, ROYALFLUSH = 10
};

class PokerHand {
private:
    vector<Card> PHand;
    HandRank BestHand;
    vector<int> HighCard;
    string BestRank;
public:
    PokerHand(Card A, Card B, Card C, Card D, Card E) {
        PHand.push_back(A);
        PHand.push_back(B);
        PHand.push_back(C);
        PHand.push_back(D);
        PHand.push_back(E);
        std::sort(PHand.begin(), PHand.end());
        processBestHand();
    }

    void processBestHand() {
        if (RoyalFlush()) {
            BestHand = HandRank::ROYALFLUSH;
            BestRank = "Royal Flush";
            getHighCard("RoyalFlush");
        } else if (StraightFlush()) {
            BestHand = HandRank::STRAIGHTFLUSH;
            BestRank = "Straight Flush";
            getHighCard("StraightFlush");
        } else if (FourOfAKind()) {
            BestHand = HandRank::FOUROFAKIND;
            BestRank = "Four of a Kind";
            getHighCard("FourOfAKind");
        } else if (FullHouse()) {
            BestHand = HandRank::FULLHOUSE;
            BestRank = "Full House";
            getHighCard("FullHouse");
        } else if (Flush()) {
            BestHand = HandRank::FLUSH;
            BestRank = "Flush";
            getHighCard("Flush");
        } else if (Straight()) {
            BestHand = HandRank::STRAIGHT;
            BestRank = "Straight";
            getHighCard("Straight");
        } else if (ThreeOfAKind()) {
            BestHand = HandRank::THREEOFAKIND;
            BestRank = "Three of a Kind";
            getHighCard("ThreeOfAKind");
        } else if (TwoPair()) {
            BestHand = HandRank::TWOPAIR;
            BestRank = "Two Pair";
            getHighCard("TwoPair");
        } else if (OnePair()) {
            BestHand = HandRank::ONEPAIR;
            BestRank = "One Pair";
            getHighCard("OnePair");
        } else {
            BestHand = HandRank::HIGHCARD;
            BestRank = "HighCard";
            getHighCard("HighCard");
        }
    }

    vector<Card> getSortedCard() const {
        return PHand;
    }

    void getHighCard(string str) {
        if (str == "RoyalFlush") {
            HighCard.push_back(14);
        } else if (str == "StraightFlush" or str == "Straight") {
            if (this->PHand[0].getValue() == 2 and this->PHand[PHand.size() - 1].getValue() == 14) {
                HighCard.push_back(5);
            } else {
                HighCard.push_back(PHand[PHand.size() - 1].getValue());
            }
        } else if (str == "FourOfAKind") {
            if (PHand[0].getValue() < PHand[1].getValue()) {
                HighCard.push_back(PHand[1].getValue());
                HighCard.push_back(PHand[0].getValue());
            } else if (PHand[3].getValue() < PHand[4].getValue()) {
                HighCard.push_back(PHand[3].getValue());
                HighCard.push_back(PHand[4].getValue());
            }
        } else if (str == "FullHouse") {
            if (PHand[2].getValue() < PHand[3].getValue()) {
                HighCard.push_back(PHand[2].getValue());
                HighCard.push_back(PHand[3].getValue());
            } else if (PHand[2].getValue() == PHand[3].getValue()) {
                HighCard.push_back(PHand[2].getValue());
                HighCard.push_back(PHand[1].getValue());
            }
        } else if (str == "Flush" or str == "HighCard") {
            for (auto i = 4; i >= 0; i--) {
                HighCard.push_back(PHand[i].getValue());
            }
        } else if (str == "ThreeOfAKind") {
            if (PHand[0].getValue() == PHand[1].getValue()) {    // 2 2 2 3 4
                HighCard.push_back(PHand[0].getValue());
                HighCard.push_back(PHand[4].getValue());
                HighCard.push_back(PHand[3].getValue());
            } else if (PHand[0].getValue() < PHand[1].getValue()) {
                if (PHand[1].getValue() == PHand[2].getValue()) {     // 2 3 3 3 4
                    HighCard.push_back(PHand[1].getValue());
                    HighCard.push_back(PHand[4].getValue());
                    HighCard.push_back(PHand[0].getValue());
                } else {                                               // 2 3 4 4 4
                    HighCard.push_back(PHand[4].getValue());
                    HighCard.push_back(PHand[1].getValue());
                    HighCard.push_back(PHand[0].getValue());
                }
            }
        } else if (str == "TwoPair") {
            if (PHand[0].getValue() < PHand[1].getValue()) {     // 2 3 3 4 4
                HighCard.push_back(PHand[4].getValue());
                HighCard.push_back(PHand[1].getValue());
                HighCard.push_back(PHand[0].getValue());
            } else if (PHand[0].getValue() == PHand[1].getValue()) {     // 2 2 3 4 4, 2 2 3 3 4
                if (PHand[2].getValue() == PHand[3].getValue()) {     // 2 2 3 3 4
                    HighCard.push_back(PHand[2].getValue());
                    HighCard.push_back(PHand[0].getValue());
                    HighCard.push_back(PHand[4].getValue());
                } else {       // 2 2 3 4 4
                    HighCard.push_back(PHand[4].getValue());
                    HighCard.push_back(PHand[0].getValue());
                    HighCard.push_back(PHand[2].getValue());
                }
            }
        } else if (str == "OnePair") {
            if (PHand[0].getValue() == PHand[1].getValue()) {    // 2 2 3 4 5
                HighCard.push_back(PHand[0].getValue());
                HighCard.push_back(PHand[4].getValue());
                HighCard.push_back(PHand[3].getValue());
                HighCard.push_back(PHand[2].getValue());
            } else if (PHand[1].getValue() == PHand[2].getValue()) {    // 2 3 3 4 5
                HighCard.push_back(PHand[2].getValue());
                HighCard.push_back(PHand[4].getValue());
                HighCard.push_back(PHand[3].getValue());
                HighCard.push_back(PHand[0].getValue());
            } else if (PHand[2].getValue() == PHand[3].getValue()) {    // 2 3 4 4 5
                HighCard.push_back(PHand[3].getValue());
                HighCard.push_back(PHand[4].getValue());
                HighCard.push_back(PHand[1].getValue());
                HighCard.push_back(PHand[0].getValue());
            } else if (PHand[3].getValue() == PHand[4].getValue()) {    // 2 3 4 5 5
                HighCard.push_back(PHand[4].getValue());
                HighCard.push_back(PHand[2].getValue());
                HighCard.push_back(PHand[1].getValue());
                HighCard.push_back(PHand[0].getValue());
            }
        }

    }

    bool RoyalFlush() const {
        return (StraightFlush() and PHand[0].getValue() == 10);
    }

    bool StraightFlush() const {
        return Straight() and Flush();
    }

    bool FourOfAKind() const {
        auto first = PHand[0].getValue();
        auto second = PHand[1].getValue();
        auto third = PHand[2].getValue();
        auto fourth = PHand[3].getValue();
        auto fifth = PHand[4].getValue();
        // 2 2 2 2 3
        if (first == second and first == third and first == fourth and first != fifth) {
            return true;
        }
            // 2 3 3 3 3
        else if (second == third and second == fourth and second == fifth and second != first) {
            return true;
        } else {
            return false;
        }
    }

    bool FullHouse() const {
        auto first = PHand[0].getValue();
        auto second = PHand[1].getValue();
        auto third = PHand[2].getValue();
        auto fourth = PHand[3].getValue();
        auto fifth = PHand[4].getValue();
        // 2 2 2 3 3
        if (first == second and first == third and first != fourth and first != fifth and fourth == fifth) {
            return true;
        }
            // 2 2 3 3 3
        else if (third == fourth and third == fifth and third != first and third != second and first == second) {
            return true;
        } else {
            return false;
        }
    }

    bool Flush() const {
        for (auto i = 1; i < PHand.size(); i++) {
            if (PHand[0].getSuit() != PHand[i].getSuit()) {
                return false;
            }
        }
        return true;
    }

    bool Straight() const {
        auto first = PHand[0].getValue();
        auto second = PHand[1].getValue();
        auto third = PHand[2].getValue();
        auto fourth = PHand[3].getValue();
        auto fifth = PHand[4].getValue();
        // A 2 3 4 5  -> 2 3 4 5 A
        if (first == 2 and second == 3 and third == 4 and fourth == 5 and (fifth == 6 or fifth == 14)) {
            return true;
        } else {
            for (auto i = 1; i < PHand.size(); i++) {
                if (first + i != PHand[i].getValue()) {
                    return false;
                }
            }
        }
        return true;
    }

    bool ThreeOfAKind() const {
        auto first = PHand[0].getValue();
        auto second = PHand[1].getValue();
        auto third = PHand[2].getValue();
        auto fourth = PHand[3].getValue();
        auto fifth = PHand[4].getValue();
        // 2 2 2 3 4
        if (first == second and first == third and first != fourth and first != fifth and fourth != fifth) {
            return true;
        }
            // 2 3 3 3 4
        else if (second == third and second == fourth and second != first and second != fifth and first != fifth) {
            return true;
        }
            // 2 3 4 4 4
        else if (third == fourth and third == fifth and third != first and third != second and first != second) {
            return true;
        } else {
            return false;
        }
    }

    bool TwoPair() const {
        // 2 3 3 4 4
        if (PHand[1].getValue() == PHand[2].getValue() and PHand[3].getValue() == PHand[4].getValue() and
            (PHand[0].getValue() != PHand[1].getValue() and PHand[0].getValue() != PHand[2].getValue() and
             PHand[0].getValue() != PHand[3].getValue() and PHand[0].getValue() != PHand[4].getValue())) {
            return true;
        }
            // 2 2 3 4 4
        else if (PHand[0].getValue() == PHand[1].getValue() and PHand[3].getValue() == PHand[4].getValue() and
                 (PHand[2].getValue() != PHand[0].getValue() and PHand[2].getValue() != PHand[1].getValue() and
                  PHand[2].getValue() != PHand[3].getValue() and PHand[2].getValue() != PHand[4].getValue())) {
            return true;
        }
            // 2 2 3 3 4
        else if (PHand[0].getValue() == PHand[1].getValue() and PHand[2].getValue() == PHand[3].getValue() and
                 (PHand[4].getValue() != PHand[0].getValue() and PHand[4].getValue() != PHand[1].getValue() and
                  PHand[4].getValue() != PHand[2].getValue() and PHand[4].getValue() != PHand[3].getValue())) {
            return true;
        } else {
            return false;
        }
    }

    bool OnePair() const {
        if (PHand[0].getValue() == PHand[1].getValue()) {    // 2 2 3 4 5
            return true;
        } else if (PHand[1].getValue() == PHand[2].getValue()) {    // 2 3 3 4 5
            return true;
        } else if (PHand[2].getValue() == PHand[3].getValue()) {    // 2 3 4 4 5
            return true;
        } else if (PHand[3].getValue() == PHand[4].getValue()) {    // 2 3 4 5 5
            return true;
        } else {
            return false;
        }
    }

    int getBestHand() const {
        return int(BestHand);
    }

    string getBestHandRank() const {
        return BestRank;
    }

    bool operator<(const PokerHand &newPokerHand) const {
        if (this->getBestHand() == newPokerHand.getBestHand()) {
            for (auto i = 0; i < this->HighCard.size(); i++) {
                if (this->HighCard[i] < newPokerHand.HighCard[i]) {
                    return true;
                } else if (this->HighCard[i] > newPokerHand.HighCard[i]) {
                    return false;
                }
            }
            return false;
        } else {
            return this->getBestHand() < newPokerHand.getBestHand();
        }
    }

    bool operator>(const PokerHand &newPokerHand) const {
        if (this->getBestHand() == newPokerHand.getBestHand()) {
            for (auto i = 0; i < this->HighCard.size(); i++) {
                if (this->HighCard[i] < newPokerHand.HighCard[i]) {
                    return false;
                } else if (this->HighCard[i] > newPokerHand.HighCard[i]) {
                    return true;
                }
            }
            return false;
        } else {
            return this->getBestHand() > newPokerHand.getBestHand();
        }
    }

    bool operator==(const PokerHand &newPokerHand) const {
        if (this->getBestHand() == newPokerHand.getBestHand()) {
            for (auto i = 0; i < this->HighCard.size(); i++) {
                if (this->HighCard[i] < newPokerHand.HighCard[i]) {
                    return false;
                } else if (this->HighCard[i] > newPokerHand.HighCard[i]) {
                    return false;
                }
            }
            return true;
        } else {
            return this->getBestHand() == newPokerHand.getBestHand();
        }
    }
};


#endif