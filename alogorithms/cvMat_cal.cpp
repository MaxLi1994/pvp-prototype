#include "type.hpp"

using namespace pvp;

DataBucket& blur(DataBucket &data, Params &params)
{
    cv::Mat src = data.get_opencv_mat("origin");
    cv::Mat dst;
    cv::Size ksize = params.get_opencv_size("ksize");
    cv::blur(src, dst, ksize);
    data.set_opencv_mat("blurred", dst);
    return data;
}

DataBucket& canny(DataBucket &data, Params &params)
{
    cv::Mat src = data.get_opencv_mat("origin");
    cv::Mat edges;
    float threshold1 = params.get_float("threshold1");
    float threshold2 = params.get_float("threshold2");
    cv::Canny(src, edges, threshold1, threshold2);
    data.set_opencv_mat("edges", edges);
    return datas;
}
