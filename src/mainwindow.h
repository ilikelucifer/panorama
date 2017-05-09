#ifndef MAININDOW_H
#define MAININDOW_H

#include <fstream>

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTextCodec>
#include <opencv2/opencv.hpp>


//Qt通信
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkSession>
#include <QAuthenticator>
#include <QTimer>



//解析xml文件
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>

#include <string>
#include <direct.h>
#include "folderimgs.h"
#include "renderwindow.h"
#include "algorithms.h"
#include "myImageView.h"
#include <sstream>
#include "imgGraphicsView.h"
#include "query.h"
#include "stiProcess.h"


#define __STI_DEBUG__  0

#define ONE_OVER_255  (0.003921568)

#define CALIB_SIZE (1500)  //6099 当前程序太耗内存
#define FULL_SIZE (3000)

#define IMG_NUM 2



#define CALIB_RADIUS_RATIO_65 (0.7011215255735)
#define CALIB_RADIUS_RATIO_90 (0.8906040751915)
#define S_25_OVER_180  (0.1388888888888)

const Size full_resolution = Size2i(9216, 3456);

const int nHTTP_TIME = 15000; //15秒

//相机命令枚举
enum CameraCommand
{
	PHOTO_MODE = 0,
	START_PHOTO,
	PHOTO_RESOLUTION_HIGH,
	PHOTO_RESOLUTION_MIDDLE,
	PHOTO_RESOLUTION_LOW,

	VIDEO_MODE,
	START_RECORD,
	STOP_RECORD,
	VIDEO_FHD,
	VIDEO_HD,
	VIDEO_WVGA,
	VIDEO_VGA,

	GET_FREE_SPACE,
	GET_BATTERY_STATUS,
	CLEAR_SD
};


enum language
{
	english = 0, chinese
};


const QString camHttpAdress = "http://192.168.1.254/";

const QString camCommandList[15] =
{
	camHttpAdress + "?custom=1&cmd=3001&par=0",	//photo mode
	camHttpAdress + "?custom=1&cmd=1001",		//start photo
	camHttpAdress + "?custom=1&cmd=1002&par=0",	//photo resolution high
	camHttpAdress + "?custom=1&cmd=1002&par=1",	//photo resolution middle
	camHttpAdress + "?custom=1&cmd=1002&par=5", //photo resolution low

	camHttpAdress + "?custom=1&cmd=3001&par=1",	//video mode
	camHttpAdress + "?custom=1&cmd=2001&par=1",	//start record
	camHttpAdress + "?custom=1&cmd=2001&par=0",	//stop record
	camHttpAdress + "?custom=1&cmd=2002&par=0",	//move size full hd
	camHttpAdress + "?custom=1&cmd=2002&par=1",	//move size hd
	camHttpAdress + "?custom=1&cmd=2002&par=2",	//move size wvga
	camHttpAdress + "?custom=1&cmd=2002&par=3",	//move size vga

	camHttpAdress + "?custom=1&cmd=3017",		//get free space of sd card
	camHttpAdress + "?custom=1&cmd=3019",		//get battery level
	camHttpAdress + "?custom=1&cmd=4004"		//clear sd all
};


const QString batteryStatus[7] =
{
	"75%~100%",
	"50%~75%",
	"25%~50%",
	"5%~25%",
	"<5%",
	"charge",
	"unknow"
};


namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();



private:

	QImage Mat2QImage(InputArray src);

	void initMem();

	void composePano();

	void imgProcessFromMotion(QPointF center, double r, double ang, int idx);

	void readMaps();
	void readHDMaps();
	void readMasks();
	void readCommonParams();

	void updateIndividualMaps(int idx=-1);

	bool requestImgFromCam(const QString& imName);
	bool fetchImgFromCam(const QString& path, const QString& imName, int counter = 1);
	bool postOrderToCam(const QString& command);
	QString nameGenerator(const QString& imName, int secs);

	void writeImgs(const QString& name, QByteArray& data);

	bool uploadFile(const QString& file);

	void addMarkers(InputArray in);

	bool captureImg(const QString& path, bool update);

	void checkPathExistOrNo(const QString& file);

	void checkWlanStatus();
	bool getConnectedWiFiName();

	void appTest();
	void cloudTest();

signals:

private slots :

	void on_pushButton_cam_clicked();
	void on_pushButton_open_clicked();
	void on_pushButton_render_clicked();
	void on_pushButton_mode_clicked();
	void on_pushButton_save_clicked();
	void on_pushButton_load_clicked();
	void on_pushButton_upload_clicked();
	void on_pushButton_openPano_clicked();
	void on_pushButton_testOnline_clicked();
	void on_pushButton_testOffline_clicked();
	void on_pushButton_autoStitch_clicked();
	void on_pushButton_app_cloud_switch_clicked();
	void on_pushButton_showDebug_clicked();
	void on_imgRadiusChanged(double arg);
	void on_imgMoved(QPointF p);
	void on_imgRotated(double ang);
	void on_sliderReleased();

	void on_pushButton_sd_clear_clicked();
	void on_pushButton_get_sd_volume_clicked();
	void on_pushButton_get_power_clicked();

	void on_renderImgChanged();

	void requestTimeout();

	void wifiLinkResult();

private:

	QNetworkAccessManager* m_pNetworkManager;//网络管理类
	QNetworkReply* m_pNetworkReply; //封装请求返回信息
	QTimer* m_pTimer; //请求超时计时器

	Mat srcImg[IMG_NUM];
	Mat scaleSrcImg[IMG_NUM];	//为了快速验证算法，添加的缩放图像
	Mat correctImg[IMG_NUM];  //鱼眼展开校正后的图像
	Mat maskImg[IMG_NUM];		//mask裁剪并边缘过渡处理（方便融合）的图像
	Mat stitchImg[IMG_NUM];	//最终的等待拼接的图像，由maskImg平移到正确的位置得到
	Mat stitchImg_2[IMG_NUM];

	Mat _panoPreview;       //存储硬拼全景图
	Mat _panoStitch; //存储stitch精确拼接后的全景图
	Mat _panoApp;
	Mat _panoCloud;

	Mat cutMask;	//单一校正后图像的mask
	Mat cutMask_2;

	//标定时对应的低分辨率的map
	Mat mapX, mapY; //标准归一化校正map
	Mat smapX[IMG_NUM], smapY[IMG_NUM]; //根据每个镜头自身参数得到的个性化map

	//云端测试用高分辨率map
	Mat HDmapX, HDmapY; //标准归一化校正map

	QString QProPath; //工程文件路径
	string commonParamPath; //公共参数配置文件所在目录
	QString testPath;
	bool app_cloud_switch;

	QString _wlanName;

	RenderWindow *_renderWindow;

	//交互模式：实时模式/非阻塞模式
	int _activ_idx;
	bool isRTMode;
	bool firstRun;
	bool _showDebugImg;

	double _scale;	

	//lens 参数
	double _mapCurve;
	double _halfFov;
	double _fuseBand;

	bool render_pano_changed;

	language lang;

	Ui::MainWindow *ui;
};



#endif