#include <stdio.h>
#include "stdlib.h"
#include <time.h>

#define MAX_CARDS 52
#define RESHUFFLE_NUMBER 0
#define BLACKJACK 21
#define DEALER_HIT_THRESHOLD 17

typedef struct {
    int rank;
    char suit;
} Card;

typedef struct {
    Card *cards;
    int size;
} Deck;

typedef struct {
    Card card;
    Deck deck;
} CardAndDeck;

typedef struct {
    float money;
    float winningThreshold;
    float currentBet;
} Game;

Deck resetDeck() {
    Deck deck;

    deck.size = 52;

    const char suits[] = {'H', 'D', 'C', 'S'};
    const int ranks[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            deck.cards[index].suit = suits[i];
            deck.cards[index].rank = ranks[j];
            index++;
        }
    }

    return deck;
}

CardAndDeck randCard(Deck deck)
{
    int randIndex = rand() % deck.size;
    Card card = deck.cards[randIndex];

    deck.cards[randIndex] = deck.cards[deck.size - 1];

    deck.size--;

    CardAndDeck ret = {card, deck};

    return ret;
}

int calcHandTotal(Deck deck)
{
    int sum = 0;
    int i = 0;

    while (deck.cards[i].rank != 0)
    {
        sum += deck.cards[i].rank;
        i++;
    }

    return sum;
}

int main()
{
    srand(time(NULL));

    float startingMoney;
    float winningThreshold;

    char input[100];

    system("@cls||clear");

    printf("Enter the starting money: ");
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%f", &startingMoney) != 1)
    {
        const char defaultStartingMoney[] = "99.99";
        sscanf(defaultStartingMoney, "%f", &startingMoney);
    };

    printf("Enter the winning threshold: ");
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%f", &winningThreshold) != 1)
    {
        const char defaultWinningThreshold[] = "10000.00";
        sscanf(defaultWinningThreshold, "%f", &startingMoney);
    };

    Game game = {startingMoney, winningThreshold, 0};

    Deck deck = resetDeck();

    while (game.money > 0 && game.money < game.winningThreshold)
    {
        Deck comHand;
        Deck myHand;

        if (deck.size == RESHUFFLE_NUMBER)
        {
            deck = resetDeck();
        }

        CardAndDeck temp = randCard(deck);
        comHand.cards[comHand.size] = temp.card;
        deck = temp.deck;

        if (deck.size == RESHUFFLE_NUMBER) {
            deck = resetDeck();
        }

        temp = randCard(deck);
        myHand.cards[myHand.size] = temp.card;
        deck = temp.deck;

        if (deck.size == RESHUFFLE_NUMBER) {
            deck = resetDeck();
        }

        temp = randCard(deck);
        comHand.cards[comHand.size] = temp.card;
        deck = temp.deck;

        if (deck.size == RESHUFFLE_NUMBER) {
            deck = resetDeck();
        }

        temp = randCard(deck);
        myHand.cards[myHand.size] = temp.card;
        deck = temp.deck;

        printf("%d", 3);

        printf("Your total: %d\n", calcHandTotal(myHand));

        printf("%c", 'C');

        break;
    }

    return 0;
}