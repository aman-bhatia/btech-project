#include "seamcarving.h"
#include "ui_seamcarving.h"

using namespace std;
using namespace cv;


//--------------------------------------------------------Seam Carving--------------------------------------//

Mat SeamCarving::seamNormal(Mat img, int cols_to_delete, int mode){
    if (mode == HOR){
        img = img.t();
        if (this->obj)
            bin_img = bin_img.t();
    }

    int wait = 60;
    for (int z=0;z<cols_to_delete;z++){

        // Calculate Laplacian
        Mat blured, gray, dst, grad;
        GaussianBlur( img, blured, Size(3,3), 0, 0, BORDER_DEFAULT );
        cvtColor( blured, gray, COLOR_BGR2GRAY );
        Laplacian( gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );
        convertScaleAbs( dst, grad );

        vector< vector<node> > table(0);
        for (int i=0;i<img.rows;i++){
            vector<node> temp(0);
            for (int j=0;j<img.cols;j++){
                node n{0,grad.at<uchar>(i,j)};

                if (obj){
                    if (bin_img.at<Vec3b>(i,j) == Vec3b({0,0,255}) )
                        n.energy = INT_MIN;
                    else if (bin_img.at<Vec3b>(i,j) == Vec3b({0,255,0}) )
                        n.energy = INT_MAX;
                }

                temp.push_back(n);
            }
            table.push_back(temp);
        }

        for (int i=0;i<img.rows;i++){
            for (int j=0;j<img.cols;j++){
                if (i==0){
                    continue;
                } else if (j==0){		// extreme left
                    long long int mid = table[i-1][j].energy;
                    long long int right = table[i-1][j+1].energy;
                    long long int min_energy = min(mid,right);
                    table[i][j].energy += min_energy;
                    if (min_energy == mid)
                        table[i][j].path = 0;
                    else
                        table[i][j].path = 1;
                } else if (j==img.cols-1){		// extreme right
                    long long int mid = table[i-1][j].energy;
                    long long int left = table[i-1][j-1].energy;
                    long long int min_energy = min(mid,left);
                    table[i][j].energy += min_energy;
                    if (min_energy == mid)
                        table[i][j].path = 0;
                    else
                        table[i][j].path = -1;
                } else {
                    long long int mid = table[i-1][j].energy;
                    long long int left = table[i-1][j-1].energy;
                    long long int right = table[i-1][j+1].energy;
                    long long int min_energy = min(right,min(mid,left));
                    table[i][j].energy += min_energy;
                    if (min_energy == mid)
                        table[i][j].path = 0;
                    else if (min_energy == left)
                        table[i][j].path = -1;
                    else
                        table[i][j].path = 1;
                }
            }
        }

        // find the column corresponding to minimum energy
        int min_col = 0;
        long long int min_energy = table[img.rows-1][0].energy;
        for (int i=1;i<img.cols;i++){
            if (table[img.rows-1][i].energy < min_energy){
                min_energy = table[img.rows-1][i].energy;
                min_col = i;
            }
        }

        // paint the corresponding seam RED
        int index = min_col;
        for (int j=img.rows-1; j>=0; j--){
            img.at<Vec3b>(j,index) = {0,0,255};
            index += table[j][index].path;
        }

        if (mode == HOR)
            img = img.t();

        imshow("Seam Deletion",img);
        waitKey(wait);

        if (mode == HOR)
            img = img.t();

        // remove the corresponding column
        index = min_col;
        for (int i=img.rows-1;i>=0;i--){
            for (int j=index;j<img.cols-1;j++){
                img.at<Vec3b>(i,j) = img.at<Vec3b>(i,j+1);
                if (obj){
                    bin_img.at<Vec3b>(i,j) = bin_img.at<Vec3b>(i,j+1);
                }
            }
            index += table[i][index].path;
        }
        Rect crop_region(0, 0, img.cols-1, img.rows);
        img = img(crop_region);
        if (obj){
            bin_img = bin_img(crop_region);
        }
    }

    if (mode == HOR)
        img = img.t();

    return img;
}


Mat seamInsertion(Mat orig_img, int cols_to_insert, int mode){
    Mat img = orig_img.clone();

    if (mode == HOR)
        img = img.t();

    vector< vector< Point > > seams(0);
    for (int z=0;z<cols_to_insert;z++){
        vector< Point > seam(0);

        // Calculate Laplacian
        Mat blured, gray, dst, grad;
        GaussianBlur( img, blured, Size(3,3), 0, 0, BORDER_DEFAULT );
        cvtColor( blured, gray, COLOR_BGR2GRAY );
        Laplacian( gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );
        convertScaleAbs( dst, grad );

        vector< vector<node> > table(0);
        for (int i=0;i<img.rows;i++){
            vector<node> temp(0);
            for (int j=0;j<img.cols;j++){
                node n{0,grad.at<uchar>(i,j)};
                temp.push_back(n);
            }
            table.push_back(temp);
        }

        for (int i=0;i<img.rows;i++){
            for (int j=0;j<img.cols;j++){
                if (i==0){
                    continue;
                } else if (j==0){		// extreme left
                    long long int mid = table[i-1][j].energy;
                    long long int right = table[i-1][j+1].energy;
                    long long int min_energy = min(mid,right);
                    table[i][j].energy += min_energy;
                    if (min_energy == mid)
                        table[i][j].path = 0;
                    else
                        table[i][j].path = 1;
                } else if (j==img.cols-1){		// extreme right
                    long long int mid = table[i-1][j].energy;
                    long long int left = table[i-1][j-1].energy;
                    long long int min_energy = min(mid,left);
                    table[i][j].energy += min_energy;
                    if (min_energy == mid)
                        table[i][j].path = 0;
                    else
                        table[i][j].path = -1;
                } else {
                    long long int mid = table[i-1][j].energy;
                    long long int left = table[i-1][j-1].energy;
                    long long int right = table[i-1][j+1].energy;
                    long long int min_energy = min(right,min(mid,left));
                    table[i][j].energy += min_energy;
                    if (min_energy == mid)
                        table[i][j].path = 0;
                    else if (min_energy == left)
                        table[i][j].path = -1;
                    else
                        table[i][j].path = 1;
                }
            }
        }

        // find the column corresponding to minimum energy
        int min_col = 0;
        long long int min_energy = table[img.rows-1][0].energy;
        for (int i=1;i<img.cols;i++){
            if (table[img.rows-1][i].energy < min_energy){
                min_energy = table[img.rows-1][i].energy;
                min_col = i;
            }
        }

        // remove the corresponding column
        int index = min_col;
        for (int i=img.rows-1;i>=0;i--){
            seam.push_back(Point(i,index));
            for (int j=index;j<img.cols-1;j++){
                img.at<Vec3b>(i,j) = img.at<Vec3b>(i,j+1);
            }
            index += table[i][index].path;
        }
        Rect crop_region(0, 0, img.cols-1, img.rows);
        img = img(crop_region);
        seams.push_back(seam);
    }

    int wait = 60;

    img = orig_img.clone();
    if (mode == HOR)
        img = img.t();

    for (int i=0;i<seams.size();i++){
        copyMakeBorder(img,img,0,0,0,1,0);
        for (int j=0;j<seams[i].size();j++){
            int row_index = seams[i][j].x;
            int col_index = seams[i][j].y;
            for (int k=img.cols-1;k>col_index;k--){
                img.at<Vec3b>(row_index,k) = img.at<Vec3b>(row_index,k-1);
            }
            img.at<Vec3b>(row_index,col_index) = img.at<Vec3b>(row_index,col_index-1)/2 + img.at<Vec3b>(row_index,col_index+1)/2;
        }

        if (mode == HOR)
            img = img.t();

        imshow("Seam Insertion",img);
        waitKey(wait);

        if (mode == HOR)
            img = img.t();
    }

    if (mode == HOR)
        img = img.t();

    return img;
}

//------------------------------ Draw save/remove objects-----------------//

bool left_button_down = false;
bool right_button_down = false;
Mat obj_img;
Mat bin_img;
string draw_winname = "Draw to explicitly save/remove objects";

void obj_draw(int event, int x, int y, int /*flags*/, void* /*param*/){
    if (event == EVENT_LBUTTONDOWN){
        left_button_down = true;
    }else if (event == EVENT_RBUTTONDOWN){
        right_button_down = true;
    } else if (event == EVENT_MOUSEMOVE && right_button_down){
        int rad = 5;
        circle(obj_img, Point(x,y), rad, RED, -1);
        circle(bin_img, Point(x,y), rad, RED, -1);
        imshow(draw_winname,obj_img);
    } else if (event == EVENT_MOUSEMOVE && left_button_down){
        int rad = 5;
        circle(obj_img, Point(x,y), rad, GREEN, -1);
        circle(bin_img, Point(x,y), rad, GREEN, -1);
        imshow(draw_winname,obj_img);
    } else if (event == EVENT_LBUTTONUP){
        left_button_down = false;
    } else if (event == EVENT_RBUTTONUP){
        right_button_down = false;
    }
}


SeamCarving::SeamCarving(std::string src_image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeamCarving)
{
    ui->setupUi(this);
    this->img_name = src_image;

    Mat img = imread(img_name);

    ui->label_num_cols->setText(QString::fromStdString(to_string(img.cols)));
    ui->label_num_rows->setText(QString::fromStdString(to_string(img.rows)));

    ui->lineEdit_num_cols_del->setValidator(new QIntValidator(0,img.cols-2,this));
    ui->lineEdit_num_rows_del->setValidator(new QIntValidator(0,img.rows-2,this));

    ui->lineEdit_num_cols_insert->setValidator(new QIntValidator(0,img.cols,this));
    ui->lineEdit_num_rows_insert->setValidator(new QIntValidator(0,img.rows,this));
}

SeamCarving::~SeamCarving()
{
    delete ui;
}

void SeamCarving::on_pushButton_save_rem_clicked()
{
    QMessageBox::information(this, tr("Usage Information"),tr("Press right mouse button and drag over an object to delete it. Similarly, press left mouse button and drag over an object to save it."));
    obj = true;
    obj_img = imread(img_name);
    bin_img = Mat::zeros(obj_img.rows, obj_img.cols,obj_img.type());
    namedWindow(draw_winname,WINDOW_AUTOSIZE);
    setMouseCallback( draw_winname, obj_draw, NULL);
    imshow(draw_winname, obj_img);
    waitKey();
    destroyAllWindows();
}

void SeamCarving::on_buttonBox_accepted()
{
    Mat img = imread(img_name);
    int rows_to_delete = ui->lineEdit_num_rows_del->text().toInt();
    int cols_to_delete = ui->lineEdit_num_cols_del->text().toInt();

    if (cols_to_delete) img = seamNormal(img,cols_to_delete,VER);
    if (rows_to_delete) img = seamNormal(img,rows_to_delete,HOR);
    if (cols_to_delete or rows_to_delete){
        imwrite("../../Seam Carving Deletion.jpg",img);
        imshow("Seam Deletion",img);
        waitKey();
        destroyAllWindows();
    }
    obj = false;

    int rows_to_insert = ui->lineEdit_num_rows_insert->text().toInt();
    int cols_to_insert = ui->lineEdit_num_cols_insert->text().toInt();
    if (cols_to_insert) img = seamInsertion(img,cols_to_insert,VER);
    if (rows_to_insert) img = seamInsertion(img,rows_to_insert,HOR);
    if (cols_to_insert or rows_to_insert){
        imwrite("../../Seam Carving Insertion.jpg",img);
        imshow("Seam Insertion",img);
        waitKey();
        destroyAllWindows();
    }
}
