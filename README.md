# Qt-GUI-Notifier-Widget

Animated messages appearing on the right side of the screen. This is a static library project. Compile one, include header file to your Qt project and link the library to start messaging.

### Usage Example:

The possible widget usage looks like follows:

PushNotifier* notifier = new PushNotifier("Hello Qt!", 500, this); // create widget, setup text, Y position and a parent widget

// adjusting animation timings in ms...

notifier->setPauseDuration(5000);

notifier->setSlideOutDuration(200);

notifier->setSlideInDuration(300);

notifier->show();
