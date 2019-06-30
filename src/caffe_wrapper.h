#pragma once

#undef ERROR
#undef STRICT

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

class CaffeWrapper {
public:
	CaffeWrapper(std::string proto_file, std::string model_file,
		std::string mean_file);
	std::vector<float> get_pred(cv::Mat const &im);
private:
	void set_mean(std::string const &mean_file);
	void wrap_input_layer(std::vector<cv::Mat> *input_channels);
	void preprocess(cv::Mat const &im, std::vector<cv::Mat> *input_channels);
	boost::shared_ptr<caffe::Net<float> > net;
	cv::Size input_size;
	cv::Mat mean;
	int n_channels;
};
