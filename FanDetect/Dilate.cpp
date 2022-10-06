#include "general.hpp"

void General::fanDilate(Mat &src)
{
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(2, 2));
    Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(1, 1));

    dilate(src, src, element_dilate_1);// why only Dilate1?
    erode(src, src, element_erode_1);
    erode(src, src, element_erode_2);
    erode(src, src, element_erode_3);
}

void General::ArmorDilate(Mat& src){
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(1, 1));

    dilate(src, src, element_dilate_1);
    erode(src, src, element_erode_1);
}

void General::FlowStripFanDilate(Mat& src) {
	Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(1, 1));

	dilate(src, src, element_dilate_1);
	erode(src, src, element_erode_1);
	erode(src, src, element_erode_2);
	erode(src, src, element_erode_3);
}

void General::FlowStripDilate(Mat& src) {
	Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(1, 1));

	dilate(src, src, element_dilate_1);
	erode(src, src, element_erode_1);
	erode(src, src, element_erode_2);
	erode(src, src, element_erode_3);
}