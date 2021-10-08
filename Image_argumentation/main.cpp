#include<opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img_origin, img_small;
	img_origin = imread("CAM1.bmp", IMREAD_COLOR);
	resize(img_origin, img_small, Size(400, 400));
	//imshow("color", img_small);
	//imshow("color", img_origin);


	//int height = img_small.rows; //행
	//int width = img_small.cols; //렬
	int height = img_origin.rows; //행
	int width = img_origin.cols; //렬

	//---------- 이미지 회전 ------------------
	Mat R1 = getRotationMatrix2D(Point(width / 2.0, height / 2.0), //회전 할 때 중심점
		5, // 회전 각도(양수는 반시계 방향, 음수는 시계 방향
		1); //이미지 배율. 1이면 원래 크기
	Mat R2 = getRotationMatrix2D(Point(width / 2.0, height / 2.0), //회전 할 때 중심점
		-5, // 회전 각도(양수는 반시계 방향, 음수는 시계 방향
		1); //이미지 배율. 1이면 원래 크기

	//회전 행렬 R을 이미지 img_origin에 적용한다.
	Mat img_rotated_45, img_rotated_45_2;
	//warpAffine(img_small, img_rotated_45, R1, Size(width, height));
	//warpAffine(img_small, img_rotated_45_2, R2, Size(width, height));
	warpAffine(img_origin, img_rotated_45, R1, Size(width, height));
	warpAffine(img_origin, img_rotated_45_2, R2, Size(width, height));
	//imshow("rotation1", img_rotated_45);
	//imshow("rotation2", img_rotated_45_2);

	
	//---------- 이미지 이동 ------------
	Mat M(2, 3, CV_64F, Scalar(0.0));

	M.at<double>(0, 0) = 1;
	M.at<double>(1, 1) = 1;
	M.at<double>(0, 2) = -40;
	M.at<double>(1, 2) = -20;

	//이동 행렬을 이미지에 적용함.
	Mat img_translation;
	//warpAffine(img_small, img_translation, M, Size(width, height));
	warpAffine(img_origin, img_translation, M, Size(width, height));

	//imshow("translation", img_translation);

	// ------- 이미지 밝기 조절 ---------
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