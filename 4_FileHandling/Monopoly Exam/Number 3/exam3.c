#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Title Deed structure
typedef struct {
	int id;
	char name[20];
	char color[20];
	double amount[9]; 			// rent lot but empty, 1, 2, 3, 4, hotel, mortgage, house cost, hotel cost (house cost * 5) 
	int houseCount;				// will be used only if players owns already the property
	int hotelCount;				// will be used only if players owns already the property
	int mortgage;				// will be used only if players owns already the property and value is 1 - under mortgage, 0 - not in mortgage 
} TitleDeed;

typedef struct {
	char cardType[20];
	char cardDescription[100];
} Card, Cards[16];

// Used to store Title Deeds in a linkled list 
typedef struct prop {
	TitleDeed lot;
	struct prop *next;
} Prop, *PropLList, *SortedPropLList;

// Used to store Title Deeds in an array list 
typedef struct {
	TitleDeed *lot;
	int count;
	int max;
} PropAList, SortedPropAList;

// Player structure
typedef struct {
	int id;
	SortedPropLList owned;		// initially empty but insertSorted when adding ownership to a title deed based on id
	int moneyCount[7];			// 2pcs-$500, 2pcs-$100, 2pcs-$50, 6pcs-$20, 5pcs-$10, 5pcs-$5, 5pcs-$1
	double totalMoney;			// $1500
	int position;				// current position in board starts at 0
} Player;

// GameBoard structure
typedef struct {
	PropLList ownedBank;		// the collection of title deeds not yet owned by a player
	int boardLot[40];			// compromises the lot area
	int moneyCount[7];			// 30pcs-$500, 30pcs-$100, 30pcs-$50, 30pcs-$20, 30pcs-$10, 30pcs-$5, 30pcs-$1
	double totalMoney;			// $20580
	Player players[8];			// players of the game
	int playerCount;			// current count of players
	int houseCount;				// 32 houses
	int hotelCount;				// 12 hotels
	Cards chance;				// chance cards
	int currChanceTop;			// initially starts at 0 then moves once the player lands a chance lot
	Cards communityChest;		// commmunity chest cards
	int currCommunityChestTop;	// initially starts at 0 then moves once the player lands a community chest lot
	int dice[2];				// will contain the dice values (0 for the dice 1 and 1 for dice 2)
} GameBoard;

//	> 0 special(-1 community chest, -2 chance, -3 free parking, -4 income tax, -5 jail, -6 electric company, -7 water works, -8 road 1, -9 road 2, -10 road 3, -11 road 4, -12)
//  0 owned by bank, id of the player if lot is owned by a player
//  initial value of board lot 0, *0, -1, *0, -4, -8, !0, -2, !0, !0, -5, *0, -6, *0, *0, -9, !0, -1, !0, !0, -3, *0, -2, *0, *0, -10, !0, !0, -7, !0, -12, *0, *0, -1, *0, -11, -2, !0, -4, !0

// must implement
bool acquireProperty(GameBoard * board, int player_id, int property_id);

// place the other function prototypes needed
void adjustBank(GameBoard *board, PropLList *property, int playerIndex, int property_id);
void adjustMoneyBetweenPlayers(GameBoard *board, float price, int player1Index, int player2Index);
void adjustMoneyCounterBank(GameBoard *board, float price, int playerIndex);
PropLList *propertyInBank(GameBoard *board, int property_id);
PropLList *propertyInSelf(GameBoard *board, int playerIndex, int property_id);
PropLList *propertyInOthers(GameBoard *board, int property_id, int *otherIndex);
int findPlayer(GameBoard *board, int player_id);

int main(int argc, char *argv[]) {
	GameBoard board;
	acquireProperty(&board, 1, 1);

	return 0;
}

bool acquireProperty(GameBoard * board, int player_id, int property_id) {
	
	int playerIndex = findPlayer(board, player_id);
	int otherIndex = -1;
	PropLList* property = propertyInBank(board, property_id);
	PropLList* selfOwned = propertyInSelf(board, playerIndex, property_id);
	PropLList* diffOwned = propertyInOthers(board, property_id, &otherIndex);

	//if in bank
	if((*property) != NULL &&
		board->players[playerIndex].totalMoney >= (*property)->lot.amount[0]
	) {
		adjustBank(board, property, playerIndex, property_id);
	}
	else if((*selfOwned) != NULL) {
		if((*selfOwned)->lot.houseCount < 4 &&
			board->players[playerIndex].totalMoney >= (*selfOwned)->lot.amount[7]
		) {
			float price = (*selfOwned)->lot.amount[7];

			//update total money
			board->players[playerIndex].totalMoney -= price;
			board->totalMoney += price;

			//update house count
			(*selfOwned)->lot.houseCount++;
			board->houseCount--;

			//update money count
			adjustMoneyCounterBank(board, price, playerIndex);
		}
		else if(board->players[playerIndex].totalMoney >= (*selfOwned)->lot.amount[8]) {

			float price = (*selfOwned)->lot.amount[8];

			//adjust total money
			board->players[playerIndex].totalMoney -= price;
			board->totalMoney += price;

			//adjust house and hotel counters
			(*selfOwned)->lot.houseCount -= 4;
			(*selfOwned)->lot.hotelCount++;
			board->houseCount += 4;
			board->hotelCount--;

			adjustMoneyCounterBank(board, price, playerIndex);
		}
	}
	else if((*diffOwned) != NULL) {
		float price = 0;
		int house = (*selfOwned)->lot.houseCount;
		int hotel = (*selfOwned)->lot.hotelCount;

		int amountIndex = (hotel == 1) ? hotel : house;

		price = (*selfOwned)->lot.amount[amountIndex] * 3;

		if(board->players[otherIndex].totalMoney >= price) {
			adjustMoneyBetweenPlayers(board, price, playerIndex, otherIndex);

			//delete from other players list
			PropLList temp = (*diffOwned);
			(*diffOwned) = (*diffOwned)->next;

			//add to current players list
			SortedPropLList *trav;
			for(trav = &board->players[playerIndex].owned; (*trav) != NULL && property_id > (*trav)->lot.id; trav = &(*trav)->next) {}

			//inserted 
			temp->next = (*trav);
			(*trav) = temp;
		}

	}
	else {
		return false;
	}
	return true;
}

void adjustBank(GameBoard *board, PropLList *property, int playerIndex, int property_id) {
	//copy to new LList
	PropLList insert = (*property);

	//traverse
	SortedPropLList *trav;
	for(trav = &board->players[playerIndex].owned; (*trav) != NULL && (*trav)->lot.id > property_id; trav = &(*trav)->next) {}

	//insert sorted to players owned
	insert->next = (*trav);
	(*trav) = insert;

	//delete from bank
	(*property) = (*property)->next;

	//update total money
	float price = (*property)->lot.amount[0];

	board->players[playerIndex].totalMoney -= price;
	board->totalMoney += price;

	//adjust counters
	adjustMoneyCounterBank(board, price, playerIndex);
}

void adjustMoneyBetweenPlayers(GameBoard *board, float price, int player1Index, int player2Index) {
	int change = 0;
	int prices[7] = {500, 100, 50, 20, 10, 5, 1};

	int i = 0;
	while(price > 0) {
		while(board->players[player1Index].moneyCount[i] > 0) {

			price -= prices[i];
			board->players[player1Index].moneyCount[i]--;
			board->players[player2Index].moneyCount[i]++;

			if(price < 0) {
				change -= price;
				price = 0;
			}

		}
		i++;
	}

	//supply change if necessary
	i = 0;
	while(change > 0) {
		if(change < prices[i]) {
			i++;
		}
		else {
			change -= prices[i];
			board->players[player2Index].moneyCount[i]--;
			board->players[player1Index].moneyCount[i]++;
		}
	}
}

void adjustMoneyCounterBank(GameBoard *board, float price, int playerIndex) {
	int change = 0;
	int prices[7] = {500, 100, 50, 20, 10, 5, 1};

	int i = 0;
	while(price > 0) {
		while(board->players[playerIndex].moneyCount[i] > 0) {

			price -= prices[i];
			board->players[playerIndex].moneyCount[i]--;
			board->moneyCount[i]++;

			if(price < 0) {
				change -= price;
				price = 0;
			}

		}
		i++;
	}

	//supply change if necessary
	i = 0;
	while(change > 0) {
		if(change < prices[i]) {
			i++;
		}
		else {
			change -= prices[i];
			board->moneyCount[i]--;
			board->players[playerIndex].moneyCount[i]++;
		}
	}
}

PropLList *propertyInBank(GameBoard *board, int property_id) {
	PropLList *curr;

	//find property
	for(curr = &board->ownedBank; (*curr) != NULL && (*curr)->lot.id != property_id; curr = &(*curr)->next) {}

	return curr;
}

PropLList *propertyInSelf(GameBoard *board, int playerIndex, int property_id) {
	PropLList *curr;

	//find property
	for(curr = &board->players[playerIndex].owned; (*curr) != NULL && (*curr)->lot.id != property_id; curr = &(*curr)->next) {}

	return curr;
}

PropLList *propertyInOthers(GameBoard *board, int property_id, int *otherIndex) {
	PropLList *curr = NULL;

	for(int i = 0; i < board->playerCount; i++) {
		for(curr = &board->players[i].owned; (*curr) != NULL && (*curr)->lot.id != property_id; curr = &(*curr)->next) {}
		if((*curr) != NULL) {
			*otherIndex = i;
			break;
		}
	}

	return curr;
}

//returns index of player
int findPlayer(GameBoard *board, int player_id) {
	Player main;

	//find current player
	int i;
	for(i = 0; i < board->playerCount && player_id != board->players[i].id; i++) {}

	return (i < board->playerCount) ? i : -1;
}