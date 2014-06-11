#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

IplImage *image,*img_out;

//unsigned char r,g,b;
int x,y;
int bpp;

int main()
{
	CvCapture *videoCapture = cvCreateCameraCapture( 1 );

	if( videoCapture == NULL )
    {
		printf("Camera Device Not Connect!!\n");
        exit(1);
    }
	
	cvNamedWindow("image");

	img_out = cvQueryFrame(videoCapture);
	bpp=img_out->nChannels*img_out->depth/8;

	while( cvWaitKey( 1 ) == -1 )
    {
		img_out = cvQueryFrame( videoCapture );
		//img_out =cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U,3);
		//int i=0;
		for(y=0;y<img_out->height;y++){
			for(x=0;x<img_out->width;x++){
				int i = (y*img_out->width+x)*bpp;
				int b = (unsigned char)img_out->imageData[i];
				int g = (unsigned char)img_out->imageData[i+1];
				int r = (unsigned char)img_out->imageData[i+2];
				//int b = (unsigned char)img_out->imageData[img_out->widthStep * y + x*3];
				//int g = (unsigned char)img_out->imageData[img_out->widthStep * y + x*3+1];
				//int r = (unsigned char)img_out->imageData[img_out->widthStep * y + x*3+2];
				printf("R:%d G:%d B:%d\n",r,g,b);
				if(b<170){
					b=255;
					r=255;
					c=255;
				}else{
					b=r=c=0;
				}
			}
		}
		cvShowImage( "image", img_out );
	}
	cvReleaseCapture( &videoCapture );

	return 0;
}
