# Qt-GUI-Notifier-Widget

Animated messages appearing on the right side of the screen. 

Usage Example:

  PushNotifier* notifier = new PushNotifier("Hello Qt!", 500, this); // create widget 
  notifier->setPauseDuration(5000);
  notifier->setSlideOutDuration(200);
  notifier->setSlideInDuration(300);
  notifier->show();
