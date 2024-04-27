#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "robot.h"
#include "userplayer.h"
#include "cards.h"

struct BetRecord
{
    BetRecord()
    {
        reset();
    }
    void reset()
    {
        player = nullptr;
        bet = 0;
        times = 0;
    }
    Player* player;
    int bet;
    int times;
};

class GameControl : public QObject
{
    Q_OBJECT

public:
    explicit GameControl(QObject *parent = nullptr);

    // 游戏状态
    enum GameStatus
    {
        DispatchCard,
        CallingLord,
        PlayingHand
    };

    // 玩家状态
    enum PlayerStatus
    {
        ThinkingForCallLord,
        ThinkingForPlayHand,
        Winning
    };

    // 玩家初始化
    void playerInit();

    // 获取玩家的示例对象
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();

    // 设置、获取当前玩家对象
    void setCurrentPlayer(Player* player);
    Player* getCurrentPlayer();

    // 获取当前玩家及其打出的牌
    Player* getPendPlayer();
    Cards getPendCards();

    void initAllCards();                            // 初始化扑克牌
    Card takeOneCard();                             // 每次发一张牌
    Cards getSurplusCards();                        // 得到最后三张地主牌
    void resetCardData();                           // 重置卡牌数据

    void startLordCard();                           // 准备叫地主
    void becomeLord(Player *player, int bet);       // 成为地主

    void clearPlayerScore();                        // 清空所有玩家的得分
    int getPlayerMaxBet();

    void onGrabBet(Player* player, int bet);

    void onPlayHand(Player *player, const Cards &card);

signals:
    void playerStatusChanged(Player* player, PlayerStatus status);
    void notifyGrabLordBet(Player* player, int bet, bool flag);
    void gameStatusChanged(GameStatus status);
    void notifyPlayHand(Player* player, const Cards& card);
    void pendingInfo(Player* player, const Cards& card);

private:
    // 三个玩家的指针
    Robot* m_robotLeft = nullptr;
    Robot* m_robotRight = nullptr;
    UserPlayer* m_user = nullptr;

    Player* m_currPlayer = nullptr;             // 当前玩家指针
    Player* m_pendPlayer = nullptr;             // 打出牌的玩家
    Cards m_pendCards;                          // 玩家打出的牌
    Cards m_allCards;                           // 卡牌对象
    BetRecord m_betRecord;
    int m_curBet = 0;

};

#endif // GAMECONTROL_H
