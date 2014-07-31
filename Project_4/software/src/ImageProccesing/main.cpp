#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

typedef struct
{
	int all_area;//総面積
	int white;
	int black;
}binarization;
binarization space={0};

IplImage *image_gray;
IplImage *image_in;
IplImage *image_out;

int x,y,w,h;
int ofs,idx;
int r,g,b;
unsigned char *pix;
int pixCnt;

int main()
{
    // カメラからのビデオキャプチャを初期化する
    CvCapture *videoCapture = cvCreateCameraCapture( 1 );
    if( videoCapture == NULL )
    {
		printf("Camera Device Not Connect!!\n");
        exit(1);
    }


    // ウィンドウを作成する
    //char windowName[] = "Capture Window";
    //cvNamedWindow( windowName, CV_WINDOW_AUTOSIZE );

	cvNamedWindow("image_in");
	cvNamedWindow("image_gray");
	cvNamedWindow("image_out");

	image_in =cvQueryFrame(videoCapture);                          // 初期フレーム取得
    image_gray=cvCreateImage(cvSize(image_in->width,image_in->height), IPL_DEPTH_8U,1);  // グレースケール
    image_out =cvCreateImage(cvSize(image_in->width,image_in->height), IPL_DEPTH_8U,3);  // カラー

    // 何かキーが押下されるまで、ループをくり返す
    while( cvWaitKey( 1 ) == -1 )
    {
        // カメラから1フレーム取得する
        image_in = cvQueryFrame( videoCapture );
		cvCvtColor(image_in, image_gray, CV_BGR2GRAY);       // グレースケールへ変換
        cvThreshold(image_gray,image_gray, 50, 255, CV_THRESH_BINARY);  // 2値化

		cvShowImage("image_in",image_in);                   // 1フレームWindow表示
        cvShowImage("image_gray",image_gray);                 // 1フレームWindow表示
        cvShowImage("image_out",image_out);                  // 1フレームWindow表示

		/*pix = (unsigned char*)image->imageData;
		pixCnt = image->width*image->height;

		for( y=0; y<image->height; y++ ) {
			ofs = y*image->widthStep;
				for( x=0; x<image->width; x++ ) {
					idx = ofs + x*3;
				}
		}

		r = pix[idx+2];
		g = pix[idx+1];
		b = pix[idx];

		printf("B:%d\n",b);*/
        // ウィンドウに画像を表示する
        cvShowImage( "image_in", image_in );
		cvShowImage( "image_gray", image_gray );
		cvShowImage( "image_out", image_out );
    }


    // ビデオキャプチャを解放する
    cvReleaseCapture( &videoCapture );
	//cvReleaseImage(&image);

    // ウィンドウを破棄する
    cvDestroyAllWindows();

    return 0;
}
