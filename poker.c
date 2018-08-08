/*=============================================================================  
|      Source code:  poker.c (goes with cardDeck.c, hands.c, 
|                           pokerRank.c and testPokerRank.c)
|           Author:  Kierstin Matsuda
|         Due Date:  October, 31st 2017
|
|    I hereby certify that this collective work is my own
|    and none of it is the work of any other person or entity.
|    ______________________________________ [  Kierstin Matsuda   ]
|  
|        Language:  C
|  Compile/Run: The headerfile "pokerGame.h" needs to be in the same directory
|               numCards will default to 5 but is required input
|               numPlayers needs to be between 1 and 7

|     gcc poker.c cardDeck.c hands.c pokerRank.c testPokerRank.c -o play.out -lm
|     ./play.out (numCards) (numPlayers)
|       
|  With the makefile, compile: make BUILD  
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
#include <time.h>       /* to seed rand() */
#include "pokerGame.h"  /*  user defined header for this program    */

/*---------------------------- main ----------------------------
        |  function main (int argc, char *argv[])
        |
        |  Purpose: call functions in cardDeck.c, create hands using hands.c
        |           determining their rankings and winners by pokerRank.c
        |           calling testPokerRank.c functions to test pokerRank.c
        |
        |  @param int argc - how many command line arguments
        |  @param char * argv - a array of pointers to arrays of chars
        |  @return  int  -- NOERROR, 0 returned when program terminates normally
        *-------------------------------------------------------------------*/
int main (int argc, char * argv[])
{
    /* if the command line input is valid, continue, else, return */
    if (validateInput(argc, argv) == TRUE)
    {
        int numPlayers = atoi((argv)[CLARG3]);
        int numCards = CARDS_INHAND;
        /* creating card deck and pointer */
        struct card deck[DECK + CARD_ONE];
        struct card * deckPtr = &deck[ARR_ADD];
        printf("\n%s\n", "Here is the original, unshuffled deck:");
        printDeck(newDeck(deckPtr));

        /* randomize random num generator using current time
                    shuffling and printing card deck */
        srand((unsigned)time(NULL));
        shuffleDeck(deckPtr);
        printf("\n%s\n", "Here is the shuffled, undealt deck:");
        printDeck(deckPtr);
        /* creating an array to hold pointers to arrays of hands */
        struct card * hand[numPlayers + PLAYER1];
        /* creating player hands up to max players */
        struct card player1[numCards + CARD_ONE];
        struct card player2[numCards + CARD_ONE];
        struct card player3[numCards + CARD_ONE];
        struct card player4[numCards + CARD_ONE];
        struct card player5[numCards + CARD_ONE];
        struct card player6[numCards + CARD_ONE];
        struct card player7[numCards + CARD_ONE];
        /* putting the addresses of the player hands in the hands array */
        hand[PLAYER1] = &player1[ARR_ADD];
        hand[PLAYER2] = &player2[ARR_ADD];
        hand[PLAYER3] = &player3[ARR_ADD];
        hand[PLAYER4] = &player4[ARR_ADD];
        hand[PLAYER5] = &player5[ARR_ADD];
        hand[PLAYER6] = &player6[ARR_ADD];
        hand[PLAYER7] = &player7[ARR_ADD];

        /* sending validated command-line args as numCards and numPlayers */
        dealHands(deckPtr, hand, numCards, numPlayers);
        displayHands(hand, numCards, numPlayers);
        sortAllHands(hand, numCards, numPlayers);
       
        printf("\n%s\n\n", "-- Players, here are your sorted, ranked hands --");
        int playerRanks[numPlayers + PLAYER1];
        setPokerRanks(hand, playerRanks, numPlayers);
        printPokerRanks(hand, playerRanks, numPlayers);
        printPokerWinners(hand, playerRanks, numPlayers);
        /* testing functions in pokerRank.c */
        testRanks();
    }
    else 
    {
        printf("\n%s\n\n", "Please run the program again.");
        return ERROR;
    }
    return NOERROR;
}

/*---------------------------- validateInput ----------------------------
        |  function int validateInput(int numArgs, char * args[])
        |
        |  Purpose:  checks that command line arg 2 and 3 are integers
        |           CLARG2 is defaulted to 5, and CLARG3 is between 1-7
        |           using atof and atoi checks for validity of input
        |
        |  @return  int  -- TRUE if valid input else FALSE
        *-------------------------------------------------------------------*/
int validateInput(int numArgs, char * args[])
{
    int cardPerHand = CARDS_INHAND;
    int numHands = MIN_PLAYERS;

    if (numArgs != NUM_CL_ARGS) { return FALSE; }
    if (cardPerHand != atoi((args)[CLARG2]) ) 
    {
        printf("\n%s\n", "Defaulting to 5 cards per hand.");
    }
    /* check if user input chars - atoi will return false */
    if ( (numHands = atoi((args)[CLARG3])) != FALSE) 
    {
        /* check if user input decimal - compare atoi's int to atof's double */
        if ((double)numHands == atof(args[CLARG3]))
        {
            if (cardPerHand == CARDS_INHAND && numHands <= MAX_PLAYERS 
                                            && numHands >= MIN_PLAYERS)
            {
                return TRUE; 
            }
        }
    }
    else { return FALSE; }
return FALSE;
}
