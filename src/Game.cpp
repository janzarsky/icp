#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <string>
#include <functional>
#include <time.h>
#include <algorithm>
#include "Game.hpp"




// using namespace std;



//Print all cards in the vector
void PrintCards(vector<card> st)
{
	unsigned counter = 0;
	for (card c : st)
	{
		cout << setiosflags(ios::left)<< flush;
		switch (c.getSuit())
		{
		case CLUBS:
			cout<<  "CLUBS" << flush;
			break;
		case DIAMONDS:
			cout <<  "DIAMONDS" << flush;
			break;
		case HEARTS:
			cout <<  "HEARTS" << flush;
			break;
		case SPADES:
			cout << "SPADES" << flush;
			break;
		default:
			cout << "UNKNOWN" << flush;
			break;
		}
		cout << ":" << flush;
		switch (c.getValue())
		{
		case 11:
			cout << setw(3) << "J";
			break;
		case 12:
			cout << setw(3) << "Q";
			break;
		case 13:
			cout << setw(3) << "K";
			break;
		case 1:
			cout << setw(3) << "A";
			break;
		default:
			cout << setw(3) << c.getValue();
			break;
		}
	}
	cout << endl;
}

void PrintCards(card c)
{
		cout << setiosflags(ios::left)<< flush;
		switch (c.getSuit())
		{
		case CLUBS:
			cout <<"CLUBS" << flush;
			break;
		case DIAMONDS:
			cout <<"DIAMONDS" << flush;
			break;
		case HEARTS:
			cout <<"HEARTS" << flush;
			break;
		case SPADES:
			cout <<"SPADES" << flush;
			break;
		default:
			cout <<"UNKNOWN" << flush;
			break;
		}
		cout << ":" << flush;
		switch (c.getValue())
		{
		case 11:
			cout <<"J  " << endl;
			break;
		case 12:
			cout <<"Q  " << endl;
			break;
		case 13:
			cout <<"K  " << endl;
			break;
		case 1:
			cout <<"A  " << endl;
			break;
		default:
			cout <<c.getValue() << "  "<< endl;
			break;
		}
}

//Slice vector to a vector from pos begin to end of the original one
template<class T>
vector<T> VecSlice(vector<T> base, int begin, int end )
{
	if(base.size() == 0) {
		return vector<T>{};
	}
	if (end < 0) {
		end = base.size() + end ;
	}
	else if (end == 0) {
		end = base.size()-1;
	}
	if (begin < 0) {
		begin = base.size() + begin;
	}
	if ( begin <= end)
	{
		return vector<T>(base.begin() + begin, base.begin() + 1 + end);
	}
	else
	{
		return vector<T>{};
	}

}

	//move card from STACK to vector of cards
	void GAME::construct_card_vector(int pos, vector<card>& tempVector)
	{
		tempVector.push_back(cardStack[pos]);
		cardStack.erase(cardStack.begin() + pos);
	};

	//function for moving cards
	int GAME::MoveCard() {
		int from = -1,to = -1 , count= -1;


		cout << "Choose pile: " << flush;
		cin >> from;


		if ((from < 1 || from > 7) && (from != NUM_OF_COLUMNS + NUM_OF_HOMES+1)) {
			cerr << "\nWrong pile choosen" << endl;
			return -1;
		}

		cout << "Choose amount of cards: " << flush;
		cin >> count;


		if (static_cast<unsigned int> (count) > piles[from-1]->shownCards || count < 1) {
			cerr << "\nWrong amount choosen" << endl;
			return -1;
		}


		cout << "Choose another pile to place: " << flush;
		cin >> to;


		if (to < 1 || to >  (NUM_OF_COLUMNS + NUM_OF_HOMES) || to == from) {
			cerr << "\nWrong pile choosen" << endl;
			return -1;
		}
		if (to > 7 && count > 1) {
			cerr << "\nCan't place more then one card to this piles" << endl;
			return -1;
		}

			//detection if were chosen right amount of cards
			vector<card> temp_vect = VecSlice(piles[from-1]->GetPile(), -count);
			if (temp_vect.size() < 1) {
				cerr << "\nYou must choose pile with cards" << endl;
				return -1;
			}


		//add all choosen cards from source pile to target pile
		vector<card> temp_card_vec;
		for (int i = 0; i < count; i++) {
			temp_card_vec.push_back(piles[from - 1]->PopCard());
		}
		if(piles[to - 1]->AddCard(temp_card_vec)){
				cerr<<"\nYou can't place cards here."<<endl;
				piles[from - 1]->AddCard(temp_card_vec, Pile_Interface::INSERT_ONLY);
				piles[from - 1]->shownCards+= count;
				return -1;
		}

	}

	void GAME::RotateStack()
	{
		if(piles[11]->IsEmpty()){
			cerr<<"\npile 11 is empty some error occured!\n";
			exit(-1);
		}
		card temp = piles[11]->GetPile()[0];
		auto temp_vec = VecSlice(piles[11]->GetPile(), 1);
		temp_vec.push_back(temp);
		delete piles[11];
		piles[11] = factory.GetStoragePile(temp_vec);
	}

	//"Play game" for CONSOLE version of game
	void GAME::Play()
	{
		char choose;
		cout << "m - move cards    n-new card   x-exit"<<endl;
		cout << "Choose what you want to do: "<<flush;
		cin >> choose;
		switch (choose)
		{
		case 'm':
			MoveCard();
			break;
		case 'n':
			RotateStack();
			break;
		case 'x':
			exit(1);
			break;
		default:
			cerr << "unknown command "<<endl;
			break;
		}
		int win = 0;
		for(auto home : homes){
			if(home->size == 14) win++;
		}
		if(win == 4){
			cout<<"CONGRATS!!\nWIN!\n";
			exit(0);
		}
	}

	void GAME::ShowTable() {
		for (int i = 1; i <= NUM_OF_HOMES + NUM_OF_COLUMNS + 1;i++) {
			cout <<setw(3)<< i << ") " << flush;
			PrintCards( VecSlice(piles[i-1]->GetPile(),-static_cast<int>(piles[i-1]->shownCards)));
		}
	}
