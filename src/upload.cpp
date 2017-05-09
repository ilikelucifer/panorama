#include <QFile>
#include "upload.h"
#include "ui_upload.h"

Upload::Upload(QWidget *parent):
QDialog(parent),
ui(new Ui::Upload)
{
	ui->setupUi(this);

	setFixedSize(this->width(), this->height());

	_uploadManager = new QNetworkAccessManager(this);
}


void Upload::upload(QString file_name, QUrl url)
{
	QFile xml_file(file_name);

	//准备文件
	xml_file.open(QIODevice::ReadOnly);
	int file_lenth = xml_file.size();
	QDataStream in(&xml_file);
	char* buf = new char[file_lenth];
	in.readRawData(buf, file_lenth);
	xml_file.close();

	//准备头信息
	QNetworkRequest netRequest;
	netRequest.setUrl(url);
	netRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
	netRequest.setRawHeader("filename", xml_file.fileName().toUtf8());

	//准备数据
	QByteArray arr = QByteArray(buf, file_lenth);
	_reply = _uploadManager->post(netRequest, arr);

	connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
	connect(_reply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(OnUploadProgress(qint64, qint64)));
}


void Upload::replyFinished(QNetworkReply* rep)
{

}


void Upload::upLoadError(QNetworkReply::NetworkError errorCode)
{

}


void Upload::OnUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{

}