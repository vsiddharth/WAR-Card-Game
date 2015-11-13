/* WAR: A simple card game
 * author: vsiddharth
 */

#include <iostream>
#include <algorithm>

using namespace std;

enum suits {spade, club, diamond, heart};

class Card {
    public:
        Card();
        Card(suits, int);

        int rank;
        suits suit;
};

Card::Card()
{
    rank = 1;
    suit = spade;
}

Card::Card(suits s, int r)
{
    suit = s;
    rank = r;
}

ostream& operator << (ostream &out, Card &c)
{
    switch(c.rank) {
        case 1:
            out << "Ace";
            break;
        case 11:
            out << "Jack";
            break;
        case 12:
            out << "Queen";
            break;
        case 13:
            out << "King";
            break;
        default:
            out << c.rank;
            break;
    }

    switch(c.suit) {
        case spade:
            out << " of Spades";
            break;
        case club:
            out << " of Clubs";
            break;
        case diamond:
            out << " of Diamonds";
            break;
        case heart:
            out << " of Hearts";
            break;
    }
    return out;
}


class randomInt {
    public:
        unsigned int operator () (unsigned int max)
        {
            unsigned int rval = rand();
            return rval % max;
        }
};

randomInt randomizer;


class Deck {
    public:
        Deck();
        void shuffle();
        bool isEmpty();
        Card draw();

    protected:
        Card cards[52];
        int topCard;
};

Deck::Deck()
{
    topCard = 0;
    for (int i = 1; i <= 13; i++) {
        Card c1(spade, i);
        Card c2(club, i);
        Card c3(diamond, i);
        Card c4(heart, i);
        cards[topCard++] = c1;
        cards[topCard++] = c2;
        cards[topCard++] = c3;
        cards[topCard++] = c4;
    }
}

void Deck::shuffle()
{
    random_shuffle(cards, cards+52, randomizer);
}

bool Deck::isEmpty()
{
    return topCard <= 0;
}

Card Deck::draw()
{
    if (!isEmpty()) {
        return cards[--topCard];
    }
    else {
        Card spadeAce(spade, 1);
        return spadeAce;
    }
}


class Player {
    public:
        Player (Deck&);

        Card draw();
        void addPoints(int);
        int score();
        void replaceCard (Deck&);

    protected:
        Card myCards[3];
        int myScore;
        int removedCard;
};

Player::Player (Deck &d)
{
    myScore = 0;
    for (int i = 0; i < 3; i++) {
        myCards[i] = d.draw();
    }
    removedCard = 0;
}

Card Player::draw()
{
    removedCard = randomizer(3);
    return myCards[removedCard];
}


void Player::addPoints(int p)
{
    myScore += p;
}

int Player::score()
{
    return myScore;
}

void Player::replaceCard (Deck &d)
{
    myCards[removedCard] = d.draw();
}


int main(int argc, char **argv)
{
    Deck d;
    d.shuffle();

    Player p1(d);
    Player p2(d);

    while (! d.isEmpty()) {
        Card c1 = p1.draw();
        cout << "Player 1 plays " << c1 << endl;
        Card c2 = p2.draw();
        cout << "Player 2 plays " << c2 << endl;

        if (c1.rank == c2.rank) {
            p1.addPoints(1);
            p2.addPoints(1);
            cout << "Players Tie " << endl;
        }
        else if (c1.rank > c2.rank) {
            p1.addPoints(2);
            cout << "Player 1 wins round" << endl;
        }
        else {
            p2.addPoints(2);
            cout << "Player 2 wins round" << endl;
        }

        p1.replaceCard(d);
        p2.replaceCard(d);
    }

    cout << "\n\n ===> Final Scores: " << endl;
    cout << "Player 1: " << p1.score () << endl;
    cout << "Player 2: " << p2.score () << endl;

    return 0;
}
