#ifndef UPLOAD_H
#define UPLOAD_H

#include <QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QNetworkAccessManager>
#include <QNetworkReply>

using namespace std;

namespace Ui{
	class Upload;
}

class Upload: public QDialog
{
	Q_OBJECT

public:
	explicit Upload(QWidget *parent = 0);

	void upload(QString file_name, QUrl url);

	private slots:

	void replyFinished(QNetworkReply*);
	void upLoadError(QNetworkReply::NetworkError errorCode);
	void OnUploadProgress(qint64 bytesSent, qint64 bytesTotal);

private:

	QNetworkAccessManager *_uploadManager;
	QNetworkReply *_reply;
	QUrl _url;

	Ui::Upload *ui;
};

#endif // !UPLOAD_H



