#include <opencv/cv.h>
#include <opencv/highgui.h>

int main (int argc, char **argv)
{
  int x, y;
  uchar p[3];
  IplImage *img;

  if (argc != 2 || (img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR)) == 0)
    return -1;

  // (1)画素値（R,G,B）を順次取得し，変更する
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      /* 画素値を直接操作する一例 */
      p[0] = img->imageData[img->widthStep * y + x * 3];        // B
      p[1] = img->imageData[img->widthStep * y + x * 3 + 1];    // G
      p[2] = img->imageData[img->widthStep * y + x * 3 + 2];    // R
      img->imageData[img->widthStep * y + x * 3] = cvRound (p[0] * 0.6 + 10);
      img->imageData[img->widthStep * y + x * 3 + 1] = cvRound (p[1] * 1.0);
      img->imageData[img->widthStep * y + x * 3 + 2] = cvRound (p[2] * 0.0);
    }
  }

  cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image", img);
  cvWaitKey (0);

  cvDestroyWindow ("Image");
  cvReleaseImage (&img);

  return 0;
}
