#include "PushNotifier.h"

PushNotifier::PushNotifier(const QString message, const unsigned Y, QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowFlag(Qt::Dialog);
    setStyleSheet("background-color: black;");
    // get monitor metrics
    QRect dimensions = QApplication::desktop()->screenGeometry(0);
    // making salad background
    saladBackgroung = new QLabel(this);
    saladBackgroung->setStyleSheet("background-color: #59E817;");
    saladBackgroung->setGeometry(QRect(0, 0, 300, 100));
    // setup animations
    saladInAnimationion  = new QPropertyAnimation(saladBackgroung, "geometry");
    saladOutAnimationion = new QPropertyAnimation(saladBackgroung, "geometry");
    saladInAnimationion->setDuration(300);
    saladOutAnimationion->setDuration(300);
    saladInAnimationion->setStartValue(QRect(0, 0, 300, 100));
    saladInAnimationion->setEndValue(QRect(width() - 370, 0, 300, 100));
    saladOutAnimationion->setStartValue(QRect(width() - 370, 0, 300, 100));
    saladOutAnimationion->setEndValue(QRect(0, 0, 300, 100));
    // Notification Message
    what = new QLabel(this);
    what->setText(message);
    what->setFont(QFont("Times New Roman", 12));
    what->setStyleSheet("QLabel {color : white; }");
    what->setMargin(-20);
    what->setAlignment(Qt::AlignCenter);
    what->setGeometry(QRect(40, 0, 270, 100));
    eff->setOpacity(0);
    what->setGraphicsEffect(eff);
    // setup text message fade-in / fade-out animation
    fadeInAnimation = new QPropertyAnimation(eff, "opacity");
    fadeOutAnimation = new QPropertyAnimation(eff, "opacity");
    fadeInAnimation->setDuration(500);
    fadeOutAnimation->setDuration(500);
    fadeInAnimation->setStartValue(0);
    fadeInAnimation->setEndValue(1);
    fadeOutAnimation->setStartValue(1);
    fadeOutAnimation->setEndValue(0);

    animationSeqGroup = new QSequentialAnimationGroup(this);
    animationParInGroup = new QParallelAnimationGroup(this);
    animationParOutGroup = new QParallelAnimationGroup(this);

    slideInAnimationion = new QPropertyAnimation(this, "geometry");
    slideOutAnimationion = new QPropertyAnimation(this, "geometry");

    slideInAnimationion->setDuration(_slideInDuration);
    slideOutAnimationion->setDuration(_slideOutDuration);
    slideInAnimationion->setEasingCurve(QEasingCurve::InSine);

    slideInAnimationion->setStartValue(QRect(dimensions.width(),     Y, 0,   100));
    slideInAnimationion->setEndValue(QRect(dimensions.width() - 300, Y, 300, 100));

    slideOutAnimationion->setStartValue(QRect(dimensions.width() - 300, Y, 300, 100));
    slideOutAnimationion->setEndValue(QRect(dimensions.width(),         Y, 0,   100));
    // setup a pause before text disappearing
    pauseAnimation = new QPauseAnimation(this);
    pauseAnimation->setDuration(_pauseDuration);
    // compile all animations
    animationParInGroup->addAnimation(slideInAnimationion);
    animationParOutGroup->addAnimation(slideOutAnimationion);
    animationSeqGroup->addAnimation(animationParInGroup);
    animationSeqGroup->addAnimation(saladInAnimationion);
    animationSeqGroup->addAnimation(fadeInAnimation);
    animationSeqGroup->addAnimation(pauseAnimation);
    animationSeqGroup->addAnimation(fadeOutAnimation);
    animationSeqGroup->addAnimation(saladOutAnimationion);
    animationSeqGroup->addAnimation(animationParOutGroup);
    // animation complete event
    connect(slideOutAnimationion, &QAbstractAnimation::finished, this, &PushNotifier::onAnimationComplete);
    // push the message out
    animationSeqGroup->start();
}

void PushNotifier::setPauseDuration(const unsigned ms)
{
    _pauseDuration = ms;
    pauseAnimation->setDuration(_pauseDuration);
}

void PushNotifier::setSlideOutDuration(const unsigned ms)
{
    _slideOutDuration = ms;
    slideOutAnimationion->setDuration(_slideOutDuration);
}

void PushNotifier::setSlideInDuration(const unsigned ms)
{
    _slideInDuration = ms;
    slideInAnimationion->setDuration(_slideInDuration);
}

void PushNotifier::onAnimationComplete()
{
    qDebug() << "Animation complete"; // just a debug output
    close();
}
