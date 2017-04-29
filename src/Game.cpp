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


	void GAME::construct_card_vector(int pos, vector<card>& tempVector) {
		tempVector.push_back(cardStack[pos]);
		cardStack.erase(cardStack.begin() + pos);
	};

	int GAME::MoveCard() {
		int from = -1,to = -1 , count= -1;


		cout << "Choose pile: " << flush;
		cin >> from;


		if ((from < 1 || from > 7) && (from != NUM_OF_COLUMNS + NUM_OF_HOMES+1)) {
			cerr << "Wrong pile choosen" << endl;
			return -1;
		}

		cout << "Choose amount of cards: " << flush;
		cin >> count;


		if (static_cast<unsigned int> (count) > piles[from-1]->shownCards || count < 1) {
			cerr << "Wrong amount choosen" << endl;
			return -1;
		}


		cout << "Choose another pile to place: " << flush;
		cin >> to;

		//TODO in new ver. replace with : if (to < 1 || to == from)
		if (to < 1 || to >  (NUM_OF_COLUMNS + NUM_OF_HOMES) || to == from) {
			cerr << "Wrong pile choosen" << endl;
			return -1;
		}
		//TODO DELETE
		if (to > 7 && count > 1) {
			cerr << "Can't place more then one card to this piles" << endl;
			return -1;
		}

			//detection if were chosen right amount of cards
			vector<card> temp_vect = VecSlice(piles[from-1]->GetPile(), -count);
			if (temp_vect.size() < 1) {
				cerr << "You must choose pile with cards" << endl;
				return -1;
			}


		//add all choosen cards from source pile to target pile
		vector<card> temp_card_vec;
		for (int i = 0; i < count; i++) {
			temp_card_vec.push_back(piles[from - 1]->PopCard());
		}
		if(piles[to - 1]->AddCard(temp_card_vec)){
				cerr<<"You can't place cards here."<<endl;
				piles[from - 1]->AddCard(temp_card_vec, Pile_Interface::INSERT_ONLY);
				piles[from - 1]->shownCards+= count;
				return -1;
		}

	}

	void GAME::RotateStack() {
		if(piles[11]->IsEmpty()){
			cerr<<"pile 11 is empty some error occured!\n";
			exit(-1);
		}
		card temp = piles[11]->GetPile()[0];
		auto temp_vec = VecSlice(piles[11]->GetPile(), 1);
		temp_vec.push_back(temp);
		delete piles[11];
		piles[11] = factory.GetStoragePile(temp_vec);
	}

	void GAME::Play() {
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
	}

	void GAME::ShowTable() {
		for (int i = 1; i <= NUM_OF_HOMES + NUM_OF_COLUMNS + 1;i++) {
			cout <<setw(3)<< i << ") " << flush;
			PrintCards( VecSlice(piles[i-1]->GetPile(),-static_cast<int>(piles[i-1]->shownCards)));
		}
	}


// int main(int argc, char **argv)
// {
// 	GAME game;
// 	for (auto c : game.piles) {
// 		PrintCards(c.GetPile());
// 		cout << string(40, '=')<<endl;
// 	}
// 	while (1) {
// 		cout << string(40, '+') << endl;
// 		game.ShowTable();
// 		cout << string(40, '+') << endl;
// 		game.Play();
// 	}
// 	return 0;
	//vector<card> cardStack = {};
	//for (int i = 2; i <= A; i++)
	//{
	//	for (int k = CLUBS; k <= SPADES; k= k+1)
	//	{
	//		cardStack.push_back(card(static_cast<cardsuit>(k), i));
	//	}
	//}

	//
	//vector<card> tempVector;
	////add card to vector and delete from card stack
	//auto construct_card_vector = [&](int pos){
	//	tempVector.push_back(cardStack[pos]);
	//	cardStack.erase(cardStack.begin() + pos);
	//};



	//vector < pile > piles;
	//srand(static_cast<unsigned int>(time(0)));
	//
	////fill all 7 piles with random cards
	//for (int i = 0; i < 7; i++) {
	//	for (int num = 0; num <= i; num++) {
	//		construct_card_vector(rand() % cardStack.size());
	//	}
	//	piles.push_back(pile(tempVector));
	//	tempVector.clear();
	//}
	//for (auto pil : piles) {
	//	PrintCards(pil.GetPile());
	//	cout << string(40,'=')<<endl;
	//}


	//cout << endl << endl<<"Shown cards ("<<piles[6].shownCards<<"):\n";
	////prints shown on pile cards
	//PrintCards(VecSlice(piles[6].GetPile(), -static_cast<int>(piles[6].shownCards) ));

	////inicialization of homes
	//pile home1(vector<card>{});
	//pile home2(vector<card>{});
	//pile home3(vector<card>{});
	//pile home4(vector<card>{});
	//home1.shownCards = 0;
	//home2.shownCards = 0;
	//home3.shownCards = 0;
	//home4.shownCards = 0;


	//

	//return 0;
// }
