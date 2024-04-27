#ifndef PLAYER_H
#define PLAYER_H

/* 玩家基类 */

#include <QObject>
#include "cards.h"

class Player : public QObject
{
    Q_OBJECT

public:
    enum Role{Lord, Farmer};                                        // 角色
    enum Sex{Man, Woman};                                           // 性别
    enum Direction{Left, Right};                                    // 头像的显示方位
    enum Type{Robot, User, UnKnow};                                 // 玩家的类型
    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name, QObject *parent = nullptr);

    // 名字
    void setName(QString name);
    QString getName();

    // 角色
    void setRole(Role role);
    Role getRole();

    // 性别
    void setSex(Sex sex);
    Sex getSex();

    // 方位
    void setDirection(Direction direction);
    Direction getDirection();

    // 类型
    void setType(Type type);
    Type getType();

    // 分数
    void setScore(int score);
    int getScore();

    // 结果
    void setWin(bool flag);
    bool isWin();

    // 上家 下家
    void setPrevPlayer(Player* player);
    void setNextPlayer(Player* player);
    Player* getPrevPlayer();
    Player* getNextPlayer();

    // 抢地主
    void grabLordBet(int point);

    // 存储扑克牌（发牌的时候得到的）
    void storeDispatchCard(const Card& card);
    void storeDispatchCard(const Cards& cards);

    // 得到玩家手中所有的牌
    Cards getCards();

    // 清空玩家手中所有的牌
    void clearCards();

    // 出牌
    void playHand(const Cards& cards);

    // 设置打出的扑克牌的玩家以及打出的扑克牌
    void storePendingInfo(Player* player, const Cards& cards);

    // 获取打出的扑克牌的玩家以及打出的扑克牌
    Player* getPendPlayer();
    Cards getPendCards();

    virtual void prepareCallLord();         // 准备叫地主
    virtual void thinkCallLord();

    virtual void preparePlayHand();         // 准备出牌
    virtual void thinkPlayHand();

signals:
    void notifyGrabLordBet(Player* player, int bet);
    void notifyPlayHand(Player* player, const Cards& card);
    void notifyPickCards(Player* player, const Cards& cards);

protected:
    int m_score = 0;                        // 玩家分数
    QString m_name;                         // 玩家名字
    Role m_role;                            // 玩家角色
    Sex m_sex;                              // 玩家性别
    Direction m_direction;                  // 玩家头像的显示方位
    Type m_type;                            // 玩家类型
    bool m_isWin = false;                   // 游戏结果
    Player* m_prev = nullptr;               // 当前玩家的上家
    Player* m_next = nullptr;               // 当前玩家的下家
    Cards m_cards;                          // 存储多张扑克牌（玩家手中的牌）
    Cards m_pendCards;                      // 打出的扑克牌
    Player* m_pendPlayer = nullptr;         // 打出的扑克牌的所有者
};

#endif // PLAYER_H
