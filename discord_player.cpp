#include "discord_player.h"
#include "ui_discord_player.h"

#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QWebEngineSettings>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

static QUrl baseUrl("https://discordapp.com/channels/@me");

static DiscordPlayerPage *globalPageToGetClickUrl;

DiscordPlayerPage::DiscordPlayerPage(QWebEngineProfile *profile, QObject *parent) : QWebEnginePage(profile, parent) {}
DiscordPlayerPage::DiscordPlayerPage(QObject *parent) : QWebEnginePage(parent) {}

QWebEnginePage *DiscordPlayerPage::createWindow(QWebEnginePage::WebWindowType type) {
    qDebug() << "createWindow type: " << type;
    return globalPageToGetClickUrl;
}

bool DiscordPlayerPage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame) {
    qDebug() << "acceptNavigationRequest url: " << url << " type: " << type << " isMainFrame: " << isMainFrame;
    if (isMainFrame) {
        // Exception for base link
        if (url == baseUrl)
            goto pass;
        QDesktopServices::openUrl(url);
        return false;
    }

pass:
    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}

discord_player::discord_player(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::discord_player)
{
    QDir configDirectory(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));

    // Check the lock for other open instances
    QFile lock(configDirectory.absoluteFilePath(QStringLiteral("discord-player/lock")));
    if (lock.open(QIODevice::ReadOnly)) {
        // The lock is already acquired
        QMessageBox::critical(this, "Application running",
                                  "Another instance of discord-player was detected running.",
                                  QMessageBox::Ok);
        lock.close();
        exit(1);
    }
    while (!lock.open(QIODevice::WriteOnly)) {
        configDirectory.mkdir(configDirectory.absoluteFilePath("discord-player"));
    }
    lock.close();

    ui->setupUi(this);

    globalPageToGetClickUrl = new DiscordPlayerPage();

    DiscordPlayerPage *DPage = new DiscordPlayerPage();
    ui->webEngineView->setPage(DPage);

    showMaximized();

    QFile css(configDirectory.absoluteFilePath(QStringLiteral("discord-player/custom.css")));
    if (css.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray source = css.readAll();
        qInfo() << "Injecting custom css: " << source;
        QWebEngineScript script;
        QString s = QStringLiteral("(function() {"\
                                   "    css = document.createElement('style');"\
                                   "    css.type = 'text/css';"\
                                   "    css.id = 'injectedCss';"\
                                   "    document.head.appendChild(css);"\
                                   "    css.innerText = atob('%2');"\
                                   "})()").arg(QString::fromLatin1(source.toBase64()));
        script.setName(QStringLiteral("injectedCss"));
        script.setSourceCode(s);
        script.setInjectionPoint(QWebEngineScript::DocumentReady);
        script.setRunsOnSubFrames(true);
        script.setWorldId(QWebEngineScript::ApplicationWorld);
        ui->webEngineView->page()->scripts().insert(script);
    }

    connect(ui->webEngineView->page(),
            SIGNAL(featurePermissionRequested(const QUrl &, QWebEnginePage::Feature)),
            this,
            SLOT(grantFeaturePermission(const QUrl &, QWebEnginePage::Feature)));

    ui->webEngineView->page()->settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);

    ui->webEngineView->page()->setUrl(QUrl(baseUrl));
}

discord_player::~discord_player()
{
    QDir configDirectory(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    QFile lock(configDirectory.absoluteFilePath(QStringLiteral("discord-player/lock")));

    lock.remove();

    delete globalPageToGetClickUrl;
    delete ui->webEngineView->page();
    delete ui;
}

void discord_player::grantFeaturePermission(const QUrl &q, QWebEnginePage::Feature f) {
    qDebug() << q << f;

    QString s;
    QDebug d(&s);
    d << "Grant \"" << q << "\" permission to use \"" << f << "\"?";

    QMessageBox::StandardButton r;
    r = QMessageBox::question(this, "Grant permission", s,
            QMessageBox::Yes | QMessageBox::No);

    if (r == QMessageBox::Yes) {
        ui->webEngineView->page()->setFeaturePermission(q, f,
            QWebEnginePage::PermissionGrantedByUser);
    } else {
        ui->webEngineView->page()->setFeaturePermission(q, f,
            QWebEnginePage::PermissionDeniedByUser);
    }
}

void discord_player::on_webEngineView_titleChanged(const QString &title)
{
    setWindowTitle(title);
}

void discord_player::on_webEngineView_iconChanged(const QIcon &arg1)
{
    setWindowIcon(arg1);
}
