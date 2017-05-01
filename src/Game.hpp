#ifndef GAME_H
#define GAME_H
#include "Card.hpp"
#include "Pile_Factory.hpp"
#include <vector>

using namespace std;
typedef Pile_Interface pile;

const int NUM_OF_CARDS = 52;
const int NUM_OF_COLUMNS = 7;
const int NUM_OF_HOMES = 4;

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


//Slice vector to a vector from pos begin to end of the original one
template<class T>
vector<T> VecSlice(vector<T>, int = 0, int = 0);

class GAME {


public:
	vector <pile *> piles;
	vector<card> cardStack = {};
	Pile_Factory factory;
	vector<pile *> homes;
  GAME() {

		for (int i = 1; i <= K; i++)
		{
			for (int k = CLUBS; k <= SPADES; k = k + 1)
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
  void construct_card_vector(int pos, vector<card>& tempVector);
  int MoveCard();
  void RotateStack();
  void Play();
  void ShowTable();


};

#endif
