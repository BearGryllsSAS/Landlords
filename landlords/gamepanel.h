#ifndef GAMEPANEL_H
#define GAMEPANEL_H

/* 游戏主窗口 */

#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include "cardpanel.h"
#include "gamecontrol.h"
#include "animationwindow.h"
#include "player.h"
#include "countdown.h"
#include "bgmcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GamePanel; }
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();
    enum AnimationType{ShunZi, LianDui, Plane, JokerBomb, Bomb, Bet};

    // 初始化游戏控制类信息
    void gameControlInit();
    // 更新分数面板的分数
    void updatePlayerScore();
    // 切割并存储图片
    void initCardMap();
    // 裁剪图片
    void cropImage(QPixmap& pix, int x, int y, Card& c);
    // 初始化游戏中的按钮组
    void initButtonsGroup();
    // 初始化玩家在窗口中的上下文环境
    void initPlayerContext();
    // 初始化游戏场景
    void initGameScene();
    // 处理游戏的状态
    void gameStatusPrecess(GameControl::GameStatus status);
    // 发牌
    void startDispatchCard();
    void cardMoveStep(Player* player, int curPos);
    // 处理分发得到的扑克牌
    void disposeCard(Player* player, const Cards& cards);
    // 更新玩家的扑克牌在窗口中的显示
    void updatePlayerCards(Player* player);
    QPixmap loadRoleImage(Player::Sex sex, Player::Direction direct, Player::Role role);

    // 定时器的处理动作
    void onDispatchCard();
    void onPlayerStatusChanged(Player* player, GameControl::PlayerStatus status);
    void onGrabLordBet(Player* player, int bet, bool flag);
    void onDisposePlayHand(Player* player, const Cards& cards);
    void onCardSelected(Qt::MouseButton button);
    void onUserPlayHand();
    void onUserPass();

    void showAnimation(AnimationType type, int bet = 0);
    void hidePlayerDropCards(Player* player);
    void showEndingScorePanel();
    void initCountDown();

protected:
    void paintEvent(QPaintEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);


private:
    enum CardAlign{Horizontal, Vertical};
    struct PlayerContext
    {
        QRect cardRect;             // 玩家扑克牌的显示区域
        QRect playHandRect;         // 出牌的区域
        CardAlign align;            // 扑克牌的对齐方式 水平 or 垂直
        bool isFrontSide;           // 扑克牌显示正面还是被背面
        QLabel* info;               // 游戏过程中的提示信息
        QLabel* roleImg;            // 玩家的头像
        Cards lastCards;            // 玩家刚打出的牌
    };

    Ui::GamePanel *ui;
    QPixmap m_bkImage;
    GameControl* m_gameCtl;
    QVector<Player*> m_playerList;
    QMap<Card, CardPanel*> m_cardMap;
    QSize m_cardSize;
    QPixmap m_cardBackImg;
    QMap<Player*, PlayerContext> m_contextMap;
    CardPanel* m_baseCard;
    CardPanel* m_moveCard;
    QVector<CardPanel*> m_last3Card;
    QPoint m_baseCardPos;
    GameControl::GameStatus m_gameStatus;
    QTimer* m_timer;
    AnimationWindow* m_animation;
    CardPanel* m_curSelCard;
    QSet<CardPanel*> m_selectCards;
    QRect m_cardsRect;
    QHash<CardPanel*, QRect> m_userCards;
    CountDown* m_countDown;
    BGMControl* m_bgm;
};
#endif // GAMEPANEL_H
