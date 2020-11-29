//CommonDefine.h
//

#ifndef _COMMON_DEFINE_H_
#define _COMMON_DEFINE_H_


#include "../common/MultiLinkList.h"

#ifdef _NANOC_WINDOWS_
//#define _CNN_SHOW_GUI_
//#define _CNN_SHOW_CURV_
#endif

#ifdef _CNN_SHOW_GUI_
#define _CNN_SHOW_LOSS_
#define _CNN_SHOW_CONV_
#endif

#include "../NN/mt19937ar.h"

//Define Maxium Hidden Layer
#define MAX_HIDDEN_LAYER		30 + 2

//Define Maxium Simulation Range
#define MAX_SIMULATION_RANGE_INPUT	1.0
#define MAX_SIMULATION_RANGE_OUTPUT	1.0

#define WEIGHT	((2.0*(double)rand()/RAND_MAX) - 1)//(((EFTYPE)(rand() % 10))/100.0)//��ʼ��ȨֵΪ0��Ҳ���Գ�ʼ�����ֵ 
#define BIAS	((2.0*(double)rand()/RAND_MAX) - 1)//0.1//��ʼ����ֵΪ0��Ҳ���Գ�ʼ�����ֵ

//#define ETA_W    0.95   //Ȩֵ������ adjustWeight
#define ETA_W    0.03   //Ȩֵ������ adjustWeight
#define ETA_B    0.01    //��ֵ������ adjustBias

#define T_ERROR	0.075		//����������������
#define T_TIMES	10000000	//ѵ������

#if 0
#ifdef _NANOC_WINDOWS_
#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>

#ifndef max
#define max(x, y) (x > y ? x : y)
#endif
#ifndef min
#define min(x, y) (x < y? x : y);
#endif


//Get sample_number samples in XML file,from the start column. 
void get_input_label(std::string filename, cv::Mat& input, cv::Mat& label, int sample_num, int start=0);
#endif
#endif
#endif