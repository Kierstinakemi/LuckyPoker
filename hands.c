/*=============================================================================  
|      Source code:  hands.c (goes with poker.c, cardDeck.c, 
|                           pokerRank.c and testPokerRank.c)
|           Author:  Kierstin Matsuda
|             Date:  October, 31st 2017
|
|    I hereby certify that this collective work is my own
|    and none of it is the work of any other person or entity.
|    ______________________________________ [ Kierstin Matsuda ]
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
#include <stdio.h>      /*  required for I/O   */
#include "pokerGame.h" /*  user defined header for this program    */

/*---------------------------- printHand ----------------------------
        |  function void printHand(const struct card hand,int numCards,int playerNum)
        |
        |  Purpose:  This function takes a pointer type double to an array
        |           how many cards are in the array and the player number
        |           and prints the cards using printCard
        |
        |  @param const struct card * hand - pointer to an array of cards
        |  @param int numCards - how many cards are in the array
        |  @param int playerNum - the player whos hand it is
        |  @return void - returns nothing
        *-------------------------------------------------------------------*/
void printHand(const struct card * hand, int numCards, int playerNum)
{
    printf("\n%s%d%s\n\n", "Player ", playerNum, " here is your hand.");
    int card = 0;

    for (card = 0; card < numCards; card++)
    {
        printCard(hand[card]);
    }
    printf("\n\n");
}
/*---------------------------- printHand ----------------------------
        |  function void printHand(struct card *hands[],int numCards,int playerNum)
        |
        |  Purpose: This function will print each hand of cards using printHand()
        |
        |  @param struct card *hands[] -pointer to an array of pointers to hands
        |  @param int numCards - how many cards are in the array
        |  @param int playerNum - the player whos hand it is
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void displayHands(struct card *hands[], int cardsInHand, int numPlayers)
{
    int player = PLAYER1;
    struct card * playerHand;

    for (player = PLAYER1; player <= numPlayers; player++)
    {
        playerHand = hands[player];
        printHand(playerHand, cardsInHand, player);
    }
}

/*---------------------------- dealHands ----------------------------
        | function void dealHands(struct card *deck,
        |                 struct card *hands[],int cardsInHand, int numPlayers)
        |
        |  Purpose:  This function assumes input has been validated for
        |           0 < numPlayers <= 7, cardsInHand = 5 
        |           it will deal cards to one player at a time and put it
        |           in a an array whos pointer is in an array of hands
        |
        |  @param struct card * deck - pointer to deck array of cards
        |  @param struct card *hands[] - array of pointers to arrays of hands
        |  @param int cardsInHand - how many cards to be dealt per player
        |  @param int numPlayers - how many players to be dealt
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void dealHands(struct card * deck, struct card *hands[], int cardsInHand, int numPlayers)
{
    int cards = 0;
    int player = PLAYER1;
    int cardIndex = CARD_ONE;
    struct card * playerHand;

    /* start at player 1 because no 0th player */
    for (player = PLAYER1; player <= numPlayers; player++)
    {
        playerHand = hands[player];

        for (cards = 0; cards < cardsInHand; cards++)
        {
            playerHand[cards] = deck[cardIndex];
            cardIndex++;
        }
    }
}
/*---------------------------- sortAllHands----------------------------
        |  function void sortAllHands(struct card *hands[],int numCards,int playerNum)
        |
        |  Purpose:  This function will pass individual hands to sortHand()
        |
        |  @param struct card *hands[] -pointer to an array of pointers to hands
        |  @param int numCards - how many cards are in the array
        |  @param int playerNum - the player whos hand it is
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void sortAllHands(struct card *hands[], int cardsInHand, int numPlayers)
{
    int player = PLAYER1;
    struct card * playerHand;

    for (player = PLAYER1; player <= numPlayers; player++)
    {
        playerHand = hands[player];
        sortHand(playerHand, cardsInHand);
    }
}

/*---------------------------- sortHand ----------------------------
        |  function void printHand(struct card *hand, int numCards)
        |
        |  Purpose:  This function uses the bubble sort algorithm found in
        |           Dietel and Dietel's "C How to Program" on page 293
        |           to sort an array of struct cards from lowest to highest rank
        |
        |  @param struct card * hand - pointer to an array of cards
        |  @param int numCards - how many cards are in the array
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void sortHand(struct card * hand, int numCards)
{
    int card = 0;
    int pass = 0;

    for (pass = 0; pass < numCards - NEXT; pass++)
    {
        for (card = 0; card < numCards - NEXT; card++)
        {
            if (hand[card].rank > hand[card + NEXT].rank)
            {
                swap(hand, card, card + NEXT);
            }
        }
    }
}