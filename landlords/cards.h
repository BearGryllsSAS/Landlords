#ifndef CARDS_H
#define CARDS_H

/* 多张卡牌类 */

#include <QSet>
#include "card.h"

class Cards
{
public:
    enum SortType{Asc, Desc, NoSort};           // 指定扑克牌升序排序、降序排序、不排序
    Cards();
    explicit Cards(const Card& card);

    // 添加扑克牌
    void add(const Card& card);
    void add(const Cards& cards);
    void add(const QVector<Cards>& cards);

    // 一次性插入多个扑克牌（单张、多张） 链式编程 操作符重载 <<
    Cards& operator <<(const Card& card);
    Cards& operator <<(const Cards& cards);

    // 删除扑克牌
    void remove(const Card& card);
    void remove(const Cards& cards);
    void remove(const QVector<Cards>& cards);

    int cardCount();                            // 获取当前扑克牌的数量
    bool isEmpty();                             // 判断是否为空
    bool isEmpty() const;                       // 判断是否为空
    void clear();                               // 清空扑克牌

    Card::CardPoint maxPoint();                 // 获取当前扑克牌最大点数
    Card::CardPoint minPoint();                 // 获取当前扑克牌最大点数
    int pointCount(Card::CardPoint point);      // 获取指定点数的牌的数量
    bool contains(const Card& card);            // 判断是否存在某单张牌
    bool contains(const Cards& cards);          // 判断是否存在某几张牌

    Card takeRandomCard();                      // 随机取出一张牌发给玩家

    CardList toCardList(SortType type = Desc);  // QSet->QVector 对扑克牌进行排序 可指定升序或者降序

    void printAllCardInfo();

private:
    QSet<Card> m_cards;                         // 存放拥有的单张扑克牌（唯一、无序）
};

#endif // CARDS_H
