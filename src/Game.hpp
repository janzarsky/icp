/**
 * @file    Game.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Declaration of Class Game, desctiption of look of all game piles
 */

#ifndef GAME_H
#define GAME_H
#include "Card.hpp"
#include "Pile_Factory.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include "Command.hpp"
#include <fstream>
#include <sstream>


using namespace std;

namespace solitaire
{

typedef Pile_Interface pile;

const int NUM_OF_CARDS = 52;
const int NUM_OF_COLUMNS = 7;
const int NUM_OF_HOMES = 4;
const int MAX_RETURNS = 5; //!< Maximum backsteps (editable)




/*									  ALL	PILES LOOK

1)piles[0]---------------first     TARGET      pile---------------------
2)piles[1]---------------second    TARGET      pile---------------------
3)piles[2]---------------third     TARGET      pile---------------------
4)piles[3]-------------- fourth    TARGET      pile---------------------
5)piles[4]---------------fifth     TARGET      pile---------------------
6)piles[5]---------------sixth     TARGET      pile---------------------
7)piles[6]---------------seventh   TARGET      pile---------------------
8)piles[7]---------------first     HOME        pile---------------------
9)piles[8]---------------second    HOME        pile---------------------
10)piles[9]--------------third     HOME        pile---------------------
11)piles[10]-------------forth     HOME        pile---------------------
12)piles[11]-------------pile with STORAGE     pile---------------------
*/


//Print all cards in the vector
void PrintCards(vector<card>);
void PrintCards(card c);


template<class T>
vector<T> VecSlice(vector<T>, int = 0, int = 0);

/** Main class that controls all actions in one game*/
class GAME {

		list<solitaire::Command> history;	//!< List that holds history of moves
		solitaire::Command currentCmd;	//!< Holds current command
		vector<card> cardStack = {};	//!< Stack of all cards
		Pile_Factory factory;	//!< Factory for creating piles
		vector<pile *> homes; //!< Vector with pointers to homes

		void construct_card_vector(int pos, vector<card>& tempVector);

		void rev_MoveCard();

		void rev_RotateStack();

		int IsEnd();

	public:
		vector <pile *> piles;	//!< Vector of pointers to all PILES
		bool End = 0;  //!< Indicates if game is ended
	  GAME()
		{
			for (unsigned i = 1; i <= K; i++)
			{
				for (unsigned k = CLUBS; k <= SPADES; k = k + 1)
				{
					cardStack.push_back(card(static_cast<cardsuit>(k), i));
				}
			}
			vector<card> tempVector;
			srand(static_cast<unsigned int>(time(0)));

			//fill all 7 piles with random cards
			for (int i = 0; i < NUM_OF_COLUMNS + NUM_OF_HOMES + 1; i++) {
				//creating HOMES
				if (i >= 7 && i < (NUM_OF_COLUMNS + NUM_OF_HOMES )) {
					piles.push_back(factory.GetHomePile());
					homes.push_back(piles.back());
				}//creating STORAGE
				else if (i == NUM_OF_COLUMNS + NUM_OF_HOMES) {
					piles.push_back(factory.GetStoragePile(cardStack));
					random_shuffle(piles.back()->GetPile().begin(),piles.back()->GetPile().end());
				}//creating TARGET PILE
				else {
					for (int num = 0; num <= i; num++) {
						construct_card_vector(rand() % cardStack.size(), tempVector);
					}
					piles.push_back(factory.GetTargetPile(tempVector));
					tempVector.clear();
				}
			}

		}


		GAME(string path_to_save)
		{
			int pile_counter = 1;
			ifstream ifile;
			ifile.open(path_to_save.c_str());
			if(ifile.fail()){
				throw std::invalid_argument("Can't open file for reading.");
				return;
			}
			char line [200];

			//fill all 12 piles
			while(ifile.getline(line,sizeof(line))){
				stringstream ln;
				ln.str(line);
				char buf[10];
				int temp_shownCards;
				ln.getline(buf,9,',');
				temp_shownCards = atoi(buf);
				vector<card> tempVector {};

				//fill temp vector with cards
				while(ln.getline(buf,9,',')){
					string temp_card {buf};
					cardsuit temp_suit = CLUBS ;
					cardsuit temp_value;
					switch (temp_card[0]) {
						case 'D':
							temp_suit = DIAMONDS;
							break;
						case 'H':
							temp_suit = HEARTS;
							break;
						case 'S':
							temp_suit = SPADES;
							break;
						case 'C':
							temp_suit = CLUBS;
							break;
						default:
							cerr<<"ERROR: Unknown card suit\n";
							break;
					}
					temp_card.erase(0,1);
					temp_value = static_cast<cardsuit>(atoi(temp_card.c_str()));
					tempVector.push_back(card(temp_suit, temp_value));
				}
				if(pile_counter <= NUM_OF_COLUMNS){
					piles.push_back(factory.GetTargetPile(tempVector));
					tempVector.clear();
				}
				else if(pile_counter <= NUM_OF_COLUMNS + NUM_OF_HOMES){
					piles.push_back(factory.GetHomePile(tempVector));
					homes.push_back(piles.back());
					tempVector.clear();
				}
				else{
					piles.push_back(factory.GetStoragePile(tempVector));
					tempVector.clear();
				}

				piles.back()->shownCards = temp_shownCards;

				pile_counter++;
			}
			ifile.close();
		}



	  int MoveCard();
		int MoveCard(solitaire::Command);


	  void RotateStack();


	  void Play();
		void Play(solitaire::Command);

		void Help(int &, int &) const;


		void Save(string);

	  void ShowTable();

		void Backward();

};

}

#endif
