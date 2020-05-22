/*
 * main.cpp
 * Programmer: Jessmer John Palanca
 * Description: This is the main that coordinates the game activities.
 *              The main creates a new dealer object and number of player of objects.
 *              Each round of the game, the dealer shuffles a new deck of cards, distribute
 *              the cards, collects $2.00 from each player, and determine who wins.
 *              The dealer adds the pot money to the winner's current balance. If there
 *              are multiple winners (tie), the pot money will be split to the winners.
 *              It prints out the community cards, each player's two cards, best hand,
 *              current balance, and prints out the winner, winner's winning hand, and
 *              the winner's new balance.
 */

#include <iostream>
#include <iomanip>
#include "Dealer.hpp"
#include "Card.cpp"
#include "52Cards.hpp"
#include <string>
#include <vector>
#include "Player.hpp"

using namespace std;

int main() {
    char option = ' ';
    int numberOfPlayers;
    vector<Player> players;

    cout << "How many players? ";
    cin >> numberOfPlayers;

    Dealer Jessmer(numberOfPlayers);

    for (auto i = 0; i < numberOfPlayers; i++) {
        double InitialMoney = 100.00;
        Player newPlayer(InitialMoney);
        players.push_back(newPlayer);
    }

    while (option != 'n') {

        vector<Card> CommunityCards;
        vector<vector<Card>> BestHandList;

        CommunityCards.clear();
        for (auto i = 0; i < 5; i++) {
            CommunityCards.push_back(Jessmer.Distribute());
        }
        for (auto i = 0; i < players.size(); i++) {
            players[i].SetNewTwoCards(Jessmer.Distribute(), Jessmer.Distribute());
        }

        cout << "Community Cards: ";

        for (auto card: CommunityCards) {
            cout << card.toString() << " ";
        }

        cout << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << endl;

        BestHandList.clear();

        for (auto i = 0; i < players.size(); i++) {
            players[i].setSevenCards(CommunityCards);
            players[i].ProcessCombination();
            players[i].getTheBestHand();
            players[i].minusBalance();
            BestHandList.push_back(players[i].getPlayerBestHand());
        }

        for (auto i = 0; i < players.size(); i++) {
            cout << "Player " << i + 1 << ": $" << fixed << setprecision(2) << players[i].getBalance() << " - ";
            players[i].PrintTwoCards();
            cout << endl;
            cout << "\t";
            players[i].PrintBestHand();
        }

        vector<int> playerIndex;
        double PotMoney = Jessmer.getPotMoney();
        playerIndex = Jessmer.DetermineWinner(BestHandList);

        if (playerIndex.size() > 1) {
            double PotDivided = PotMoney / double(playerIndex.size());
            cout << endl;
            cout << "Winning hands (tie)" << endl;
            cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            for (auto i = 0; i < playerIndex.size(); i++) {
                players[playerIndex[i]].addMoney(PotDivided);
            }

            for (auto i = 0; i < Jessmer.getWinnerHand().size(); i++) {
                for (auto j = 0; j < Jessmer.getWinnerHand()[i].size(); j++) {
                    cout << Jessmer.getWinnerHand()[i][j].toString() << " ";
                }
                cout << Jessmer.getWinningHandName() << " Player " << playerIndex[i] + 1 << " $"
                     << fixed << setprecision(2) << players[playerIndex[i]].getBalance() << endl;
            }


        } else if (playerIndex.size() == 1) {
            players[playerIndex[0]].addMoney(PotMoney);
            cout << endl;
            cout << "Winner: Player " << playerIndex[0] + 1 << " $" << fixed << setprecision(2) <<
                 players[playerIndex[0]].getBalance() << endl;
            cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            for (auto hand:Jessmer.getWinnerHand()) {
                for (auto card: hand) {
                    cout << card.toString() << " ";
                }
                cout << "   " << Jessmer.getWinningHandName() << endl;
            }
        }

        Jessmer.DealDeck();

        cout << endl;
        cout << "Play another game? <y or n> ";
        cin >> option;

    }
    return 0;
}