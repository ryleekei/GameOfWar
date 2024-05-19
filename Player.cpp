#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

// default constructor 
Player::Player()
{
	 numCards = 0;  // how many cards in player's hand 	
}

// alternative constructor 
Player:: Player(vector<Card> ini_cards)
{
	for (int pos = 0; pos != ini_cards.size(); pos++)
	{
		cards.push_back(ini_cards.at(pos));
	}

	numCards = ini_cards.size();

}

// return how many cards player holds currently 
int Player::getNumCards() const
{
	return numCards;
}

// player plays one card at the front of cards at hand 
Card Player::play_a_card()
{//check if numCards is 0


	if (numCards != 0)
	{
		Card card = cards.front();
		cards.pop_front();
		
		numCards = numCards - 1;
		
		return card;

	}
	
}

// player wins and adds winning cards to the end of the pile at hand  
void Player::addCards(vector<Card> winningCards)
{
	for (int i = 0; i < winningCards.size(); i++)
	{
		cards.push_back(winningCards.at(i));

	}
	numCards = numCards + winningCards.size();
}

// player drops THREE cards from the front of pile at hand 
// when there is a tie 
vector<Card> Player::dropCards()
{
	vector<Card> ThreeCards;

	int iterator = 3;

	if (numCards < 3)
	{
		iterator = cards.size();
	}
	
	for (int i = 0; i < iterator; i++) 
	{
		Card card = cards.front();
		cards.pop_front();
		ThreeCards.push_back(card);
	}
	numCards = numCards - iterator;
	return ThreeCards;

}

// display cards at player's hand 
void Player::print() const
{
	auto pos = cards.begin();
	Card card;

	while (pos != cards.end()) 
	{
		card = *pos;
		cout << " ";
		card.print();
		pos++;
	}
	
}