/*================================================================
|     Source code: pokerGame.h
|          Author:  Kierstin Matsuda
|            Date:  October, 31st 2017
|
|       I hereby certify that this collective work is my own
|       and none of it is the work of any other person or entity.
|       ______________________________________ [ Kierstin Matsuda ]
================================================================*/
enum boolean {FALSE, TRUE}; /* 0 for False, 1 for true, enum boolean */
enum suits {DIAMOND = 1, HEART, CLUB, SPADE}; /* suit enumeration */
/* assigning players an int, player enum */
enum players {PLAYER1 = 1, PLAYER2, PLAYER3, PLAYER4, PLAYER5, PLAYER6,
        PLAYER7};
/* assigning the non-numerical ranks enum */
enum ranks {ACE = 1, TEN = 10, JACK = 11, QUEEN = 12, KING = 13};
/* assigning the poker ranks numerical values, highest wins */
enum pokerRanks {HIGHCRD = 1, ONEPAIR, TWOPAIR, THR_KIND, STRAIGHT, 
        FLUSH, FULLHOUSE, FR_KIND, STRTFLUSH};

#define NOERROR 0       /* zero for no errrors */
#define ERROR -1        /* -1 error when program doesn't run as it should */
#define NUM_CL_ARGS 3   /* command line arguments needed for this program*/
#define CLARG2 1        /* location in pointer array of argument 2 */
#define CLARG3 2        /* location in pointer array of argument 3 */
#define ARR_ADD 0        /* the location in the array of the array address */

#define DECK 52     /* number of cards in a deck of cards */
#define RANKS 13    /* number of ranks per suit in a deck of cards */
#define SUITS 4     /* number of suits in a deck of cards */
#define CARD_ONE 1  /* card 1 in array starts at index 1 */
#define RANK_CODE 13      /* the coding for the last of the rankings */
#define RANK_CODE_DIFF 1  /* the mathematical difference between card codes */

#define CARDS_INHAND 5      /* max cards in poker */
#define MAX_PLAYERS 7       /* max players in this game */
#define MIN_PLAYERS 1       /* minimum players for program */
#define NEXT 1 /* used in comparisons in arrays */
#define THREEKIND 3 /*THR_KIND for comparisons, different than its enum value*/
#define TWOPAIRS 2 /* TWOPAIR value of actual number of pairs not enum */

#define DIAMOND_SYMB "\xe2\x99\xa2" /* the UTF-8 code for a diamond */
#define HEART_SYMB "\xe2\x99\xa1"   /* the UTF-8 code for a heart */
#define CLUB_SYMB "\xe2\x99\xa0"    /* the UTF-8 code for a club */
#define SPADE_SYMB "\xe2\x99\xa3"   /* the UTF-8 code for a spade */

static const char * SUIT_DISP[] = {" ", 
                        DIAMOND_SYMB, HEART_SYMB, CLUB_SYMB, SPADE_SYMB};
static const char RANK_DISP[] = {' ',
                        'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
static const char * POKER_RANK[] = {"", "a High Card", "One Pair", "Two Pair", 
            "Three of a Kind", "a Straight", "a Flush", 
            "a Full House", "Four of a Kind", "a Straight Flush"};

/* structure for a card, suit between 1 and 4, rank between 1 and 13 */
struct card 
{
    int suit;
    int rank;
};

/* prototypes for functions in poker.c in order of apperarance */
int main (int argc, char * argv[]);
int validateInput(int numArgs, char * args[]);

/* prototypes for functions in cardDeck.c in order of appearance */
struct card * newDeck(struct card * deck);
struct card makeCard(int suitNum,int ranking);
void printDeck(const struct card * deck);
void printCard(const struct card singleCard);
/* functions used to shuffleDeck in cardDeck.c, swap also used to sort Hand */
void shuffleDeck(struct card * deck);
void swap(struct card * array, int indexOne, int indexTwo);

/* prototypes for functions in hands.c in order of appearance */
void printHand(const struct card * hand, int numCards, int player);
void displayHands(struct card *hands[], int cardsInHand, int numPlayers);
void dealHands(struct card * deck, struct card *hands[], int numPlayers, int cardsInHand);
void sortAllHands(struct card *hands[], int cardsInHand, int numPlayers);
void sortHand(struct card * hand, int numCards);

/* prototypes for functions in pokerRanks.c in order of appearance */
void setPokerRanks(struct card *hands[], int ranks[], int numPlayers);
int isStrtFlush(struct card * hand);
int numOfKind(struct card * hand);
int isFullHouse(struct card * hand);
int isFlush(struct card * hand);
int isStraight(struct card * hand);
void printPokerRanks(struct card *hands[], int ranks[], int numPlayers);
void printPokerWinners(struct card *hands[], int ranks[], int numPlayers);

/* prototype for functions in testPokerRank.c in order of appearance */
void testRanks();
void testRanksHelper();