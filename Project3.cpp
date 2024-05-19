/*
File: Project3.cpp
 * Course: CS215-002
 * Project: Project 3
 * Purpose: Demonstrate War between two players, displaying their card amounts and who wins each round, and, ultimately the 
 *			entire game. If a tie occurs between players, they must drop three cards each into the pile then play a fourth one. 
 *          This decides who wins the tie.
 * Author: Rylee Hobbs
*/

#include <iostream>
#include <string>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

//function to display the pile to save space
void displayPile(vector<Card> pile) {
    cout << "\n----------------------------------------------" << endl;

    cout << "\nThere are " << pile.size() << " on the pile!" << endl;

    cout << "\n----------------------------------------------" << endl;
}

int main() {
    // Avoid magic numbers
    const int HANDS = 26;    // each player holds 26 cards to begin the game

    // create an object of Deck class to represent standard 52-card deck
    // create a 52-card deck first
    Deck playDeck;
    playDeck.createDeck();
    //playDeck.shuffleDeck();

    //Deal 26 cards to both players
    vector<Card> cards_Player1;
    vector<Card> cards_Player2;
    vector<Card> pile;

    for (int i = 0; i < HANDS; i++)
    {
        cards_Player1.push_back(playDeck.deal_a_card());
        cards_Player2.push_back(playDeck.deal_a_card());
    }

    //Create players
    Player player1(cards_Player1);
    Player player2(cards_Player2);

    string cont;

    do {
        cont = "\n";
        // 1. Display one top card(suit and point) from each player, which represents the card played by each player in the current round
        Card faceup1 = player1.play_a_card();
        cout << "Player 1 plays: ";
        faceup1.print();

        Card faceup2 = player2.play_a_card();
        cout << "\nPlayer 2 plays: ";
        faceup2.print();


        // 2. Display how many cards on the pile(on the table)

        pile.push_back(faceup1);
        pile.push_back(faceup2);

        displayPile(pile);

        // 3. Decide which player wins the current round or it is a tie

        if (faceup1.compareTo(faceup2) == 1) //faceup1 > faceup2
        {
            cout << "Player 1 wins...get all cards from the current round!" << endl;
            player1.addCards(pile);
            pile.clear();
        }
        else if (faceup1.compareTo(faceup2) == (-1)) //faceup1 < faceup2
        {
            cout << "Player 2 wins...get all cards from the current round!" << endl;
            player2.addCards(pile);
            pile.clear();
        }
        else //If there is a tie, draw the next set of cards
        {
            cout << "It is a tie...for this round!\nEach player drops three cards(face down) on the pile, then\nplay one more card (face up)";

            vector<Card> drop1 = player1.dropCards();
            auto pos = drop1.begin();
            while (pos != drop1.end()) {
                Card card = *pos;
                pile.push_back(card);
                pos++;
            }

            vector<Card> drop2 = player2.dropCards();
            pos = drop2.begin();
            while (pos != drop2.end()) {
                Card card = *pos;
                pile.push_back(card);
                pos++;
            }
            displayPile(pile); //adding player's dropped cards to the pile
        }
        
        //displaying the hands of each player
        cout << "Player1 has " << player1.getNumCards() << " cards in hand!" << endl;
        cout << "Player2 has " << player2.getNumCards() << " cards in hand!" << endl;

        cout << "\nDo you want to continue...for the next round ? (N or n to\nquit)" << endl;

        
        getline(cin, cont, '\n');
        cin.clear();
    } while (player1.getNumCards() > 0 && player2.getNumCards() > 0 && cont != "n" && cont !="N");
    
    //initializing each deck size for comparison
    int p1Cards = player1.getNumCards();
    int p2Cards = player2.getNumCards();

    if (cont == "n" || cont == "N")
    {
        cout << "You choose to quit the game!" << endl;
        cout << "Player1 has " << p1Cards << " cards left!" << endl;
        cout << "Player2 has " << p2Cards << " cards left!" << endl;
    }

    else
    {
        cout << "Game is over!";
            if (p1Cards > p2Cards)
            {
                cout << "Player 1 ";
            }
            else cout << "Player 2 ";
            cout << "wins the game!" << endl;
    }

    return 0;
}