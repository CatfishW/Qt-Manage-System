#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QtSql>
int main(int argc, char *argv[])
{
    QSqlDatabase db;
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GraduateCareerManageSystem_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("nj-cynosdbmysql-grp-mu5omonl.sql.tencentcdb.com");
    db.setPort(27491);
    db.setDatabaseName("qt");
    db.setUserName("root");
    db.setPassword("Wyl132161366");
    bool db_open = db.open();
    LoginWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    if (!db_open) {
            qDebug()<<"database not connected";
            return -1;
        }
    w.show();
    return a.exec();
}
