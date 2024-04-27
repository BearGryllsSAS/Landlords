#ifndef USERPLAYER_H
#define USERPLAYER_H

/* 玩家类 */

#include <QObject>
#include "player.h"

class UserPlayer : public Player
{
    Q_OBJECT
public:
    using Player::Player;                               // 继承父类的构造函数
    explicit UserPlayer(QObject *parent = nullptr);

    void prepareCallLord() override;                    // 准备叫地主
    void preparePlayHand() override;                    // 准备出牌

signals:
    void startCountDown();
};

#endif // USERPLAYER_H
