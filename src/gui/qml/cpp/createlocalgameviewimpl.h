#ifndef CREATELOCALGAMEVIEWIMPL_H
#define CREATELOCALGAMEVIEWIMPL_H
#include "boost/shared_ptr.hpp"
#include <QtCore>
#include <QQmlListProperty>
#include <QQmlApplicationEngine>

class ConfigFile;
class MyListViewItemData;
class StartViewImpl;

class CreateLocalGameViewImpl : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void readConfigValues();
    Q_INVOKABLE void startGame();

    CreateLocalGameViewImpl(QObject *parent, QQmlApplicationEngine *engine, boost::shared_ptr<ConfigFile>, StartViewImpl*);
    ~CreateLocalGameViewImpl();

    MyListViewItemData* listItem(QString id);

signals:

public slots:
private:
    QQmlApplicationEngine *myQmlEngine;
    QList<QObject*> myListData;
    boost::shared_ptr<ConfigFile> myConfig;
    StartViewImpl *myStartView;
};

#endif // CREATELOCALGAMEVIEWIMPL_H
