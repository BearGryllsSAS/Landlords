#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

/* 按钮组类 */

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    enum Panel{Start, PlayCard, PassOrPlay, CallLord, Empty};       // 各个 page 页对应的索引
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    // 初始化按钮
    void initButtons();

    // 处理按钮组中 page 页的切换
    void selectPanel(Panel type, int bet = 0);

signals:
    // 按钮组中有事件时，在当前类中发射相应的信号给其他类处理


    void startGame();               // 开始游戏
    void playHand();                // 出牌
    void pass();                    // 不出牌
    void betPoint(int bet);         // 抢地主

private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTONGROUP_H
