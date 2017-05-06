#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <string>
#include <functional>
#include <time.h>
#include <algorithm>
#include "Game.hpp"


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

		//Control you choose from target pile or stack
		if ((from < 1 || from > 7) && (from != NUM_OF_COLUMNS + NUM_OF_HOMES+1)) {
			cerr << "\nWrong pile choosen" << endl;
			return -1;
		}

		cout << "Choose amount of cards: " << flush;
		cin >> count;

		//Control you choose allowed amount of cards
		if (static_cast<unsigned int> (count) > piles[from-1]->shownCards || count < 1) {
			cerr << "\nWrong amount choosen" << endl;
			return -1;
		}


		cout << "Choose another pile to place: " << flush;
		cin >> to;

		//Control you choose right pile to place cards
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

		//Control you choose from target pile or stack
		if ((from < 1 || from > 7) && (from != NUM_OF_COLUMNS + NUM_OF_HOMES+1)) {
			cerr << "\nWrong pile choosen" << endl;
			return -1;
		}

		//Control you choose allowed amount of cards
		if (static_cast<unsigned int> (count) > piles[from-1]->shownCards || count < 1) {
			cerr << "\nWrong amount choosen" << endl;
			return -1;
		}

		//Control you choose right pile to place cards
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

	//Help function return throuw parameter  possible piles to choose from
	void GAME::Help(int &one, int &two) const
	{

		//pass through targer piles and storage
		for(one =1; one<= NUM_OF_COLUMNS+NUM_OF_HOMES+1;one++){
			if(one == 8){
				one = 11;
				continue;
			}
			auto spl = piles[one-1];
			if(spl->IsEmpty()) continue;

			card fcd = *(spl->GetPile().end() - spl->shownCards);
			card lcd = *(spl->GetPile().end() - 1);


			for(two = 1;two <= NUM_OF_COLUMNS+NUM_OF_HOMES;two++){
				auto dpl = piles[two-1];
				//trying placing to HOME pile
				if(two > NUM_OF_COLUMNS && two <= NUM_OF_COLUMNS+NUM_OF_HOMES ){
					if(dpl->IsEmpty()){
						if(lcd.getValue() == A){
							return;
						}
						continue;
					}
					else{
						int Dtemp_suit = dpl->GetPile().back().getSuit();
						int Dtemp_value = dpl->GetPile().back().getValue();
						if( (lcd.getValue() - 1 == Dtemp_value) && (Dtemp_suit == lcd.getSuit()) )  {
	            return;
	          }
					}
				}
				//trying placing to TARGET piles
				else{
					if(dpl->IsEmpty()){
						if(fcd.getValue() == K && spl->shownCards != spl->size){
							return;
						}
						continue;
					}
					else{
						int Dtemp_suit = dpl->GetPile().back().getSuit();
						int Dtemp_value = dpl->GetPile().back().getValue();
						switch (fcd.getSuit()) {
		        case DIAMONDS:
		        case HEARTS:
							if( (fcd.getValue() + 1 == Dtemp_value) &&(Dtemp_suit == SPADES || Dtemp_suit == CLUBS) ) {
		            return;
		          }
		          break;
		        default:
							if( (fcd.getValue() + 1 == Dtemp_value) && (Dtemp_suit == DIAMONDS || Dtemp_suit == HEARTS) )  {
		            return;
		          }
		        }
					}
				}
			}

		}
		one =12;two = 12;
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
			int from,to;
			Help(from,to);
			cout<<"HELP: "<<from<<"--"<<to<<endl;
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
        if (command.type == solitaire::move) {
		    if(piles[command.from - 1]->shownCards == command.count && command.count != piles[command.from - 1]->size) command.revealed = true;
		    else command.revealed = false;
        }

		switch (command.type)
		{
		case solitaire::move:
			if(MoveCard(command) == 0){
				//add current command to history
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
			//add current command to history
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
