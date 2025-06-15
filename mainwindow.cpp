#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

#include <iostream>
#include "fstream"
#include <thread>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
using namespace cv;



void MainWindow::cbdetectFindChessboard(const char* str, cbdetect::CornerType corner_type, vector<Point2f>& corner) {
    cbdetect::Corner corners;
    std::vector<cbdetect::Board> boards;
    cbdetect::Params params;
    params.corner_type = corner_type;
    params.detect_method = cbdetect::LocalizedRadonTransform;
    static int printCornerPoint = 0;

    cv::Mat img = cv::imread(str, cv::IMREAD_COLOR);

    auto t1 = std::chrono::high_resolution_clock::now();
    cbdetect::find_corners(img, corners, params);
    auto t2 = std::chrono::high_resolution_clock::now();
    cbdetect::plot_corners(img, corners);
    auto t3 = std::chrono::high_resolution_clock::now();
    cbdetect::boards_from_corners(img, corners, boards, params);
    auto t4 = std::chrono::high_resolution_clock::now();
    printf("Find corners took: %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0);
    printf("Find boards took: %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count() / 1000.0);
    printf("Total took: %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0 + std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count() / 1000.0);
    cout << "board.size = " << boards.size() << endl;
	if (boards.size() > 0)
	{
		cout << "board[0].idx.size() = " << boards[0].idx.size() << endl;
		cout << "board[0].idx[0].size() = " << boards[0].idx[0].size() << endl;
	}
	else
	{
		cout << "No board found." << endl;
	}
    std::vector<cv::Point2d> board_corners;
    cbdetect::plot_boards(img, corners, boards, params, board_corners);
    cout << "board_corners.size = " << board_corners.size() << endl;

    if (printCornerPoint == 0) {
        cout << "board_corners.point = [\n";
        for (auto c : board_corners) {
            corner.push_back(Point2f(c.x, c.y));
            cout << c.x << "," << c.y << "\n";
        }
        cout << "]\n";
		printCornerPoint = 1;
	}
	else {
		for (auto c : board_corners) {
			corner.push_back(Point2f(c.x, c.y));
		}
	}
}


void MainWindow::opencv4FindChessboardSB() {

    Size squareSize, boardSize, imageSize;
	squareSize = cv::Size(50, 50); // 棋盘格的物理尺寸，单位mm
    boardSize.width = 18;
    boardSize.height = 17;
    int winSize = 11;
    int64 t[10] = { 0 };
    static int printCornerPoint = 0;

    Mat image, imageGray;
    //vector<vector<Point2f> > imagePoints;
    // 保存标定板上角点的三维坐标,假设标定板放在世界坐标系中z=0的平面上
    std::vector<cv::Point3f> objectPoint;
    for (int i = 0; i < boardSize.height; i++)
        for (int j = 0; j < boardSize.width; j++)
            objectPoint.push_back(Point3f(j * squareSize.width,
                i * squareSize.height, 0));

    for (int i = 1; i <= 10; i++)
    {
        string filename = "../images/chessboard/" + to_string(i) + ".bmp";
		cout << "calibration filename: " << filename << endl;
        image = imread(filename);
        imageSize = image.size();
        vector<Point2f> corners;
        cvtColor(image, imageGray, COLOR_BGR2GRAY);
        bool found;
        //found = findChessboardCorners(image, boardSize, pointbuf,
        //    CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_FILTER_QUADS);
        found = findChessboardCornersSB(image, boardSize, corners,
            CALIB_CB_EXHAUSTIVE | CALIB_CB_ACCURACY);
        if (found) {
            // 将当前图像的角点存入imagePoints中
            imagePoints.push_back(corners);
			// 将当前图像的物理坐标存入objectPoints中
            objectPoints.push_back(objectPoint);
            //cornerSubPix(imageGray, pointbuf, Size(winSize, winSize),
            //    Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
            drawChessboardCorners(image, boardSize, Mat(corners), found);
            //std::ofstream myfile;
            string txtName = "corner" + to_string(i) + ".txt";
            //myfile.open(txtName, ios::out);
            if (printCornerPoint == 0) {
                cout << "board_corners.point = [\n";
                for (unsigned int j = 0; j < corners.size(); j++)
                {
                    float x_pos = corners.at(j).x;
                    float y_pos = corners.at(j).y;
                    cout << x_pos << "," << y_pos << "\n";
                    //保存角点坐标
                    //myfile << x_pos << " " << y_pos << std::endl;
                }
                cout << "]\n";
                printCornerPoint = 1;
            }
            //myfile.close();
        }
        //cv::namedWindow("image", WINDOW_NORMAL);
        //cv::imshow("image", image);

        QImage* tmpImage = new QImage(image.data, image.cols, image.rows,
                   static_cast<int>(image.step), QImage::Format_RGB888);
        srcPixmap->setPixmap(QPixmap::fromImage(tmpImage->rgbSwapped()));


		if (stopCalib)
		{
            cout << "stop calibration" << endl;
			cv::destroyAllWindows();
			return;
		}
        cv::waitKey(1000);
    }
    cout << "start calibrateCamera\n";
    std::cout << "Object points size: " << objectPoints.size() << std::endl;
    std::cout << "Image points size: " << imagePoints.size() << std::endl;
    for (size_t i = 0; i < objectPoints.size(); ++i) {
        std::cout << "objectPoints[" << i << "] size: " << objectPoints[i].size() << std::endl;
        std::cout << "imagePoints[" << i << "] size: " << imagePoints[i].size() << std::endl;
    }

    reprojectionError = calibrateCamera(objectPoints, imagePoints,
      imageSize, cameraMatrix, cameraDistCoeffs, rvecs, tvecs, CALIB_FIX_K3);

    cout << "reprojectionError = " << reprojectionError << endl
         << "cameraMatrix = " << cameraMatrix  << endl
         << "cameraDistCoeffs = " << cameraDistCoeffs << endl
         << endl;

    return;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , uiSetting(new setting)
{
    //设置只显示错误日志
    cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_ERROR);

    ui->setupUi(this);


    QTimer *timerDate = new QTimer(this);
    timerDate->start(1000);
    connect(timerDate, SIGNAL(timeout()),this,SLOT(timerDateTimeout()));

    showMaximized();
    initDockingPanes();


    scene = new QGraphicsScene();
    srcPixmap = new QGraphicsPixmapItem();
    srcImage = new QImage();
    Mat *srcMat = new cv::Mat();

    // 将QGraphicsPixmapItem类添加到QGraphicsScene
    // 对象元素-->场景
    scene->addItem(srcPixmap);
    // 将QGraphicsScene添加到QGraphicsView
    // 场景-->视图
    grvOutput->setScene(scene);
    // 设置QGraphicsView更新
    grvOutput->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    *srcMat = imread("../images/chessboard/1.bmp");
    int64 t[10] = { 0 };
    // 图片文件不为空，转换为要显示的对象元素
    if (!srcMat->empty())
    {
		t[0] = getTickCount();
        QImage* tmpImage = new QImage(srcMat->data, srcMat->cols, srcMat->rows,
            static_cast<int>(srcMat->step),
            QImage::Format_RGB888);
        t[1] = getTickCount();
        srcPixmap->setPixmap(QPixmap::fromImage(
            tmpImage->rgbSwapped()));       
        float scale = float(grvOutput->width()) / srcPixmap->pixmap().width();
		// 设置缩放比例
        //ui->grvOutput->scale(scale, scale);
        grvOutput->fitInView(grvOutput->scene()->sceneRect(),Qt::KeepAspectRatio);

        *srcImage = QImage(srcMat->data, srcMat->cols, srcMat->rows,
                          static_cast<int>(srcMat->step),
                          QImage::Format_RGB888);
        srcPixmap->setPixmap(QPixmap::fromImage(
                              srcImage->rgbSwapped()));

        cout << "Open Successful\n";
        delete tmpImage;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerDateTimeout()
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString( "yyyy-MM-dd hh:mm:ss");
    //lblStatusbarTime->setText(timestr);
    // remind user there are some changes to xml file
    QString sWindowTitle = ("Camera Calibration");
    // make sure only change window tile once  << not implement yet
    if(flagXmlChanged){
        this->setWindowTitle(sWindowTitle + " *");
    }
    else{
        this->setWindowTitle(sWindowTitle);
    }

}
// initialize docking for various display
void MainWindow::initDockingPanes()
{

    dockingPaneManager = new DockingPaneManager;

    grvOutput = new QGraphicsView;

    dockingPaneManager->setClientWidget(grvOutput);

    setCentralWidget(dockingPaneManager->widget());

    dockingPanes[DOCK_OUTPUT] =
        dockingPaneManager->createPane(QUuid::createUuid().toString(),
            "Output and Log", createTextEdit(),
            QSize(200, 200), DockingPaneManager::dockBottom);
    dockingPanes[DOCK_IMAGE] =
        dockingPaneManager->createPane(QUuid::createUuid().toString(),
            "Images", createFileTreeView(),
            QSize(200, 200), DockingPaneManager::dockLeft, nullptr);
    dockingPanes[DOCK_REP_ERR_IMAGE] =
        dockingPaneManager->createPane(QUuid::createUuid().toString(),
            "RepErrImage", createTextEdit(),
            QSize(100, 200), DockingPaneManager::dockRight, nullptr);
    /*
    dockingPanes[DOCK_REP_ERR_POINT] =
        dockingPaneManager->createPane(QUuid::createUuid().toString(),
            "RepErrPoint", createTextEdit(),
            QSize(200, 200), DockingPaneManager::dockRight, dockingPanes[DOCK_REP_ERR_IMAGE]);
    dockingPanes[DOCK_REP_CAMERA] =
        dockingPaneManager->createPane(QUuid::createUuid().toString(),
            "Camera in World", createLabel("Camera in World"),
            QSize(200, 200), DockingPaneManager::dockRight, dockingPanes[DOCK_REP_ERR_POINT]);
    dockingPaneManager->hidePane(dockingPanes[DOCK_REP_CAMERA]);
    */
}


QLabel *MainWindow::createLabel(QString string)
{
    auto label = new QLabel(string);

    label->setAlignment(Qt::AlignCenter);

    return(label);
}
// Create the dockwidget that displays a content of file system folder
QTreeView *MainWindow::createFileTreeView()
{
    QFileSystemModel* fsModel = new QFileSystemModel;
    fsModel->setRootPath(QDir::currentPath());

    QTreeView* fileTreeView = new QTreeView();
    fileTreeView->setModel(fsModel);
    fileTreeView->setRootIndex(fsModel->index(QDir::currentPath()));
    return fileTreeView;
}
// Create the dockwidget that display list names of some Qt classes
QListView *MainWindow::createListView()
{
    QStringListModel* slModel = new QStringListModel();
    QStringList classList;
    classList << "QWidget" << "QPushButton" << "QImage" << "QCheckBox" << "QWindow" << "QTextEdit" << "QScrollBar" << "QPoint";
    slModel->setStringList(classList);

    QListView* strView = new QListView();
    strView->setModel(slModel);
    return strView;
}
// Create the dockwidget that display list of some standard widgets
QWidget *MainWindow::createToolBox()
{
    QWidget* toolBox = new QWidget();
    QFormLayout* formLayout = new QFormLayout();
    formLayout->setLabelAlignment(Qt::AlignRight);
    toolBox->setLayout(formLayout);

    formLayout->addRow("Push Button", new QPushButton("OK"));
    formLayout->addRow("Tool Button", new QToolButton());
    formLayout->addRow("Radio Button", new QRadioButton());
    formLayout->addRow("Check Box", new QCheckBox());
    formLayout->addRow("Spin Box", new QSpinBox());
    formLayout->addRow("Line Edit", new QLineEdit());
    formLayout->addRow("Combo Box", new QComboBox());
    return toolBox;
}
// Create the dockwidget that display a text edit widget
QTextEdit *MainWindow::createTextEdit()
{
    QTextEdit* textEdit = new QTextEdit();
    textEdit->setReadOnly(true);
    textEdit->setText(R"(Output text)");
    return textEdit;
}


void MainWindow::on_actionStart_triggered()
{
    stopCalib = 0;
    

    //opencv4FindChessboardSB();
    
    Size squareSize = cv::Size(50, 50); // 棋盘格的物理尺寸，单位mm
    Size boardSize = cv::Size(18, 17); // 标定板上每行、列的角点数（格子数*2-1）
    Mat imgSrc = imread("../images/chessboard/1.bmp");
    Size imageSize = imgSrc.size();


    
    // 保存标定板上角点的三维坐标,假设标定板放在世界坐标系中z=0的平面上
    std::vector<cv::Point3f> objectPoint;
    for (int i = 0; i < boardSize.width; i++)
        for (int j = 0; j < boardSize.height; j++)
            objectPoint.push_back(Point3f(i * squareSize.width,
                j * squareSize.height, 0));
    for (int i = 1; i <= 10; i++)
    {
        vector<Point2f> vecCorner;
        string filename = "../images/chessboard/" + to_string(i) + ".bmp";
        cout << "calibration filename: " << filename << endl;
        cbdetectFindChessboard(filename.c_str(), cbdetect::SaddlePoint, vecCorner);
		// 将当前图像的角点存入imagePoints中
		imagePoints.push_back(vecCorner);
        // 将当前图像的物理坐标存入objectPoints中
        objectPoints.push_back(objectPoint);
        cv::waitKey(1000);
    }
	cout << "start calibrateCamera\n";
	std::cout << "Object points size: " << objectPoints.size() << std::endl;
	std::cout << "Image points size: " << imagePoints.size() << std::endl;
	for (size_t i = 0; i < objectPoints.size(); ++i) {
		std::cout << "objectPoints[" << i << "] size: " << objectPoints[i].size() << std::endl;
		std::cout << "imagePoints[" << i << "] size: " << imagePoints[i].size() << std::endl;
	}
    

	reprojectionError = calibrateCamera(objectPoints, imagePoints,
        imageSize, cameraMatrix, cameraDistCoeffs, rvecs, tvecs, CALIB_FIX_K3);

	cout << "reprojectionError = " << reprojectionError << endl
		<< "cameraMatrix = " << cameraMatrix << endl
		<< "cameraDistCoeffs = " << cameraDistCoeffs << endl
		<< endl;
    
}

void MainWindow::on_actionStop_triggered()
{
    stopCalib = 1;
}
/// @brief choose image path
void MainWindow::on_actionImages_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        "/home",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        imagePath = dir;
    }
}

void MainWindow::on_actionCalibrationBoard_triggered()
{

}

void MainWindow::on_actionViewImage_triggered()
{
    if(ui->actionViewImage->isChecked())
        dockingPaneManager->showPane(dockingPanes[DOCK_OUTPUT]);
    else
        dockingPaneManager->hidePane(dockingPanes[DOCK_OUTPUT]);
}

void MainWindow::on_actionViewOutput_triggered()
{
    qDebug() << "DOCK_OUTPUT->state" << dockingPanes[DOCK_OUTPUT]->state();
    if(ui->actionViewOutput->isChecked())
        dockingPaneManager->showPane(dockingPanes[DOCK_OUTPUT]);
    else
        dockingPaneManager->hidePane(dockingPanes[DOCK_OUTPUT]);
}

void MainWindow::on_actionViewRepErrImage_triggered()
{
    if(ui->actionViewRepErrImage->isChecked())
        dockingPaneManager->showPane(dockingPanes[DOCK_REP_ERR_IMAGE]);
    else
        dockingPaneManager->hidePane(dockingPanes[DOCK_REP_ERR_IMAGE]);
}

void MainWindow::on_actionViewRepErrPoint_triggered()
{
    return;
    if(ui->actionViewRepErrPoint->isChecked())
        dockingPaneManager->showPane(dockingPanes[DOCK_REP_ERR_POINT]);
    else
        dockingPaneManager->hidePane(dockingPanes[DOCK_REP_ERR_POINT]);
}

void MainWindow::on_actionViewCamera_triggered()
{
    return;
    if(ui->actionViewCamera->isChecked())
        dockingPaneManager->showPane(dockingPanes[DOCK_REP_CAMERA]);
    else
        dockingPaneManager->hidePane(dockingPanes[DOCK_REP_CAMERA]);
}

void MainWindow::on_actionTheme_triggered()
{
    curTheme = (++curTheme) % 3;  // change qss setting
    // set ui qss
    if(curTheme == USE_QSS_DEFAULT)
        qApp->setStyleSheet("");
    else if(curTheme == USE_QSS_DARK){
        QFile f(":qstyle/dark/darkstyle.qss");

        if (!f.exists()) {
            printf("Unable to set dark stylesheet, file not found\n");
        }
        else {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            qApp->setStyleSheet(ts.readAll());
        }
    }
    else if(curTheme == USE_QSS_LIGHT){
        QFile f(":qstyle/light/lightstyle.qss");

        if (!f.exists())   {
            printf("Unable to set light stylesheet, file not found\n");
        }
        else   {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            qApp->setStyleSheet(ts.readAll());
        }
    }
}

void MainWindow::on_actionParameters_triggered()
{
    uiSetting->show();
}
