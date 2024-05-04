#ifndef STRATEGY_H
#define STRATEGY_H

#include "player.h"
#include "playhand.h"

// 制定出牌策略
// 第一个出牌 firstPlay
// 得到比指定牌型大的牌
// 能大过指定的牌时，判断是出牌还是放行，返回true->出牌，返回false->放行

class Strategy
{
public:
    Strategy(Player* player, const Cards& cards);


    Cards makeStrategy();
    Cards firstPlay();
    Cards getGreaterCards(PlayHand type);
    bool whetherToBeat(Cards& cs);

    // 找出指定数量 count 的相同点数的牌 point，找出 count 张点数为 point 的牌
    Cards findSamePointCards(Card::CardPoint point, int count);
    // 找出所有点数数量为 count 的牌 --- 得到一个多张扑克牌数组
    QVector<Cards> findCardsByCount(int count);
    // 根据点数范围找牌 --- 得到指定范围内的所有牌的集合
    Cards getRangeCards(Card::CardPoint begin, Card::CardPoint end);
    // 按牌型找牌，并且指定要找的牌是否要大过指定的牌型 --- 得到相同牌型的不同种组合
    QVector<Cards> findCardType(PlayHand hand, bool beat);

    void pickSeqSingles(QVector<QVector<Cards>> &allSeqRecord, const QVector<Cards> &seqSingle, const Cards& cards);
    QVector<Cards> pickOptimalSeqSingles();

private:
    using function = Cards (Strategy::*)(Card::CardPoint point);
    struct CardInfo
    {
        Card::CardPoint begin;
        Card::CardPoint end;
        int extra;
        bool beat;
        int number;
        int base;
        function getSeq;
    };
    // 找出并返回不小于指定点数 && 指定张数的一组牌
    QVector<Cards> getCards(Card::CardPoint point, int number);
    // 找 三带一 三代二 的牌
    QVector<Cards> getTripleSingleOrPair(Card::CardPoint begin, PlayHand::HandType type);
    QVector<Cards> getPlane(Card::CardPoint begin);
    QVector<Cards> getPlane2SingleOr2Pair(Card::CardPoint begin, PlayHand::HandType type);
    QVector<Cards> getSepPairOrSeqSingle(CardInfo &info);
    Cards getBaseSeqPair(Card::CardPoint point);
    Cards getBaseSeqSingle(Card::CardPoint point);
    QVector<Cards> getBomb(Card::CardPoint begin);

private:
    Player* m_player;
    Cards m_cards;
};

#endif // STRATEGY_H
