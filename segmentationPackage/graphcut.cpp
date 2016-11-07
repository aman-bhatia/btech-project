#include "graphcut.h"
#include "ui_graphcut.h"
#include <QMessageBox>

using namespace std;
using namespace cv;

graphCut::graphCut(std::string src_image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphCut)
{
    ui->setupUi(this);
    this->src_image = src_image;
    ui->lineEdit->setValidator(new QIntValidator(0,1000,this));
}

graphCut::~graphCut()
{
    delete ui;
}

void graphCut::increase_smoothness()
{
    cout << "Increasing smoothness... \n";
    smoothness += 5;
    for ( int l1 = 0; l1 < num_labels; l1++ ){
        for (int l2 = 0; l2 < num_labels; l2++ ){
            int cost = (l1==l2) ? 0 : smoothness;
            graph->setSmoothCost(l1,l2,cost);
        }
    }
    cout << "Applying alpha-expansion... ";
    graph->expansion(1);
}

void graphCut::decrease_smoothness()
{
    cout << "Decreasing smoothness... \n";
    smoothness -= 5;
    if (smoothness < 5){
        smoothness = 5;
        return;
    }
    for ( int l1 = 0; l1 < num_labels; l1++ ){
        for (int l2 = 0; l2 < num_labels; l2++ ){
            int cost = (l1==l2) ? 0 : smoothness;
            graph->setSmoothCost(l1,l2,cost);
        }
    }
    cout << "Applying alpha-expansion... ";
    graph->expansion(1);
}

void graphCut::on_buttonBox_accepted()
{
    QMessageBox::information(this, tr("Usage Information"),tr("Press\n 1 to apply alpha-expansion\n 2 to apply alpha-beta swap \n 'i' to increase smmothness \n 'd' to decrease smoothness."));
    num_labels = ui->lineEdit->text().toInt();
    Mat img = imread(this->src_image);

    int width = img.cols;
    int height = img.rows;
    int num_pixels = width*height;

    // Apply kmeans clustering on image
    Mat samples(num_pixels, 3, CV_32F);
    for (int i=0;i<img.rows;i++)
        for (int j=0;j<img.cols;j++)
            for (int z=0;z<3;z++)
                samples.at<float>(j + i*img.cols, z) = img.at<Vec3b>(i,j)[z];

    Mat labels;
    int attempts = 5;
    Mat centers;
    TermCriteria criteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 100, 0.01);
    kmeans(samples, num_labels, labels, criteria, attempts, KMEANS_PP_CENTERS, centers);

    graph = new GCoptimizationGridGraph(width,height,num_labels);

    // first set up data costs individually
    for ( int i = 0; i < num_pixels; i++ ){
        for (int l = 0; l < num_labels; l++ ){
            Scalar v1(centers.at<float>(l,0),centers.at<float>(l,1),centers.at<float>(l,2));
            Scalar v2(samples.at<float>(i,0),samples.at<float>(i,1),samples.at<float>(i,2));
            double cost = norm(v1,v2, NORM_L2);
            graph->setDataCost(i,l,cost);
        }
    }

    // next set up smoothness costs individually
    for ( int l1 = 0; l1 < num_labels; l1++ ){
        for (int l2 = 0; l2 < num_labels; l2++ ){
            int cost = (l1==l2) ? 0 : smoothness;
            graph->setSmoothCost(l1,l2,cost);
        }
    }

    cout << "Before optimization energy is " << graph->compute_energy() << endl;
    graph->expansion(1);
    while(true){
        cout << "After optimization energy is " << graph->compute_energy() << endl;

        Mat gc_image(img.size(), img.type());
        for(int i=0;i<img.rows;i++){
            for(int j=0;j<img.cols;j++){
                int cluster_idx = graph->whatLabel(j + i*img.cols);
                gc_image.at<Vec3b>(i,j)[0] = centers.at<float>(cluster_idx, 0);
                gc_image.at<Vec3b>(i,j)[1] = centers.at<float>(cluster_idx, 1);
                gc_image.at<Vec3b>(i,j)[2] = centers.at<float>(cluster_idx, 2);
            }
        }
        imshow("GC image", gc_image);
        int c = waitKey(0);
        if (c=='1'){
            cout << "Applying alpha-expansion... ";
            graph->expansion(1);
        } else if (c=='2'){
            cout << "Applying alpha-beta swap... ";
            graph->swap(1);
        } else if (c=='i'){
            increase_smoothness();
       } else if (c=='d'){
            decrease_smoothness();
       } else break;
    }
    delete graph;
    destroyAllWindows();
}
