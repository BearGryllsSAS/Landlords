#ifndef CARD_H
#define CARD_H

/* 单张卡牌类 */

#include <QVector>

class Card
{
public:
    // 花色
    enum CardSuit
    {
        Suit_Begin,
        Diamond,
        Club,
        Heart,
        Spade,
        Suit_End
    };
    // 点数
    enum CardPoint
    {
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,     // small joker
        Card_BJ,     // big joker
        Card_End
    };

    Card();
    Card(CardPoint point, CardSuit suit);

    void setPoint(CardPoint point);
    void setSuit(CardSuit suit);
    CardPoint point() const;
    CardSuit suit() const;

private:
    CardPoint m_point;
    CardSuit m_suit;
};

// 定义类型的别名，多张卡牌类中用到，方便对扑克牌排序
using CardList = QVector<Card>;

// 对象比较,用于对多张扑克牌进行排序
bool lessSort(const Card& c1, const Card& c2);
bool greaterSort(const Card& c1, const Card& c2);


// 因为多张卡牌类中用到 QSet 存储自定义类型的 Card 对象，所以要有以下两个操作

// 操作符重载
bool operator <(const Card& c1, const Card& c2);
bool operator ==(const Card& left, const Card& right);

// 重写全局函数 qHash
uint qHash(const Card& card);


#endif // CARD_H
