#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>
#include "gamecontrol.h"
#include "playhand.h"

GameControl::GameControl(QObject *parent) : QObject(parent)
{

}

void GameControl::playerInit()
{
    // 玩家对象实例化
    m_robotLeft = new Robot("机器人A", this);
    m_robotRight = new Robot("机器人B", this);
    m_user = new UserPlayer("我自己", this);

    // 玩家头像显示方位
    m_robotLeft->setDirection(Player::Left);
    m_robotRight->setDirection(Player::Right);
    m_user->setDirection(Player::Right);

    // 玩家性别
    Player::Sex sex;
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotLeft->setSex(sex);
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotRight->setSex(sex);
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_user->setSex(sex);

    // 上家 下家
    m_user->setPrevPlayer(m_robotLeft);
    m_user->setNextPlayer(m_robotRight);
    m_robotLeft->setPrevPlayer(m_robotRight);
    m_robotLeft->setNextPlayer(m_user);
    m_robotRight->setPrevPlayer(m_user);
    m_robotRight->setNextPlayer(m_robotLeft);

    // 指定当前玩家对象
    m_currPlayer = m_user;

    connect(m_user, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);
    connect(m_robotLeft, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);
    connect(m_robotRight, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);

    connect(this, &GameControl::pendingInfo, m_robotLeft, &Robot::storePendingInfo);
    connect(this, &GameControl::pendingInfo, m_robotRight, &Robot::storePendingInfo);
    connect(this, &GameControl::pendingInfo, m_user, &Robot::storePendingInfo);

    connect(m_robotLeft, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
    connect(m_robotRight, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
    connect(m_user, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
}

Robot *GameControl::getLeftRobot()
{
    return m_robotLeft;
}

Robot *GameControl::getRightRobot()
{
    return m_robotRight;
}

UserPlayer *GameControl::getUserPlayer()
{
    return m_user;
}

void GameControl::setCurrentPlayer(Player *player)
{
    m_currPlayer = player;
}

Player *GameControl::getCurrentPlayer()
{
    return m_currPlayer;
}

Player *GameControl::getPendPlayer()
{
    return m_pendPlayer;
}

Cards GameControl::getPendCards()
{
    return m_pendCards;
}

void GameControl::initAllCards()
{
    m_allCards.clear();

    // for 循环遍历花色和点数赋值给单张扑克牌对象，然后加入牌堆
    for(int p = Card::Card_Begin+1; p<Card::Card_SJ; ++p)
    {
        for(int s = Card::Suit_Begin+1; s<Card::Suit_End; ++s)
        {
            Card c((Card::CardPoint)p, (Card::CardSuit)s);
            m_allCards.add(c);
        }
    }
    m_allCards.add(Card(Card::Card_SJ, Card::Suit_Begin));
    m_allCards.add(Card(Card::Card_BJ, Card::Suit_Begin));
}

Card GameControl::takeOneCard()
{
#if 0
    // 测试飞机
    static bool flag = true;
    static Cards tmp;
    if(flag)
    {
        Card c1(Card::Card_10, Card::Club);
        Card c2(Card::Card_10, Card::Diamond);
        Card c3(Card::Card_10, Card::Heart);

        Card c4(Card::Card_J, Card::Club);
        Card c5(Card::Card_J, Card::Diamond);
        Card c6(Card::Card_J, Card::Heart);

        tmp << c1 << c2 << c3 << c4 << c5 << c6;
        m_allCards.remove(tmp);
        flag = false;
    }

    if(getCurrentPlayer() == m_user && !tmp.isEmpty())
    {
        return tmp.takeRandomCard();
    }
    else
    {
        return m_allCards.takeRandomCard();
    }
#else
    // not test code
    return m_allCards.takeRandomCard();
#endif
}

Cards GameControl::getSurplusCards()
{
    return m_allCards;
}

void GameControl::resetCardData()
{
    // 洗牌
    initAllCards();

    // 清空所有玩家的牌
    m_robotLeft->clearCards();
    m_robotRight->clearCards();
    m_user->clearCards();

    // 初始化出牌玩家和打出的牌
    m_pendPlayer = nullptr;
    m_pendCards.clear();
}

void GameControl::startLordCard()
{
    // 发牌结束 准备叫地主
    m_currPlayer->prepareCallLord();
    // 通知主窗口玩家状态发生了变化
    emit playerStatusChanged(m_currPlayer, ThinkingForCallLord);
}

void GameControl::becomeLord(Player *player, int bet)
{
    m_curBet = bet;
    player->setRole(Player::Lord);
    player->getPrevPlayer()->setRole(Player::Farmer);
    player->getNextPlayer()->setRole(Player::Farmer);

    m_currPlayer = player;
    player->storeDispatchCard(m_allCards);              // 获得剩下三张地主牌

    QTimer::singleShot(1000, this, [=]()                // 如果是机器人玩家成为地主则增加思考时间
    {
        // 通知主窗口游戏状态发生变化
        emit gameStatusChanged(PlayingHand);
        // 更改玩家状态
        emit playerStatusChanged(player, ThinkingForPlayHand);
        // 出牌
        m_currPlayer->preparePlayHand();
    });
}

void GameControl::clearPlayerScore()
{
    m_robotLeft->setScore(0);
    m_robotRight->setScore(0);
    m_user->setScore(0);
}

int GameControl::getPlayerMaxBet()
{
    return m_betRecord.bet;
}

void GameControl::onGrabBet(Player *player, int bet)
{  
    // 通知主界面玩家叫地主了(更新信息提示)
    if(bet == 0 || m_betRecord.bet >= bet)
    {
        // 当前玩家放弃抢地主
        emit notifyGrabLordBet(player, 0, false);
    }
    else if(bet > 0 && m_betRecord.bet == 0)
    {
        // 当前玩家第一次抢地主
        emit notifyGrabLordBet(player, bet, true);
    }
    else
    {
        // 当前玩家不是第一次抢地主
        emit notifyGrabLordBet(player, bet, false);
    }

    if(bet == 3)                                                            // 判断玩家下注是不是3分，如果是抢地主结束
    {
        becomeLord(player, bet);
        m_betRecord.reset();
        return;
    }
    if(m_betRecord.bet < bet)                                               // 下注不够3分，对玩家的分数进行比较，分数高的是地主
    {
        m_betRecord.bet = bet;
        m_betRecord.player = player;
    }
    m_betRecord.times ++;                                                   // 下注次数加一
    if(m_betRecord.times == 3)
    {
        if(m_betRecord.bet == 0)
        {
            emit gameStatusChanged(DispatchCard);                           // 通知主窗口游戏状态为重新发牌
        }
        else
        {
            becomeLord(m_betRecord.player, m_betRecord.bet);                // 让得分最大的玩家成为地主
        }
        // m_betRecord.reset();                                                // 重置下注分数
        return;
    }
    m_currPlayer = player->getNextPlayer();                                 // 切换玩家，通知下一个玩家继续抢地主
    emit playerStatusChanged(m_currPlayer, ThinkingForCallLord);            // 发送信号给主界面 告知当前游戏状态为抢地主
    m_currPlayer->prepareCallLord();                                        // 告知玩家抢地主
}

void GameControl::onPlayHand(Player *player, const Cards &card)
{
    emit notifyPlayHand(player, card);
    if(!card.isEmpty())
    {
        m_pendCards = card;
        m_pendPlayer = player;
        emit pendingInfo(player, card);
    }
    Cards myCards = const_cast<Cards&>(card);
    PlayHand::HandType type = PlayHand(myCards).getHandType();
    if(type == PlayHand::Hand_Bomb || type == PlayHand::Hand_Bomb_Jokers)
    {
        m_curBet = m_curBet * 2;
    }

    if(player->getCards().isEmpty())
    {
        Player* prev = player->getPrevPlayer();
        Player* next = player->getNextPlayer();
        if(player->getRole() == Player::Lord)
        {
            player->setScore(player->getScore() + 2 * m_curBet);
            prev->setScore(prev->getScore() - m_curBet);
            next->setScore(next->getScore() - m_curBet);
            player->setWin(true);
            prev->setWin(false);
            next->setWin(false);
        }
        else
        {
            player->setWin(true);
            player->setScore(player->getScore() + m_curBet);
            if(prev->getRole() == Player::Lord)
            {
                prev->setScore(prev->getScore() - 2 * m_curBet);
                next->setScore(next->getScore() + m_curBet);
                prev->setWin(false);
                next->setWin(true);
            }
            else
            {
                next->setScore(next->getScore() - 2 * m_curBet);
                prev->setScore(prev->getScore() + m_curBet);
                next->setWin(false);
                prev->setWin(true);
            }
        }
        emit playerStatusChanged(player, GameControl::Winning);
        return;
    }
    m_currPlayer = player->getNextPlayer();
    m_currPlayer->preparePlayHand();
    emit playerStatusChanged(m_currPlayer, GameControl::ThinkingForPlayHand);
}
