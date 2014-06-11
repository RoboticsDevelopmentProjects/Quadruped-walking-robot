#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

typedef struct
{
	int all_area;//���ʐ�
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
    // �J��������̃r�f�I�L���v�`��������������
    CvCapture *videoCapture = cvCreateCameraCapture( 1 );
    if( videoCapture == NULL )
    {
		printf("Camera Device Not Connect!!\n");
        exit(1);
    }


    // �E�B���h�E���쐬����
    //char windowName[] = "Capture Window";
    //cvNamedWindow( windowName, CV_WINDOW_AUTOSIZE );

	cvNamedWindow("image_in");
	cvNamedWindow("image_gray");
	cvNamedWindow("image_out");

	image_in =cvQueryFrame(videoCapture);                          // �����t���[���擾
    image_gray=cvCreateImage(cvSize(image_in->width,image_in->height), IPL_DEPTH_8U,1);  // �O���[�X�P�[��
    image_out =cvCreateImage(cvSize(image_in->width,image_in->height), IPL_DEPTH_8U,3);  // �J���[

    // �����L�[�����������܂ŁA���[�v������Ԃ�
    while( cvWaitKey( 1 ) == -1 )
    {
        // �J��������1�t���[���擾����
        image_in = cvQueryFrame( videoCapture );
		cvCvtColor(image_in, image_gray, CV_BGR2GRAY);       // �O���[�X�P�[���֕ϊ�
        cvThreshold(image_gray,image_gray, 50, 255, CV_THRESH_BINARY);  // 2�l��

		cvShowImage("image_in",image_in);                   // 1�t���[��Window�\��
        cvShowImage("image_gray",image_gray);                 // 1�t���[��Window�\��
        cvShowImage("image_out",image_out);                  // 1�t���[��Window�\��

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
        // �E�B���h�E�ɉ摜��\������
        cvShowImage( "image_in", image_in );
		cvShowImage( "image_gray", image_gray );
		cvShowImage( "image_out", image_out );
    }


    // �r�f�I�L���v�`�����������
    cvReleaseCapture( &videoCapture );
	//cvReleaseImage(&image);

    // �E�B���h�E��j������
    cvDestroyAllWindows();

    return 0;
}
