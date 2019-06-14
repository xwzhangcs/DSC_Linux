#pragma once

#undef ERROR
#undef STRICT

#include <caffe/caffe.hpp>
#include <opencv2/opencv.hpp>
#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Regression {
public:
	Regression(std::string proto_file, std::string model_file);
	std::vector<float> get_pred(cv::Mat const &im);
private:
	void wrap_input_layer(std::vector<cv::Mat> *input_channels);
	void preprocess(cv::Mat const &im, std::vector<cv::Mat> *input_channels);
	boost::shared_ptr<caffe::Net<float> > net;
	cv::Size input_size;
	int n_channels;
};
