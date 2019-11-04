#ifndef DOWNLOADNETWORKMANAGER_H
#define DOWNLOADNETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QUrl>

class DownloadNetworkManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit DownloadNetworkManager(QObject *parent = 0);
    ~DownloadNetworkManager();

    void checkVersion(const QUrl &url);
    void downloadFile(const QUrl &url);
signals:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void replyFinished(const int &status);
    void fileName(const QString &name);
    void signalVersionInfo(const QString &appVer,const QString &info);
    void signalDownFinish(const QString &name);
public slots:

private:
    QString m_strFileTemp;
    QString m_strFileName;

    QUrl m_url;
    QNetworkReply *m_pReply;

    bool m_bCheckVersion;

    void parseVersionInfo(const QByteArray &data);
    QString GetFileMd5(const QString &name);
private slots:
    void sltReadFiles();
    void replyFinished(QNetworkReply *reply);
    void onAuthenticationRequest(QNetworkReply *, QAuthenticator *authenticator);
};

#endif // DOWNLOADNETWORKMANAGER_H
