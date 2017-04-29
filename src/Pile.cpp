#include "Pile.hpp"



pile::pile(std::vector<card>& vec)
{
	for (card cd : vec)
	{
		this->cards.push_back(cd);
		this->size++;
	}
}

pile::pile() {

	this->shownCards = 0;
}


pile::~pile()
{
}


void pile::AddCard(card& cd, int flags)
{
	//std::cout<< "first card:" << (this->shownCards.front()).getSuit() << " " << (this->shownCards.front()).getValue() << "\n";
	//std::cout << "pushing card:" << cd.getSuit() << " " << cd.getValue() << "\n";
	this->cards.push_back(cd);
	this->shownCards++;
	if (flags & INSERT_ONLY) this->shownCards--;
	this->size++;
}


void pile::AddCard(std::vector<card> cd_vec, int flags)
{
	//std::cout<< "first card:" << (this->shownCards.front()).getSuit() << " " << (this->shownCards.front()).getValue() << "\n";
	//std::cout << "pushing card:" << cd.getSuit() << " " << cd.getValue() << "\n";
	for (auto iter = cd_vec.rbegin();iter != cd_vec.rend();iter++ ) {
		this->cards.push_back(*iter);
		this->shownCards++;
		if (flags & INSERT_ONLY) this->shownCards--;
		this->size++;
	}
}

card& pile::PopCard()
{
	if (!this->IsEmpty())
	{
		card& temp = this->cards.back();
		this->cards.pop_back();
		this->size--;
		if (this->shownCards > 1 || this->size == 0)
		{
			this->shownCards--;
		}
		return temp;
	}
	else
	{
		std::cerr << "Error: pile is empty, can't POP card\n";
		exit(-1);
	}
}
