#include "discord_player.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    const char *baseUrl;
    if (argc > 1) {
        baseUrl = argv[1];
    } else {
        baseUrl = "https://discordapp.com/channels/@me";
    }

    QApplication a(argc, argv);
    discord_player w(baseUrl);
    w.show();

    return a.exec();
}
