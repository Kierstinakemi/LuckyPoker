/*=============================================================================  
|      Source code:  cardDeck.c (goes with poker.c, hands.c, 
|                           pokerRank.c and testPokerRank.c)
|           Author:  Kierstin Matsuda
|             Date:  October, 31st 2017
|
|    I hereby certify that this collective work is my own
|    and none of it is the work of any other person or entity.
|    ______________________________________ [  Kierstin Matsuda ]
|  
|        Language:  C
|  Compile/Run: The headerfile "pokerGame.h" needs to be in the same directory
|               numCards will default to 5 but is required input
|               numPlayers needs to be between 1 and 7
|     gcc poker.c cardDeck.c hands.c pokerRank.c testPokerRank.c -o play.out -lm
|     ./play.out (numCards) (numPlayers)
|       
|       With the makefile, compile: make BUILD  
|                         run: ./myexec.out (numCards) (numPlayers)
|  +----------------------------------------------------------------------------  
|  
|  Description: Create a deck of cards that can be shuffled and dealt
|                   it will be dealt based on command line arg 2 and 3
|                   two is cards per hand and 3 is number of players,
|                  
|        Input: command-line input, 5, and one number between 1 and 7, validated
|  
|       Output: The original deck, the shuffled deck, each player's hand 
|               printed unsorted, then sorted with the rankings and winners.
|  
|     Process:  User enters input when running program, program validates it
|              creates a deck, shuffles and deals it. pokerRank.c will determine
|               winners and testPokerRank will test everything in pokerRank.c
|  
|  
|   Known Bugs:  None known.
|  *==========================================================================*/
#include <stdio.h>      /*  required for I/O    */
#include <stdlib.h>     /* for rand(), srand() and atoi()*/
#include <math.h>       /* for round() */
#include <time.h>       /* to seed rand */  
#include "pokerGame.h"  /* user defined header for this program */

/*---------------------------- newDeck ----------------------------
        |  function struct card * newDeck(struct card * deck)
        |
        |  Purpose:  new deck requires a pointer for an array of
        |          it will create struct cards using makeCard()
        |           to make a complete deck of cards
        |
        |  @return struct card * - pointer to the deck array
        *-------------------------------------------------------------------*/
struct card * newDeck(struct card * deck)
{
    int suit = DIAMOND; /* first suit starts at 1 */
    int rankCard = RANK_CODE_DIFF; /* start naming ranks at first rank */
    int cardIndex = CARD_ONE; /* start naming cards at 1, ignore deck[0] */

    for (suit = DIAMOND; suit <= SUITS; suit++) //counting suits
    {
        for (rankCard = RANK_CODE_DIFF;
             rankCard <= RANK_CODE;
             rankCard += RANK_CODE_DIFF) // += rank code diff is adding rank
        {
            deck[cardIndex] = makeCard(suit, rankCard);
            cardIndex++;
        }
    }
    return deck;
}

/*---------------------------- makeCard ----------------------------
        |  function struct card makeCard(int suitNum, int ranking)
        |
        |  Purpose:  this method creates a struct card, struct card declaration
        |           is in pokerGame.h
        |
        |  @param int suitNum - a number between 1 and 4
        |  @param int ranking - a number between 1 and 13
        |  @return struct card - returns a struct card
        *-------------------------------------------------------------------*/
struct card makeCard(int suitNum, int ranking)
{
    struct card newCard = {suitNum, ranking};
    return newCard;
}

/*---------------------------- printDeck ----------------------------
        |  function void printDeck(const struct card * deck)
        |
        |  Purpose:  using a for loop, deck is printed via printCard
        |           in a table of 4 by 13, with a legend printed first
        |
        |  @param const struct card * deck-the pointer to the deck to be printed
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void printDeck(const struct card * deck)
{
    int card = CARD_ONE;
    int suitCounter = 0;

    printf("\n%s\n\n", "A = Ace, T = Ten, J = Jack, Q = Queen, K = King");

    for (card = CARD_ONE; card <= DECK; card++)
    {
        printCard(deck[card]);
        suitCounter++;

        if (suitCounter % RANKS == 0)
        {
            printf("\n");
            suitCounter = 0;
        }
    }
}

/*---------------------------- printCard ----------------------------
        |  function void printCard(const struct cardcardCode)
        |
        |  Purpose:  printCard uses sthe suit and rank from the card 
        |           struct and prints it based on the DISP constant arrays
        |
        |  @param double cardCode - the card code to be printed
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void printCard(const struct card singleCard)
{
    int suit = singleCard.suit;
    int rank = singleCard.rank;

    printf("%s%c%s%s\t","[", RANK_DISP[rank], SUIT_DISP[suit], "]"); 
}

/*---------------------------- shuffleDeck ----------------------------
        |  function shuffleDeck(struct card * deck)
        |
        |  Purpose:  shuffle deck uses the modern version of the 
        |           fisher-yates shuffle algorithm found here:
 https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
        |
        |  @param struct card * deck - a pointer of type struct card
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void shuffleDeck(struct card * deck)
{
    int card = CARD_ONE;
    int swapCard = 0;

    /* for each card, generate a random index to swap it with */
    for (card = CARD_ONE; card <= DECK; card++)
    {
        swapCard = CARD_ONE + rand() % DECK;
        swap(deck, card, swapCard);
    }
}

/*---------------------------- swap ----------------------------
        |  function void swap(double *array, int indexOne, int indexTwo)
        |
        |  Purpose:  swaps contents at two indexes in an array 
        |       using the method described in Kernighan and Ritchie's 
        |       "The C Programming Language" In Chapter 5, pg 110 and 95
        |
        |  @param double * array - pointer to array for swapping elements
        |  @param int indexOne - index in array to swap
        |  @param int indexTwo - second index in array to swap with indexOne
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void swap(struct card * array, int indexOne, int indexTwo)
{
    struct card tempCard = makeCard(0,0);

    tempCard = array[indexOne];
    array[indexOne] = array[indexTwo];
    array[indexTwo] = tempCard;
}
