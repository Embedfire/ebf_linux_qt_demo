#include "downloadnetworkmanager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>

#include <QTextCodec>
#include <QDateTime>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QUrl>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QApplication>

DownloadNetworkManager::DownloadNetworkManager(QObject *parent) :
    QNetworkAccessManager(parent), m_bCheckVersion(false)
{
    connect(this, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(replyFinished(QNetworkReply *)));
}

DownloadNetworkManager::~DownloadNetworkManager()
{

}

void DownloadNetworkManager::checkVersion(const QUrl &url)
{
    QNetworkRequest request;
    m_bCheckVersion = true;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    this->get(request);
}

/**
 * @brief DownloadNetworkManager::execute
 * @param url
 */
void DownloadNetworkManager::downloadFile(const QUrl &url)
{
    m_url = url;
    m_bCheckVersion = false;

    // 获取当前的时间戳，设置下载的临时文件名称
    QDateTime dateTime = QDateTime::currentDateTime();
    QString date = dateTime.toString("yyyyMMdd_hhmmss-zzz");
    m_strFileTemp = qApp->applicationDirPath() + QString("/download/%1.tmp").arg(date);

    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    m_pReply = this->get(request);
    connect(m_pReply, SIGNAL(downloadProgress(qint64, qint64)),
            this, SIGNAL(downloadProgress(qint64, qint64)));
    connect(m_pReply, SIGNAL(readyRead()), this, SLOT(sltReadFiles()));
}

/**
 * @brief DownloadNetworkManager::readyRead
 */
void DownloadNetworkManager::sltReadFiles()
{
#ifdef __arm__
    m_strFileName = qApp->applicationDirPath() + "/download/fire-app.tar.bz2";
#else
    auto header = m_pReply->header(QNetworkRequest::ContentDispositionHeader);
    QString strFileName = header.toString();
    int index = strFileName.indexOf("filename=");
    m_strFileName = strFileName.mid(index + 9, strFileName.length() - index - 9);
#endif

    // 写文件-形式为追加
    QFile file(m_strFileTemp);
    if (file.open(QIODevice::Append))
        file.write(m_pReply->readAll());
    file.close();
}

/**
 * @brief DownloadNetworkManager::replyFinished
 * @param reply
 */
void DownloadNetworkManager::replyFinished(QNetworkReply *reply)
{
    // 获取响应的信息，状态码为200表示正常
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    // 无错误返回
    if (reply->error() == QNetworkReply::NoError)
    {
        // 判断
        if (m_bCheckVersion) {
            parseVersionInfo(reply->readAll());
            return;
        }
        else {
            // 首先判断文件是否存在
            if (QFile::exists(m_strFileName))
            {
                QFile::remove(m_strFileName);
            }

            // 复制文件
            bool bOk = QFile::rename(m_strFileTemp, m_strFileName);
            qDebug() << "download ok" << bOk << m_strFileName;

            // 下载完成
            emit signalDownFinish(m_strFileName);
        }
    }
    else
    {
        QString strError = reply->errorString();
        qDebug() << "Error:" << strError;
        emit signalVersionInfo("err", "网络错误,更新失败！");
    }

    emit replyFinished(statusCode.toInt());
}

/**
 * @brief DownloadNetworkManager::onAuthenticationRequest
 * @param authenticator
 */
void DownloadNetworkManager::onAuthenticationRequest(QNetworkReply *, QAuthenticator *authenticator)
{
    QByteArray password;
    password.append("123456");
    password = QByteArray::fromBase64(password);

    QString strPassword(password);

    authenticator->setUser("wang");
    authenticator->setPassword(strPassword);
}


void DownloadNetworkManager::parseVersionInfo(const QByteArray &data)
{
    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);
    if (jsonError.error == QJsonParseError::NoError) {
        //解析数据
        if (json.isObject()) {
            QJsonObject jsonObj = json.object();
            // 获取服务器最新版本号
            QString strAppVer = jsonObj.value("verNum").toString();
            QString strVersionInfo = jsonObj.value("verInfo").toString();
            emit signalVersionInfo(strAppVer, strVersionInfo);
        }
    }
    else {
        qDebug() << "has error" << jsonError.errorString() << jsonError.error;
    }


}



/**
 * @brief DownloadNetworkManager::GetFileMd5
 * 获取文件的MD5信息
 * @param name
 * @return
 */
QString DownloadNetworkManager::GetFileMd5(const QString &name)
{
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly)) return QString();
    QByteArray ba = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
    file.close();
    return ba.toHex().toUpper();
}
