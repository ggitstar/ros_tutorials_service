#include "/opt/ros/kinetic/include/ros/ros.h"
#include "ros_tutorials_service/SrvTutorial.h"

int main(int argc,char **argv){
    ros::init(argc,argv,"service_client");
    ros::NodeHandle nh;

//    if(argc!=3){
//        ROS_INFO("cmd:rosrun ros_tutorials_service service_clientarg0arg1");
//        ROS_INFO("arg0:double number,arg1:double number");
//        return 0;
//    }

    //クライアントサーバ宣言
    //srvファイルを用いてros_tutorial_service_clientを宣言
    //サービス名はros_tutorial_srv
    ros::ServiceClient ros_tutorials_service_client=
        nh.serviceClient<ros_tutorials_service::SrvTutorial>
        ("ros_tutorial_srv");

    //サービスメッセージ型のオブジェクト宣言
    ros_tutorials_service::SrvTutorial srv;
    //roslaunchから起動する場合
    int a=1,b=2;
    nh.getParam("a",a);
    nh.getParam("b",b);
    srv.request.a=a;
    srv.request.b=b;
//    srv.request.a=atoll(argv[1]);
//    srv.request.b=atoll(argv[2]);

    //サービス要請をし、受け付けられたら返された値を出力
    if(ros_tutorials_service_client.call(srv)){
        ROS_INFO("send srv, srv_request.a and b: %ld %ld",(long int)srv.request.a,(long int)srv.request.b);
        ROS_INFO("receive srv, %ld",(long int)srv.response.result);
    }
    else{
        ROS_ERROR("faild to call service");
        return 1;
    }
    return 0;
}