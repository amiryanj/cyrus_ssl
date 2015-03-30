#include "testvisioninput.h"
#include "../vision/VisionFilter.h"
#include "../../common/math/sslmath.h"
#include "../paramater-manager/parametermanager.h"

TestVisionInput::TestVisionInput()
{
    SSL_DetectionRobot* our_robot[4] = {0, 0};
    ParameterManager* pm = ParameterManager::getInstance();
    if( (Color)pm->get<int>("general.game.our_color") == SSL::Blue )   {
        our_robot[0] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robot[1] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robot[2] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robot[3] = wrapper_packet.mutable_detection()->add_robots_blue();
    } else {
        our_robot[0] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robot[1] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robot[2] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robot[3] = wrapper_packet.mutable_detection()->add_robots_yellow();
    }
    our_robot[0]->set_robot_id(0);
    our_robot[0]->set_x(2900.0);
    our_robot[0]->set_y(200.0);
    our_robot[0]->set_orientation(0.5);

    our_robot[1]->set_robot_id(1);
    our_robot[1]->set_x(2900.0);
    our_robot[1]->set_y(1300.0);
    our_robot[1]->set_orientation(0.5);

    our_robot[2]->set_robot_id(2);
    our_robot[2]->set_x(2800.0);
    our_robot[2]->set_y(1100.0);
    our_robot[2]->set_orientation(0.5);

    usleep(50);
    our_robot[3]->set_robot_id(3);
    int rand_1 = rand();
    int rand_2 = rand();
    our_robot[3]->set_x(rand_1 % 3000);
    our_robot[3]->set_y(rand_2 % 500);
    our_robot[3]->set_orientation(0.5);

    SSL_DetectionBall* ball = wrapper_packet.mutable_detection()->add_balls();
    ball->set_x(1400);
    ball->set_y(-700);
}

void TestVisionInput::check()
{
    static int frame_counter = 0;
    frame_counter ++;
    double current_time = SSL::currentTimeMSec();
    wrapper_packet.mutable_detection()->set_camera_id(0);
    wrapper_packet.mutable_detection()->set_t_capture(current_time);
    wrapper_packet.mutable_detection()->set_t_sent(current_time);
    wrapper_packet.mutable_detection()->set_frame_number(frame_counter);

    VisionFilter::getInstance()->update(wrapper_packet);
}
