#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QLabel>
#include <QTextEdit>
#include <QUuid>
#include <QDebug>
#include <QListWidgetItem>
#include <QListWidget>
#include <QTreeWidget>
#include <QListView>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QStringListModel>
#include <QTime>
#include <QTimer>
#include <QStandardItemModel>

#include "libcbdetect/boards_from_corners.h"
#include "libcbdetect/config.h"
#include "libcbdetect/find_corners.h"
#include "libcbdetect/plot_boards.h"
#include "libcbdetect/plot_corners.h"

#include "libDockingPanes/DockingPaneManager.h"
#include "libDockingPanes/DockingPaneBase.h"

#include "setting.h"

// define index of dock array for various display
enum enumDockID {
    DOCK_IMAGE = 1,   // show load images from folder
    DOCK_OUTPUT = 2,  // operation info and logs
    DOCK_REP_ERR_IMAGE = 3,  // reprojection error of full image
    DOCK_REP_ERR_POINT = 4,  // reprojection error of single point
    DOCK_REP_CAMERA = 5  // camera position in world coordinate

};
/// Qss config
#define USE_QSS_DEFAULT            0
#define USE_QSS_DARK               1
#define USE_QSS_LIGHT              2

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void timerDateTimeout(); //时间更新槽函数，状态栏显示时间
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionImages_triggered();
    void on_actionCalibrationBoard_triggered();
    void on_actionViewImage_triggered();
    void on_actionViewOutput_triggered();
    void on_actionViewRepErrImage_triggered();
    void on_actionViewRepErrPoint_triggered();

    void on_actionViewCamera_triggered();

    void on_actionTheme_triggered();

    void on_actionParameters_triggered();

private:
    Ui::MainWindow *ui;
    setting *uiSetting;

    int curTheme = USE_QSS_DEFAULT;
    QGraphicsView *grvOutput;
    QGraphicsScene* scene; // 场景
    QGraphicsPixmapItem* srcPixmap;	// 对象元素
    QImage* srcImage;	// QImage对象
    QSize oldMaxSize, oldMinSize;
    DockingPaneManager *dockingPaneManager;
    DockingPaneBase *dockingPanes[20];

    // 标定板上每行、列的角点数（格子数-1）
    cv::Size boardSize;
    // 实际测量得到的标定板上每个棋盘格的物理尺寸，单位mm
    cv::Size squareSize;
    // 存放图像的旋转向量，每一副图像的旋转向量为一个mat
    std::vector<cv::Mat> rvecs;
    // 存放图像的平移向量，每一副图像的平移向量为一个mat
    std::vector<cv::Mat> tvecs;                                                                      // 存放右图像的平移向量，每一副图像的平移向量为一个mat
    cv::Mat cameraMatrix = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0));
    cv::Mat cameraDistCoeffs = cv::Mat(1, 5, CV_32FC1, cv::Scalar::all(0)); //相机内参矩阵和畸变矩阵
    cv::Mat interR,interE,interF; // 定义旋转矩阵R，本质矩阵E，基础矩阵F
    cv::Vec3d outerT; // 定义旋转矩阵平移向量
	double  reprojectionError; // 重投影误差
	cv::Mat R_L, R_R, P_L, P_R, Q; // 定义左图像和右图像的旋转矩阵R，投影矩阵P，重投影矩阵Q
    // 保存标定板上角点的三维坐标
    std::vector<std::vector<cv::Point3f>> objectPoints;
    // 保存标定板上找到的角点的二维坐标
    std::vector<std::vector<cv::Point2f>> imagePoints;

    int stopCalib = 0;
    QString imagePath = "";
    /// indicate there are some changes of xml file
    /// and remind user to save it when exit
    int flagXmlChanged = 0;


    void initDockingPanes();
    QLabel *createLabel(QString string);
    QTreeView *createFileTreeView();
    QListView *createListView();
    QWidget *createToolBox();
    QTextEdit *createTextEdit();

    void cbdetectFindChessboard(const char* str, cbdetect::CornerType corner_type, std::vector<cv::Point2f>& corner);
    void opencv4FindChessboardSB();

};
#endif // MAINWINDOW_H
