/**
 * @file    Game.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Implementation of main class Game representing the whole game
 */

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <string>
#include <functional>
#include <time.h>
#include "Game.hpp"

namespace solitaire
{

	/**
		Print vector of  cards to standart output (debug function)
		@param st Cards vector to be printed
	*/
	void PrintCards(vector<card> st)
	{
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

	/**
		Print one card to standart output (debug function)
		@param c Card to be printed
	*/
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

	/**
		Slice vector to a vector from pos begin to end of the original one
		@param base Input vector
		@param begin Start position
		@param end End position
		@return Sliced vector
	*/
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

	/**
		Move card from STACK to vector of cards
		@param pos Position in stack of all cards
		@param[out] tempVector Vector to put in cards
	*/
	void GAME::construct_card_vector(int pos, vector<card>& tempVector)
	{
		tempVector.push_back(cardStack[pos]);
		cardStack.erase(cardStack.begin() + pos);
	};

	/**
	 Move cards in TUI version of game
	 @return Success or not
	 */
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

		if(piles[from - 1]->shownCards == static_cast<unsigned>(count) && static_cast<unsigned>(count) != piles[from - 1]->size) currentCmd.revealed = true;
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

	/**
	 Move cards in GUI version of game
	 @param cmd Structure which contains command
	 @return Success or not
	 */
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

	/**
	 Reversive move cards function for backsteps implementation
	*/
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

	/**
	 Rotate stack of cards
	*/
	void GAME::RotateStack()
		{
		if(piles[11]->IsEmpty()){
            cerr << "ERROR: deck is empty" << endl;
            return;
		}
		rotate(piles[11]->GetPile().begin(), piles[11]->GetPile().begin()+1, piles[11]->GetPile().end());
	}

	/**
	 Reversive rotate stack of cards for backsteps implementation
	*/
	void GAME::rev_RotateStack()
	{
		rotate(piles[11]->GetPile().begin(), piles[11]->GetPile().end()-1, piles[11]->GetPile().end());
	}

	/**
	 Run appropriate command for reversing last action in game
	*/
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

	/**
		Implements help in game
		@param[out] one Reference to the first returned pile
		@param[out] two Reference to the second returned pile
	*/
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
						if( (lcd.getValue() - 1 == static_cast<unsigned>(Dtemp_value)) && (Dtemp_suit == lcd.getSuit()) )  {
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
							if( (fcd.getValue() + 1 == static_cast<unsigned>(Dtemp_value)) &&(static_cast<unsigned>(Dtemp_suit) == SPADES || Dtemp_suit == CLUBS) ) {
		            return;
		          }
		          break;
		        default:
							if( (fcd.getValue() + 1 == static_cast<unsigned>(Dtemp_value)) && (static_cast<unsigned>(Dtemp_suit) == DIAMONDS || Dtemp_suit == HEARTS) )  {
		            return;
		          }
		        }
					}
				}
			}

		}
		one =12;two = 12;
	}

	/**
		Implements saving in game
		@param[out] path_to_save Path to save file
	*/
	void GAME::Save(string path_to_save)
	{
		ofstream ofile;
		ofile.open(path_to_save.c_str());
		if(ofile.fail()){
			throw std::invalid_argument("Can't open file for writing.\n");
			return;
		}
		for(auto pl : piles){
			ofile<<pl->str()<<"\n";
		}
		ofile.close();
	}

	/**
		Check if game is ended
		@return 1 if its ended 0 otherwise
	*/
	int GAME::IsEnd(){
		int win = 0;
		for(auto home : homes){
			if(home->size == 13) win++;
		}
		if(win == 4){
			End = true;
			return 1;
		}
		return 0;
	}

	/**
		Main function which controls flow of TUI game version
	*/
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
				IsEnd();
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
	}

	/**
		Main function which controls flow of GUI game version
		@param command Command structure taken from GUI
	*/
	void GAME::Play(solitaire::Command command)
	{
        if (command.type == solitaire::move) {
		    if(piles[command.from - 1]->shownCards == static_cast<unsigned>(command.count) && static_cast<unsigned>(command.count) != piles[command.from - 1]->size) command.revealed = true;
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
				IsEnd();
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
	}

	/**
		Show table in TUI version of game (debug version)
	*/
	void GAME::ShowTable() {
		for (int i = 1; i <= NUM_OF_HOMES + NUM_OF_COLUMNS + 1;i++) {
			cout <<setw(3)<< i <<"[si:"<<piles[i-1]->size<<" sh:"<<piles[i-1]->shownCards<<']'<< ") " << flush;
			PrintCards( VecSlice(piles[i-1]->GetPile(),-static_cast<int>(piles[i-1]->shownCards)));
		}
	}
}
