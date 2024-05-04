#ifndef PLAYHAND_H
#define PLAYHAND_H

#include "card.h"
#include "cards.h"



class PlayHand
{
public:
    // 出牌组合或者方式
    enum HandType
    {
        Hand_Unknown,                               // 未知
        Hand_Pass,                                  // 过

        Hand_Single,                                // 单
        Hand_Pair,                                  // 对

        Hand_Triple,                                // 三个
        Hand_Triple_Single,                         // 三带一
        Hand_Triple_Pair,                           // 三带二

        Hand_Plane,                                 // 飞机，555_666
        Hand_Plane_Two_Single,                      // 飞机带单，555_666_3_4
        Hand_Plane_Two_Pair,                        // 飞机带双，555_666_33_44

        Hand_Seq_Pair,                              // 连对，33_44_55(_66...)
        Hand_Seq_Single,                            // 顺子，34567(8...)

        Hand_Bomb,                                  // 炸弹
        Hand_Bomb_Single,                           // 炸弹带一个
        Hand_Bomb_Pair,                             // 炸弹带一对
        Hand_Bomb_Two_Single,                       // 炸弹带两单

        Hand_Bomb_Jokers,                           // 王炸
        Hand_Bomb_Jokers_Single,                    // 王炸带一个
        Hand_Bomb_Jokers_Pair,                      // 王炸带一对
        Hand_Bomb_Jokers_Two_Single                 // 王炸带两单
    };

    PlayHand();
    // 传递给类一组牌，通过类分析出牌型，点数，以及相关的附属信息(比如顺子:记录牌的数量)
    explicit PlayHand(Cards& cards);
    // 通过牌的类型，点数，以及相关的附属信息构造 PlayHand 对象
    PlayHand(HandType type, Card::CardPoint pt, int extra);

    // 得到牌的类型
    HandType getHandType();
    // 得到牌的点数
    Card::CardPoint getCardPoint();
    // 得到牌的相关属性信息
    int getExtra();

    // 比较自己的牌与其他人的牌的大小
    bool canBeat(const PlayHand& other);

private:
    void classify(Cards& cards);                    // 对扑克牌进行分类:1张的，2张，3张，4张有多少种 --- 计算出每种点数牌的数量
    void judgeCardType();                           // 对牌型进行分类 --- 判断牌的类型
    bool isPass();                                  // 判断是否不要 --- 打出空牌
    bool isSingle();                                // 判断是否为单
    bool isPair();                                  // 判断是否为对
    bool isTriple();                                // 判断是否为三个相同
    bool isTripleSingle();                          // 判断是否为三带一
    bool isTriplePair();                            // 判断是否为三带二
    bool isPlane();                                 // 判断是否为飞机
    bool isPlaneTwoSingle();                        // 判断是否为飞机带两单
    bool isPlaneTwoPair();                          // 判断是否为飞机带一对
    bool isSeqPair();                               // 判断是否为连对
    bool isSeqSingle();                             // 判断是否为顺子
    bool isBomb();                                  // 判断是否为炸弹
    bool isBombSingle();                            // 判断是否为炸弹带一单
    bool isBombPair();                              // 判断是否为炸弹带一对
    bool isBombTwoSingle();                         // 判断是否为炸弹带两单
    bool isBombJokers();                            // 判断是否为王炸
    bool isBombJokersSingle();                      // 判断是否为王炸带一单
    bool isBombJokersPair();                        // 判断是否为王炸带一对
    bool isBombJokersTwoSingle();                   // 判断是否为王炸带两单

private:
    HandType m_type;                                // 牌的类型
    Card::CardPoint m_pt;                           // 点数
    int m_extra;                                    // 相关的附属信息
    QVector<Card::CardPoint> m_oneCard;             // 存储单张点数的扑克牌 --- 3
    QVector<Card::CardPoint> m_twoCard;             // 存储两张点数的扑克牌 --- 3 3
    QVector<Card::CardPoint> m_threeCard;           // 存储三张点数的扑克牌 --- 3 3 3
    QVector<Card::CardPoint> m_fourCard;            // 存储四张点数的扑克牌 --- 3 3 3 3
};

#endif // PLAYHAND_H
