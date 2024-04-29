#ifndef MYBUTTON_H
#define MYBUTTON_H

/* 自定义按钮类 */

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

    // 为不同的状态设置按钮图片
    void setImage(QString normal, QString hover, QString pressed);

signals:

protected:
    // 重写按钮事件---美化

    void mousePressEvent(QMouseEvent* ev);          // 鼠标按下
    void mouseReleaseEvent(QMouseEvent* ev);        // 鼠标释放
    void enterEvent(QEvent* ev);                    // 鼠标进入
    void leaveEvent(QEvent* ev);                    // 鼠标离开
    void paintEvent(QPaintEvent* ev);               // 绘图事件

private:

    // 不同状态图片的路径
    QString m_normal;
    QString m_hover;
    QString m_pressed;

    QPixmap m_pixmap;

};

#endif // MYBUTTON_H
