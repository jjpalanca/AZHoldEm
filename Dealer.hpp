/*
 * Dealer.hpp
 * Programmer: Jessmer John Palanca
 * Description: This class creates an object of a dealer of the game.
 *              It instantiates a vector of deck of cards, number of players,
 *              a vector of vector of winnning pokerhand(s), the name of the
 *              winning hand, and the pot money. The dealer shuffles and deals/distribute
 *              the cards to the community and to the players. The dealer also tracks the
 *              pot money. Lastly, The dealer determines the winner.
 */

#ifndef POKERHAND_DEALER_HPP
#define POKERHAND_DEALER_HPP

#include <iostream>
#include <vector>
#include "52Cards.hpp"
#include "PokerHand.hpp"
#include "Player.hpp"
#include <algorithm>
#include <random>
#include <chrono>
#include <string>

using namespace std;

class Dealer {
private:
    vector<Card> Deck;
    int numberOfPlayers;
    vector<vector<Card>> WinnerHand;
    string WinningHandName;
    double PotMoney;
public:
    Dealer(int numPlayers) {
        numberOfPlayers = numPlayers;
        DealDeck();
        SetPotMoney();
    }

    void DealDeck() {
        vector<Card> newDeck{C2, C3, C4, C5, C6, C7, C8, C9, C10, CJ, CQ, CK, CA,
                             D2, D3, D4, D5, D6, D7, D8, D9, D10, DJ, DQ, DK, DA,
                             H2, H3, H4, H5, H6, H7, H8, H9, H10, HJ, HQ, HK, HA,
                             S2, S3, S4, S5, S6, S7, S8, S9, S10, SJ, SQ, SK, SA};

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(newDeck.begin(), newDeck.end(), default_random_engine(seed));
        Deck = newDeck;
    }

    void SetPotMoney() {
        PotMoney = double(numberOfPlayers) * 2.00;
    }

    int getNumPlayers() const {
        return numberOfPlayers;
    }

    vector<vector<Card>> getWinnerHand() const {
        return WinnerHand;
    }

    string getWinningHandName() const {
        return WinningHandName;
    }

    double getPotMoney() const {
        return PotMoney;
    }

    Card Distribute() {
        Card topCard = Deck[Deck.size() - 1];
        Deck.pop_back();
        return topCard;
    }

    vector<int> DetermineWinner(vector<vector<Card>> bestHandList) {
        vector<int> playerIndex{0};
        WinnerHand.clear();
        WinningHandName = " ";
        PokerHand winner(bestHandList[0][0], bestHandList[0][1], bestHandList[0][2], bestHandList[0][3],
                         bestHandList[0][4]);
        for (auto i = 0; i < bestHandList.size(); i++) {
            PokerHand newHand(bestHandList[i][0], bestHandList[i][1], bestHandList[i][2], bestHandList[i][3],
                              bestHandList[i][4]);
            if (i == 0) {
                WinnerHand.push_back(winner.getSortedCard());
                WinningHandName = winner.getBestHandRank();
            } else {
                if (winner < newHand) {
                    WinnerHand.clear();
                    playerIndex.clear();
                    WinningHandName = " ";
                    WinnerHand.push_back(newHand.getSortedCard());
                    playerIndex.push_back(i);
                    WinningHandName = newHand.getBestHandRank();
                    winner = newHand;
                } else if (winner == newHand) {
                    playerIndex.push_back(i);
                    WinnerHand.push_back(newHand.getSortedCard());
                    winner = newHand;
                }
            }
        }
        return playerIndex;
    }
};

#endif //POKERHAND_DEALER_HPP
