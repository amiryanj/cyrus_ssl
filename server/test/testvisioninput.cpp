#include "testvisioninput.h"
#include "../vision/VisionFilter.h"
#include "../../common/math/sslmath.h"
#include "../paramater-manager/parametermanager.h"

TestVisionInput::TestVisionInput()
{
    SSL_DetectionRobot* our_robots[4] = {0, 0, 0, 0};
    SSL_DetectionRobot* opp_robots[4] = {0, 0, 0, 0};
    ParameterManager* pm = ParameterManager::getInstance();
    if( (Color)pm->get<int>("general.game.our_color") == SSL::Blue )   {
        our_robots[0] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robots[1] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robots[2] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robots[3] = wrapper_packet.mutable_detection()->add_robots_blue();

        opp_robots[0] = wrapper_packet.mutable_detection()->add_robots_yellow();
        opp_robots[1] = wrapper_packet.mutable_detection()->add_robots_yellow();
//        opp_robots[2] = wrapper_packet.mutable_detection()->add_robots_yellow();
//        opp_robots[3] = wrapper_packet.mutable_detection()->add_robots_yellow();

    } else {
        our_robots[0] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robots[1] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robots[2] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robots[3] = wrapper_packet.mutable_detection()->add_robots_yellow();

        opp_robots[0] = wrapper_packet.mutable_detection()->add_robots_blue();
        opp_robots[1] = wrapper_packet.mutable_detection()->add_robots_blue();
//        opp_robots[2] = wrapper_packet.mutable_detection()->add_robots_blue();
//        opp_robots[3] = wrapper_packet.mutable_detection()->add_robots_blue();
    }

    our_robots[0]->set_robot_id(0);
    our_robots[0]->set_x(-3800.0);
    our_robots[0]->set_y(200.0);
    our_robots[0]->set_orientation(0.5);

    our_robots[1]->set_robot_id(1);
    our_robots[1]->set_x(2900.0);
    our_robots[1]->set_y(1300.0);
    our_robots[1]->set_orientation(0.5);

    our_robots[2]->set_robot_id(2);
    our_robots[2]->set_x(2800.0);
    our_robots[2]->set_y(1100.0);
    our_robots[2]->set_orientation(0.5);

    our_robots[3]->set_robot_id(3);
    our_robots[3]->set_x(rand() % 3000);
    our_robots[3]->set_y(rand() % 4000);
    our_robots[3]->set_orientation(0.5);

// -------- Opponent Robots ----------
    opp_robots[0]->set_robot_id(0);
    opp_robots[0]->set_x(-3300.0);
    opp_robots[0]->set_y(-20.0);
    opp_robots[0]->set_orientation(M_PI*0.95);

    opp_robots[1]->set_robot_id(1);
    opp_robots[1]->set_x(2000.0);
    opp_robots[1]->set_y(1800.0);
    opp_robots[1]->set_orientation(0.6);

//    opp_robots[2]->set_robot_id(2);
//    opp_robots[2]->set_x(-2400.0);
//    opp_robots[2]->set_y(3100.0);
//    opp_robots[2]->set_orientation(0.5);

//    opp_robots[3]->set_robot_id(3);
//    opp_robots[3]->set_x(-(rand() % 3000));
//    opp_robots[3]->set_y((rand() % 5000));
//    opp_robots[3]->set_orientation(0.5);


    SSL_DetectionBall* ball = wrapper_packet.mutable_detection()->add_balls();
    ball->set_x(-3500);
    ball->set_y(-0);
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
