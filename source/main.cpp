// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/mainwindow/mainwindow.h>
#include <QApplication>
#include <QLocale>

int main(int argc, char** argv)
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

//    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

    QApplication app(argc, argv);

    MainWindow win;
    win.show();

    return app.exec();
}
