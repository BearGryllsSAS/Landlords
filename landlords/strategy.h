#ifndef STRATEGY_H
#define STRATEGY_H

#include "player.h"
#include "playhand.h"

class Strategy
{
public:
    Strategy(Player* player, const Cards& cards);

    // 制定出牌策略 --- 机器人玩家使用
    Cards makeStrategy();
    // 第一个出牌 firstPlay
    Cards firstPlay();
    // 得到比指定牌型大的牌
    Cards getGreaterCards(PlayHand type);
    // 能大过指定的牌时，判断是出牌还是放行，返回true->出牌，返回false->放行
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
    // getSepPairOrSeqSingle 的参数
    struct CardInfo
    {
        Card::CardPoint begin;                  // 牌的起始点数
        Card::CardPoint end;                    // 牌的终止点数
        int extra;                              // 牌的额外拓展信息
        bool beat;                              // 是否要打赢
        int number;                             // 指定点数牌的数量 顺子-1 连对-2
        int base;                               // 最基础的顺子或者连对的数量
        function getSeq;                        // 回调函数
    };
    // 找出并返回不小于指定点数 && 指定张数的一组牌
    QVector<Cards> getCards(Card::CardPoint point, int number);
    // 找 三带一 三代二 的牌
    QVector<Cards> getTripleSingleOrPair(Card::CardPoint begin, PlayHand::HandType type);
    // 找飞机
    QVector<Cards> getPlane(Card::CardPoint begin);
    // 找 飞机带一 飞机带二 的牌
    QVector<Cards> getPlane2SingleOr2Pair(Card::CardPoint begin, PlayHand::HandType type);
    // 找 连对 顺子 的牌
    QVector<Cards> getSepPairOrSeqSingle(CardInfo &info);
    // 找炸弹
    QVector<Cards> getBomb(Card::CardPoint begin);
    // 回调函数 --- 连对
    Cards getBaseSeqPair(Card::CardPoint point);
    // 回调函数 --- 顺子
    Cards getBaseSeqSingle(Card::CardPoint point);

private:
    Player* m_player;
    Cards m_cards;
};

#endif // STRATEGY_H
