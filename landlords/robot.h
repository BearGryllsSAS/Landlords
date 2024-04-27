#ifndef ROBOT_H
#define ROBOT_H

/* 机器人类 */

#include <QObject>
#include "player.h"

class Robot : public Player
{
    Q_OBJECT
public:
    using Player::Player;                           // 继承父类的构造函数
    explicit Robot(QObject *parent = nullptr);

    void prepareCallLord() override;                // 准备叫地主
    void thinkCallLord() override;

    void preparePlayHand() override;                // 准备出牌
    void thinkPlayHand() override;
};

#endif // ROBOT_H
