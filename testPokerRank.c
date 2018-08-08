/*=============================================================================  
|      Source code:  testPokerRank.c (goes with poker.c, hands.c, 
|                           pokerRank.c and cardDeck.c)
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

/*---------------------------- testRanks ----------------------------
|  function void testRanks()
|
|  Purpose:  This function will test all the functions in pokerRank.c
|               with the help of the helper function
|
|  @return  void - returns nothing
*-------------------------------------------------------------------*/
void testRanks()
{
    printf("\n\n%s\n\n","***************TESTING RANKING SYSTEM***************");
    struct card * testHands[MAX_PLAYERS + PLAYER1];

    /* test Straignt flush */
    struct card test1[] = {makeCard(1, 1),makeCard(1, 2),
                                makeCard(1, 3),makeCard(1, 4),makeCard(1, 5)};
     /* test 4 of a kind  */
    struct card test2[] = {makeCard(1, 1), makeCard(2, 1),
                                makeCard(3, 1),makeCard(4, 1),makeCard(2, 8)};
     /* test full house */
    struct card test3[] = {makeCard(1, 13),makeCard(2, 13),
                             makeCard(3, 13),makeCard(2, 10),makeCard(3, 10)};
     /* test flush */
    struct card test4[] = {makeCard(4, 2),makeCard(4, 6),
                                makeCard(4, 7),makeCard(4, 5),makeCard(4, 10)};
     /* test straight */
    struct card test5[] = {makeCard(1, 2),makeCard(2, 3),
                                makeCard(3, 4),makeCard(1, 5),makeCard(4, 6)};
     /* test three of a kind */
    struct card test6[] = {makeCard(3, 11),makeCard(2, 11),
                                makeCard(1, 11),makeCard(1, 5),makeCard(4, 8)};
     /* testing two Pair */
    struct card test7[] = {makeCard(1, 10),makeCard(3, 10),
                                makeCard(4, 6),makeCard(3, 6),makeCard(1, 13)};
    testHands[PLAYER1] = &test1[0];
    testHands[PLAYER2] = &test2[0];
    testHands[PLAYER3] = &test3[0];
    testHands[PLAYER4] = &test4[0];
    testHands[PLAYER5] = &test5[0];
    testHands[PLAYER6] = &test6[0];
    testHands[PLAYER7] = &test7[0];

    printf("\n\n%s\n","-- Testing ranking system With maximum allowed players. --");
    printf("\n\n%s\n","-- Ace counts as low card --");
    int testRanks[MAX_PLAYERS + PLAYER1];
    setPokerRanks(testHands, testRanks, MAX_PLAYERS);
    printPokerRanks(testHands, testRanks, MAX_PLAYERS);
    testRanksHelper();
}
/*---------------------------- testRanksHelper ----------------------------
|  function void testRanksHelper()
|
|  Purpose:  This function will test all the functions in pokerRank.c
|               that testRanks did not test.
|
|  @return  void - returns nothing
*-------------------------------------------------------------------*/
void testRanksHelper()
{
    printf("\n\n%s\n","-- Testing ranking system with minimum players. --");
    printf("\n\n%s\n","-- Ace counts as high card --");
    /* additional test case for min amount of players and high card 
                                                Ace in straight flush */
    struct card * testHighCard[PLAYER4];
    /* test Straight flush with Ace as high card */
    struct card testingAce[] = {makeCard(1, 1),makeCard(1, 10),
                            makeCard(1, 11),makeCard(1, 12),makeCard(1, 13)};
    /* test test one pair */
    struct card testingPair[] = {makeCard(2, 1),makeCard(3, 1),
                            makeCard(3, 10),makeCard(2, 6),makeCard(1, 3)};
    /* testing High Card */
    struct card testingDefault[] = {makeCard(2, 13),makeCard(3, 11),
                            makeCard(4, 10),makeCard(2, 6),makeCard(1, 3)};
    testHighCard[PLAYER1] = &testingAce[0];
    testHighCard[PLAYER2] = &testingPair[0];
    testHighCard[PLAYER3] = &testingDefault[0];
    int highCardTest[PLAYER4];
    setPokerRanks(testHighCard, highCardTest, PLAYER3);
    printPokerRanks(testHighCard, highCardTest, PLAYER3);
}