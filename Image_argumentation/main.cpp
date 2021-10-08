#include<opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img_origin, img_small;
	img_origin = imread("CAM1.bmp", IMREAD_COLOR);
	resize(img_origin, img_small, Size(400, 400));
	//imshow("color", img_small);
	//imshow("color", img_origin);


	//int height = img_small.rows; //��
	//int width = img_small.cols; //��
	int height = img_origin.rows; //��
	int width = img_origin.cols; //��

	//---------- �̹��� ȸ�� ------------------
	Mat R1 = getRotationMatrix2D(Point(width / 2.0, height / 2.0), //ȸ�� �� �� �߽���
		5, // ȸ�� ����(����� �ݽð� ����, ������ �ð� ����
		1); //�̹��� ����. 1�̸� ���� ũ��
	Mat R2 = getRotationMatrix2D(Point(width / 2.0, height / 2.0), //ȸ�� �� �� �߽���
		-5, // ȸ�� ����(����� �ݽð� ����, ������ �ð� ����
		1); //�̹��� ����. 1�̸� ���� ũ��

	//ȸ�� ��� R�� �̹��� img_origin�� �����Ѵ�.
	Mat img_rotated_45, img_rotated_45_2;
	//warpAffine(img_small, img_rotated_45, R1, Size(width, height));
	//warpAffine(img_small, img_rotated_45_2, R2, Size(width, height));
	warpAffine(img_origin, img_rotated_45, R1, Size(width, height));
	warpAffine(img_origin, img_rotated_45_2, R2, Size(width, height));
	//imshow("rotation1", img_rotated_45);
	//imshow("rotation2", img_rotated_45_2);

	
	//---------- �̹��� �̵� ------------
	Mat M(2, 3, CV_64F, Scalar(0.0));

	M.at<double>(0, 0) = 1;
	M.at<double>(1, 1) = 1;
	M.at<double>(0, 2) = -40;
	M.at<double>(1, 2) = -20;

	//�̵� ����� �̹����� ������.
	Mat img_translation;
	//warpAffine(img_small, img_translation, M, Size(width, height));
	warpAffine(img_origin, img_translation, M, Size(width, height));

	//imshow("translation", img_translation);

	// ------- �̹��� ��� ���� ---------
	//Mat img_bright = img_small + 10;
	//Mat img_dark = img_small - 10;
	Mat img_bright = img_origin + 10; 
	Mat img_dark = img_origin - 10;

	//imshow("bright", img_bright);
	//imshow("img_dark", img_dark);

	imwrite("CAM1_rotation_1.bmp", img_rotated_45);
	imwrite("CAM1_rotation_2.bmp", img_rotated_45_2);
	imwrite("CAM1_translation.bmp", img_translation);
	imwrite("CAM1_bright.bmp", img_bright);
	imwrite("CAM1_dark.bmp", img_dark);

	waitKey(0);

	return 0;
}