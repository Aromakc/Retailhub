#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Set organisation and application names
    a.setWindowIcon(QIcon(":/Resources/icon.png"));
    a.setApplicationName("Retailhub");
    a.setApplicationVersion("0.1");
    a.setOrganizationName("SINNS");
    Login w;
    w.show();
    return a.exec();
}
