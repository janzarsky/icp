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

	//function for moving cards in CONSOLE version
	int GAME::MoveCard()
	{
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

		if(piles[from - 1]->shownCards == count && count != piles[from - 1]->size) currentCmd.revealed = true;
		else currentCmd.revealed = false;
		if(!piles[to - 1]->AddCard(temp_vect)){
				for (int i = 0; i < count; i++) {
					piles[from - 1]->PopCard();
				}
				currentCmd.type = solitaire::move;
				currentCmd.from = from;
				currentCmd.to = to;
				currentCmd.count = count;
				return 0;
		}
		else{
			return -1;
		}
	}

	//function for moving cards in GUI version
	int GAME::MoveCard(solitaire::Command cmd)
	{
		int from = cmd.from,to = cmd.to , count= cmd.count;


		if ((from < 1 || from > 7) && (from != NUM_OF_COLUMNS + NUM_OF_HOMES+1)) {
			cerr << "\nWrong pile choosen" << endl;
			return -1;
		}


		if (static_cast<unsigned int> (count) > piles[from-1]->shownCards || count < 1) {
			cerr << "\nWrong amount choosen" << endl;
			return -1;
		}


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
		if(!piles[to - 1]->AddCard(temp_vect)){
				for (int i = 0; i < count; i++) {
					piles[from - 1]->PopCard();
				}
				return 0;
		}
		else{
			return -1;
		}

	}


	void GAME::rev_MoveCard()
	{
		vector<card> vec;
		vec = VecSlice(piles[currentCmd.to-1]->GetPile(),-currentCmd.count);
		piles[currentCmd.from-1]->AddCard(vec,piles[currentCmd.from-1]->INSERT_ONLY);
		for(int i =0;i<currentCmd.count;i++)piles[currentCmd.to-1]->PopCard();

		if(currentCmd.from != NUM_OF_COLUMNS + NUM_OF_HOMES + 1){
			if(currentCmd.from <= NUM_OF_COLUMNS){
				piles[currentCmd.from-1]->shownCards+=currentCmd.count;
				if(currentCmd.revealed)piles[currentCmd.from-1]->shownCards--;
			}
			else{
				piles[currentCmd.from-1]->shownCards = 1;
			}
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


	void GAME::rev_RotateStack()
	{

		card temp = piles[11]->GetPile().back();
		auto vec = VecSlice(piles[11]->GetPile(), 0, -2);
		vec.insert(vec.begin(),temp);
		delete piles[11];
		piles[11]=factory.GetStoragePile(vec);

	}


	void GAME::Backward()
	{
		if(!history.empty()){
			currentCmd = history.back();
			history.pop_back();
			switch(currentCmd.type){
				case solitaire::move:
					rev_MoveCard();
					break;
				case solitaire::turn:
					rev_RotateStack();
					break;
				default:
					cerr<<"Unknown command in history\n";
			}
		}
		else{
			cerr<<"You can't do more backsteps\n";
		}
	}


	//"Play game" for CONSOLE version of game
	void GAME::Play()
	{
		char choose;
		cout << "m-move cards    n-new card   x-exit   b-step backward   h-help"<<endl;
		cout << "Choose what you want to do: "<<flush;
		cin >> choose;
		switch (choose)
		{
		case 'm':
		  if(MoveCard() == 0){
				//add current command to history if it's move command
				if(history.size() == MAX_RETURNS){
					history.pop_front();
					history.push_back(currentCmd);
				}
				else{
					history.push_back(currentCmd);
				}
			}
			break;
		case 'n':
			currentCmd.type = solitaire::turn;
			RotateStack();
			//add current command to history if it's next_card command
			if(history.size() == MAX_RETURNS){
				history.pop_front();
				history.push_back(currentCmd);
			}
			else{
				history.push_back(currentCmd);
			}
			break;
		case 'x':
			exit(1);
			break;
		case 'b':
			Backward();
			break;
		case 'h':
			//Help();
			break;
		default:
			cerr << "unknown command "<<endl;
			break;
		}

		//checks for win
		int win = 0;
		for(auto home : homes){
			if(home->size == 14) win++;
		}
		if(win == 4){
			cout<<"CONGRATS!!\nWIN!\n";
			exit(0);
		}
	}

	// "Play game" for GUI version of game
	void GAME::Play(solitaire::Command command)
	{
		if(piles[command.from - 1]->shownCards == command.count && command.count != piles[command.from - 1]->size) command.revealed = true;
		else command.revealed = false;

		switch (command.type)
		{
		case solitaire::move:
			if(MoveCard(command) == 0){
				//add current command to history if it's move command
				if(history.size() == MAX_RETURNS){
					history.pop_front();
					history.push_back(command);
				}
				else{
					history.push_back(command);
				}
			}
			break;
		case solitaire::turn:
			RotateStack();
			//add current command to history if it's next_card command
			if(history.size() == MAX_RETURNS){
				history.pop_front();
				history.push_back(command);
			}
			else{
				history.push_back(command);
			}
			break;
		//TODO
		// case exit:
		// 	exit(1);
		// 	break;
		// case backward:
		// 	Backward();
		// 	break;
		// case help:
		// 	Help();
		// 	break;
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
			cout <<setw(3)<< i <<"[si:"<<piles[i-1]->size<<" sh:"<<piles[i-1]->shownCards<<']'<< ") " << flush;
			PrintCards( VecSlice(piles[i-1]->GetPile(),-static_cast<int>(piles[i-1]->shownCards)));
		}
	}
