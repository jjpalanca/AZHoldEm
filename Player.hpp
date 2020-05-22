/*
 * Player.hpp
 * Programmer: Jessmer John Palanca
 * Description: This class creates an object of a player.
 *              It instantiates a vector of two cards that stores the two cards
 *              distributed by the dealer, a vector of seven cards that stores
 *              seven cards that's from the community cards and the player's two
 *              cards, a vector of best hand that stores the best hand of the player,
 *              a string that stores the name of the player's best hand, a vector of
 *              vector of 21 possible poker hands that a player can make it out of the
 *              seven cards, and the player's current balance.
 */

#ifndef AZHOLDEM_PLAYER_HPP
#define AZHOLDEM_PLAYER_HPP

#include <vector>
#include <iostream>
#include "52Cards.hpp"
#include "PokerHand.hpp"

using namespace std;

class Player {
private:
    vector<Card> TwoCards;
    vector<Card> SevenCards;
    vector<Card> BestHand;
    string HandName;
    vector<vector<Card>> Combinations;
    double Balance;

public:
    Player(const double &InitialMoney) {
        Balance = InitialMoney;
    }

    void ProcessCombination() {
        Combinations.clear();
        Card first = SevenCards[0];
        Card second = SevenCards[1];
        Card third = SevenCards[2];
        Card fourth = SevenCards[3];
        Card fifth = SevenCards[4];
        Card sixth = SevenCards[5];
        Card seventh = SevenCards[6];

        vector<Card> one{first, second, third, fourth, fifth};
        Combinations.push_back(one);
        vector<Card> two{first, second, third, fourth, sixth};
        Combinations.push_back(two);
        vector<Card> three{first, second, third, fourth, seventh};
        Combinations.push_back(three);
        vector<Card> four{first, second, third, fifth, sixth};
        Combinations.push_back(four);
        vector<Card> five{first, second, third, fifth, seventh};
        Combinations.push_back(five);
        vector<Card> six{first, second, third, sixth, seventh};
        Combinations.push_back(six);
        vector<Card> seven{first, second, fourth, fifth, sixth};
        Combinations.push_back(seven);
        vector<Card> eight{first, second, fourth, fifth, seventh};
        Combinations.push_back(eight);
        vector<Card> nine{first, second, fourth, sixth, seventh};
        Combinations.push_back(nine);
        vector<Card> ten{first, second, fifth, sixth, seventh};
        Combinations.push_back(ten);
        vector<Card> eleven{first, third, fourth, fifth, sixth};
        Combinations.push_back(eleven);
        vector<Card> twelve{first, third, fourth, fifth, seventh};
        Combinations.push_back(twelve);
        vector<Card> thirteen{first, third, fourth, sixth, seventh};
        Combinations.push_back(thirteen);
        vector<Card> fourteen{first, third, fifth, sixth, seventh};
        Combinations.push_back(fourteen);
        vector<Card> fifteen{first, fourth, fifth, sixth, seventh};
        Combinations.push_back(fifteen);
        vector<Card> sixteen{second, third, fourth, fifth, sixth};
        Combinations.push_back(sixteen);
        vector<Card> seventeen{second, third, fourth, fifth, seventh};
        Combinations.push_back(seventeen);
        vector<Card> eighteen{second, third, fourth, sixth, seventh};
        Combinations.push_back(eighteen);
        vector<Card> nineteen{second, third, fifth, sixth, seventh};
        Combinations.push_back(nineteen);
        vector<Card> twenty{second, fourth, fifth, sixth, seventh};
        Combinations.push_back(twenty);
        vector<Card> twenty1{third, fourth, fifth, sixth, seventh};
        Combinations.push_back(twenty1);
    }

    void minusBalance() {
        Balance -= 2.00;
    }

    void getTheBestHand() {
        PokerHand best(Combinations[0][0], Combinations[0][1], Combinations[0][2], Combinations[0][3],
                       Combinations[0][4]);
        for (auto i = 0; i < Combinations.size(); i++) {
            PokerHand newHand(Combinations[i][0], Combinations[i][1], Combinations[i][2], Combinations[i][3],
                              Combinations[i][4]);
            if (i == 0) {
                BestHand = best.getSortedCard();
                HandName = best.getBestHandRank();
            } else {
                if (best < newHand) {
                    BestHand.clear();
                    HandName = "";
                    BestHand = newHand.getSortedCard();
                    HandName = newHand.getBestHandRank();
                    best = newHand;
                }
            }
        }
    }

    vector<Card> getPlayerBestHand() const {
        return BestHand;
    }

    double getBalance() const {
        return Balance;
    }

    void addMoney(double money) {
        Balance = Balance + money;
    }

    void setSevenCards(vector<Card> community) {
        SevenCards.clear();
        for (auto i = 0; i < community.size(); i++) {
            SevenCards.push_back(community[i]);
        }
        SevenCards.push_back(TwoCards[0]);
        SevenCards.push_back(TwoCards[1]);
    }

    void PrintBestHand() {
        auto y = BestHand;
        cout << "Best Hand: ";
        for (auto x: BestHand) {
            cout << x.toString() << " ";
        }
        cout << " - " << HandName << endl;

    }

    void SetNewTwoCards(const Card &A, const Card &B) {
        TwoCards.clear();
        TwoCards.push_back(A);
        TwoCards.push_back(B);
    }

    void PrintTwoCards() {
        cout << TwoCards[0].toString() << " " << TwoCards[1].toString();
    }
};

#endif //AZHOLDEM_PLAYER_HPP
