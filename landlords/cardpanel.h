#ifndef CARDPANEL_H
#define CARDPANEL_H

/* 卡牌窗口类 */

#include <QWidget>
#include "card.h"
#include "player.h"

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    void setImage(const QPixmap &front, const QPixmap &back);   // 设置扑克牌窗口的正面、背面图片
    QPixmap getImage();                                         // 获取扑克牌窗口的不同正面图片

    void setFrontSide(bool flag);                               // 设置扑克牌窗口显示哪一面
    bool isFrontSide();                                         // 获取扑克牌窗口显示哪一面

    void setSeclected(bool flag);                               // 设置扑克牌窗口是否被选中
    bool isSelected();                                          // 获取扑克牌窗口是否被选中

    void setCard(const Card& card);                             // 设置扑克牌的花色以及点数
    Card getCard();                                             // 获取扑克牌的花色以及点数

    void setOwner(Player* player);                              // 设置扑克牌的所有者
    Player* getOwner();                                         // 获取扑克牌的所有者

    void clicked();

protected:
    void paintEvent(QPaintEvent *event);            // 事件处理函数处理绘图事件，把图片绘制出来
    void mousePressEvent(QMouseEvent* event);       // 事件处理函数处理鼠标点击事件（重写？）

signals:
    void cardSelected(Qt::MouseButton button);

private:
    QPixmap m_front;                // 保存传进来的图片信息
    QPixmap m_back;                 // 保存传进来的图片信息
    bool m_isfront = true;          // 判断当前窗口是否是正面
    bool m_isSelect = false;        // 判断扑克牌窗口是否被选中
    Card m_card;                    // 保存当前扑克牌的花色以及点数
    Player* m_owner = nullptr;      // 记录扑克牌的所有者
};

#endif // CARDPANEL_H
