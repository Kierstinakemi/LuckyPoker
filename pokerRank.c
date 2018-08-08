/*=============================================================================  
|      Source code:  pokerRank.c (goes with poker.c, hands.c, 
|                           cardDeck.c and testPokerRank.c)
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
|   Known Bugs:  None known.
|  *==========================================================================*/
#include <stdio.h>      /*  required for I/O   */
#include "pokerGame.h" /*  user defined header for this program    */

/*---------------------------- printHand ----------------------------
        |  function void setPokerRanks(struct card *hand[],int ranks[],int playerNum)
        |
        |  Purpose:  This function will call each of the poker ranks functions
        |           from lowest probability to highest probability, and add
        |            each player's hand's ranking to the ranks array
        |
        |  @param struct card *hand[] - pointer to an array of hands
        |  @param int ranks[] - an array to store players ranks in
        |  @param int numPlayers - how many players in the game
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void setPokerRanks(struct card *hands[],int ranks[], int numPlayers)
{
    int player = PLAYER1;
    int cardIndex = CARD_ONE;
    struct card * playerHand;

    /* start at player 1 because no 0th player */
    for (player = PLAYER1; player <= numPlayers; player++)
    {
        playerHand = hands[player];
        /* checking poker rankings from lowest probablility to highest */
        if (isStrtFlush(playerHand)) { ranks[player] = STRTFLUSH; }
        else if (numOfKind(playerHand) == FR_KIND) { ranks[player] = FR_KIND; }
        else if (isFullHouse(playerHand)) { ranks[player] = FULLHOUSE; }
        else if (isFlush(playerHand)) { ranks[player] = FLUSH; }
        else if (isStraight(playerHand)) { ranks[player] = STRAIGHT; }
        else if (numOfKind(playerHand) == THR_KIND){ ranks[player] = THR_KIND;}
        else if (numOfKind(playerHand) == TWOPAIR) { ranks[player] = TWOPAIR; }
        else if (numOfKind(playerHand) == ONEPAIR) { ranks[player] = ONEPAIR; }
        else { ranks[player] = HIGHCRD; /* default is high card */ }
    }
}
/*---------------------------- isStrtFlush ----------------------------
        |  function int isStrtFlush(struct card * hand)
        |
        |  Purpose:  This function checks if the hand is both flush and straight
        |               which makes it a straight flush
        |
        |  @param struct card * hand - array of cards sorted
        |  @return  void - returns TRUE or FALSE, TRUE if StraightFlush
        *-------------------------------------------------------------------*/
int isStrtFlush(struct card * hand)
{
    if (isFlush(hand) && isStraight(hand))
    {
        return TRUE;
    }
    else { return FALSE; }
}
/*---------------------------- isFlush ----------------------------
        |  function int isFlush (struct card * hand)
        |
        |  Purpose:  This function determines how many cards of the same
        |           rank there are in this hand, can determine two pair as well
        |
        |  @param struct card * hand - array of cards sorted
        |  @return  int - returns TWOPAIR, FR_KIND, THR_KIND or ONEPAIR
        *-------------------------------------------------------------------*/
int numOfKind(struct card * hand)
{
    int card = 0;
    int sameKind = CARD_ONE;
    int mostKind = CARD_ONE;
    int pairCounter = 0;

    for (card = 0; card < CARDS_INHAND; card++)
    {
        if (hand[card].rank == hand[card + NEXT].rank) { sameKind++; }
        else 
        { 
            if (sameKind == ONEPAIR) 
            { 
                pairCounter++; 
            }
            if (mostKind < sameKind) { mostKind = sameKind; }
            sameKind = CARD_ONE; 
        }
    }
    if (mostKind < sameKind) { mostKind = sameKind; }
    /* returns code of how many of a kind this card array has */
    if (pairCounter == (TWOPAIRS) ) { return TWOPAIR; }
    else if (mostKind > THREEKIND) { return FR_KIND; }
    else if (mostKind == THREEKIND) {return THR_KIND; }
    else if (mostKind == ONEPAIR) {return ONEPAIR; }
    return FALSE;
}
/*---------------------------- isFullHouse ----------------------------
        |  function int isFullHouse (struct card * hand)
        |
        |  Purpose:  This function checks for 3 cards of same rank, plus
        |       two cards of a different rank. If the hand has 3 of a kind
        |       and the first two cards are the same rank, as well as the
        |       last two cards are the same rank, it is a Full HOuse
        |
        |  @param struct card * hand - the array of cards sorted
        |  @return  void - returns TRUE or FALSE, TRUE if is Full House
        *-------------------------------------------------------------------*/
int isFullHouse(struct card * hand)
{
    if (numOfKind(hand) == THR_KIND)
    {
        /* if both ends of hand has two cards of same rank it is full house */
        if ( (hand[CARD_ONE - NEXT].rank == hand[CARD_ONE].rank) 
                        && (hand[3].rank == hand[4].rank) )
        {
            return TRUE;
        }
    }
    return FALSE;
}
/*---------------------------- isFlush ----------------------------
        |  function int isFlush (struct card * hand)
        |
        |  Purpose:  This function checks for 5 cards of the same suit
        |
        |  @param struct card * hand - the array of cards sorted
        |  @return  void - returns TRUE or FALSE, TRUE if Flush
        *-------------------------------------------------------------------*/
int isFlush(struct card * hand)
{
    int card = 0;
    int sameSuit = CARD_ONE;

    for (card = 0; card < CARDS_INHAND; card++)
    {
        if (hand[card].suit == hand[card + NEXT].suit)
        {
            sameSuit++;
            if (sameSuit == CARDS_INHAND) { return TRUE; }
        }
        else { sameSuit = CARD_ONE; }
    }
    return FALSE;
}
/*---------------------------- isStraight ----------------------------
        |  function int isFlush (struct card * hand)
        |
        |  Purpose:  This function tests for 5 cards in a row, Ace can count
        |         for low card or high card, ATJQK and A2345 are both straight
        |
        |  @param struct card * hand - the array of cards sorted
        |  @return  void - returns TRUE or FALSE, TRUE if Straight
        *-------------------------------------------------------------------*/
int isStraight(struct card * hand) 
{
    int card = 0;
    int countAce = FALSE;
    int straight = CARD_ONE;

    /* testing for special case of Ace as high card, not as "1" */
    if (hand[card].rank == ACE && hand[card + NEXT].rank == TEN)
    {
        straight++;
        countAce = TRUE;
    }
    /* card will start at 0 if Ace was not bottom card it will start at CARD_ONE
    if ace was found to be the first card, it will count as low and high card*/
    for (card = countAce; card < CARDS_INHAND; card++)
    {
        if (hand[card].rank == ( (hand[card + NEXT].rank) - NEXT ))
        {
            straight++;
            if (straight == CARDS_INHAND) { return TRUE; }
        }
        else { return FALSE; }
    }
    return FALSE;
}
/*---------------------------- printPokerRanks ----------------------------
        |  function void printPokerRanks(struct card *hands[],int ranks[],int playerNum)
        |
        |  Purpose:  This function will print all the poker ranks and hands
        |           using the printHand function and the POKER_RANK array
        |
        |  @param struct card *hands[] - pointer to an array of hands of cards
        |  @param int ranks[] - how many cards are in the array
        |  @param int playerNum - the number of players in the game
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void printPokerRanks(struct card *hands[], int ranks[], int numPlayers)
{
    int player = PLAYER1;
    struct card * playerHand;

    /* start at player 1 because no 0th player */
    for (player = PLAYER1; player <= numPlayers; player++)
    {
        playerHand = hands[player];
        printf("\n\n%s%d%s%s%s\n","Player ", player, " you got ",
                             POKER_RANK[ranks[player]], ".");
        printHand(playerHand, CARDS_INHAND, player);
    }
}
/*---------------------------- printPokerWinners----------------------------
        |  function void printHand(struct card *hands[],int ranks[],int playerNum)
        |
        |  Purpose:  This function will find the highest ranking in the 
        |           ranks array, then print all players who had that ranking
        |
        |  @param struct card *hands[] - pointer to an array of hands of cards
        |  @param int ranks[] - the array of player rankings 
        |  @param int playerNum - how many players in the game
        |  @return  void - returns nothing
        *-------------------------------------------------------------------*/
void printPokerWinners(struct card *hands[], int ranks[], int numPlayers)
{
    int player = PLAYER1;
    int pokerRank = STRTFLUSH;
    int highestRank = HIGHCRD;

    /* finding highest rank in the array of ranks */
    for (pokerRank = STRTFLUSH; pokerRank >= HIGHCRD; pokerRank--)
    {
        for (player = PLAYER1; player <= numPlayers; player++)
        {
            if (ranks[player] == pokerRank && highestRank < pokerRank)
            {
                highestRank = pokerRank;
            }
        }
    }
    /* printing all players with the highest rank found in the previous loop */
    for (player = PLAYER1; player <= numPlayers; player++)
    {
        if (ranks[player] == highestRank)
        {
            printf("\n%s%d%s", "Player ", player, " wins with ");
            printf("%s\n", POKER_RANK[ranks[player]]);
        }
    }
}
