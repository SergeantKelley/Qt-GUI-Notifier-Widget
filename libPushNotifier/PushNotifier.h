#ifndef PUSHNOTIFIER_H
#define PUSHNOTIFIER_H

#include <QObject>
#include <QApplication>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QPauseAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QEasingCurve>
#include <QLabel>
#include <QDebug>

class PushNotifier : public QWidget
{
    Q_OBJECT
public:
    explicit PushNotifier(const QString message, const unsigned Y, QWidget *parent = nullptr);

public:
    void setPauseDuration(const unsigned ms);
    void setSlideOutDuration(const unsigned ms);
    void setSlideInDuration(const unsigned ms);
// animations
private:
    QPropertyAnimation * slideInAnimationion        = nullptr;
    QPropertyAnimation * slideOutAnimationion       = nullptr;
    QPropertyAnimation * widthtAnimationionExapnd   = nullptr;
    QPropertyAnimation * widthtAnimationionCollapse = nullptr;
    QPropertyAnimation * fadeInAnimation            = nullptr;
    QPropertyAnimation * fadeOutAnimation           = nullptr;
    QPropertyAnimation * saladInAnimationion        = nullptr;
    QPropertyAnimation * saladOutAnimationion       = nullptr;

    QPauseAnimation * pauseAnimation                = nullptr;
    QSequentialAnimationGroup * animationSeqGroup   = nullptr;
    QParallelAnimationGroup * animationParInGroup   = nullptr;
    QParallelAnimationGroup * animationParOutGroup  = nullptr;

    QLabel * what                                   = nullptr;
    QLabel * saladBackgroung                        = nullptr;
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);

private:
    unsigned int _pauseDuration = 3000;
    unsigned int _slideOutDuration = 400;
    unsigned int _slideInDuration = 700;

private slots:
        void onAnimationComplete();

signals:

};

#endif // PUSHNOTIFIER_H
