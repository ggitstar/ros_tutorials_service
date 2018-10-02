#include "/opt/ros/kinetic/include/ros/ros.h"
#include "ros_tutorials_service/SrvTutorial.h"

#define PLUS 1
#define MINUS 2
#define MULTI 3
#define DIVISION 4
int g_operator=PLUS;

//サービス要請があった場合呼び出される関数
bool calculation(ros_tutorials_service::SrvTutorial::Request &req,
                ros_tutorials_service::SrvTutorial::Response &res)
{
    switch(g_operator){
        case PLUS:
            res.result=req.a+req.b;break;
        case MINUS:
            res.result=req.a-req.b;break;
        case MULTI:
            res.result=req.a*req.b;break;
        case DIVISION:
            if(req.b==0){
                res.result=0;break;}
            else{
                res.result=req.a/req.b;break;}
        default:
            res.result=req.a+req.b;break;
    }
    //res.result=req.a+req.b;

    ROS_INFO("request: x=%ld,y=%ld",(long int)req.a,(long int)req.b);
    ROS_INFO("sending back respoce: %ld",(long int)res.result);
    return true;

}

int main(int argc,char **argv){
    ros::init(argc,argv,"service_server");
    ros::NodeHandle nh;
    //roslaunchから起動する場合はいらない
    //nh.setParam("calculation_method",PLUS);

    //サービスサーバ宣言
    //srvファイルを用いてros_tutorial_service_serverを宣言
    //サービス名はros_tutorial_srvで、要請があった時の関数を登録
    ros::ServiceServer ros_tutorials_service_server=
        nh.advertiseService("ros_tutorial_srv",calculation);

    ROS_INFO("ready srv server!");
    ros::Rate r(10);
    while(1){
        nh.getParam("calculation_method",g_operator);
        ros::spinOnce();
        r.sleep();
    }
    //ros::spin();
    return 0;

}