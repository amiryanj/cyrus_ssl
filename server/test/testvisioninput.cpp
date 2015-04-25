#include "testvisioninput.h"
#include "../vision/VisionFilter.h"
#include "../../shared/utility/generalmath.h"
#include "../paramater-manager/parametermanager.h"
#include "../ai/SSLGame.h"

TestInput::TestInput()
{    
    ParameterManager* pm = ParameterManager::getInstance();
    if( (Color)pm->get<int>("general.game.our_color") == SSL::Blue )   {
        our_robots[0] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robots[1] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robots[2] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robots[3] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robots[4] = wrapper_packet.mutable_detection()->add_robots_blue();
        our_robots[5] = wrapper_packet.mutable_detection()->add_robots_blue();

        opponent_robots[0] = wrapper_packet.mutable_detection()->add_robots_yellow();
        opponent_robots[1] = wrapper_packet.mutable_detection()->add_robots_yellow();
        opponent_robots[2] = wrapper_packet.mutable_detection()->add_robots_yellow();
        opponent_robots[3] = wrapper_packet.mutable_detection()->add_robots_yellow();
        opponent_robots[4] = wrapper_packet.mutable_detection()->add_robots_yellow();
        opponent_robots[5] = wrapper_packet.mutable_detection()->add_robots_yellow();

    } else {
        our_robots[0] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robots[1] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robots[2] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robots[3] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robots[4] = wrapper_packet.mutable_detection()->add_robots_yellow();
        our_robots[5] = wrapper_packet.mutable_detection()->add_robots_yellow();

        opponent_robots[0] = wrapper_packet.mutable_detection()->add_robots_blue();
        opponent_robots[1] = wrapper_packet.mutable_detection()->add_robots_blue();
        opponent_robots[2] = wrapper_packet.mutable_detection()->add_robots_blue();
        opponent_robots[3] = wrapper_packet.mutable_detection()->add_robots_blue();
        opponent_robots[4] = wrapper_packet.mutable_detection()->add_robots_blue();
        opponent_robots[5] = wrapper_packet.mutable_detection()->add_robots_blue();
    }

    our_robots[0]->set_robot_id(0);
    our_robots[0]->set_x(pm->get<float>("test_input.vision.our_team.0.x"));
    our_robots[0]->set_y(pm->get<float>("test_input.vision.our_team.0.y"));
    our_robots[0]->set_orientation(pm->get<float>("test_input.vision.our_team.0.orien"));
    our_robots[0]->set_pixel_x(pm->get<float>("test_input.vision.our_team.0.v_x"));
    our_robots[0]->set_pixel_y(pm->get<float>("test_input.vision.our_team.0.v_y"));

    our_robots[1]->set_robot_id(1);
    our_robots[1]->set_x(pm->get<float>("test_input.vision.our_team.1.x"));
    our_robots[1]->set_y(pm->get<float>("test_input.vision.our_team.1.y"));
    our_robots[1]->set_orientation(pm->get<float>("test_input.vision.our_team.1.orien"));
    our_robots[1]->set_pixel_x(pm->get<float>("test_input.vision.our_team.1.v_x"));
    our_robots[1]->set_pixel_y(pm->get<float>("test_input.vision.our_team.1.v_y"));

    our_robots[2]->set_robot_id(2);
    our_robots[2]->set_x(pm->get<float>("test_input.vision.our_team.2.x"));
    our_robots[2]->set_y(pm->get<float>("test_input.vision.our_team.2.y"));
    our_robots[2]->set_orientation(pm->get<float>("test_input.vision.our_team.2.orien"));
    our_robots[2]->set_pixel_x(pm->get<float>("test_input.vision.our_team.2.v_x"));
    our_robots[2]->set_pixel_y(pm->get<float>("test_input.vision.our_team.2.v_y"));

    our_robots[3]->set_robot_id(3);
    our_robots[3]->set_x(pm->get<float>("test_input.vision.our_team.3.x"));
    our_robots[3]->set_y(pm->get<float>("test_input.vision.our_team.3.y"));
    our_robots[3]->set_orientation(pm->get<float>("test_input.vision.our_team.3.orien"));
    our_robots[3]->set_pixel_x(pm->get<float>("test_input.vision.our_team.3.v_x"));
    our_robots[3]->set_pixel_y(pm->get<float>("test_input.vision.our_team.3.v_y"));

    our_robots[4]->set_robot_id(4);
    our_robots[4]->set_x(pm->get<float>("test_input.vision.our_team.4.x"));
    our_robots[4]->set_y(pm->get<float>("test_input.vision.our_team.4.y"));
    our_robots[4]->set_orientation(pm->get<float>("test_input.vision.our_team.4.orien"));
    our_robots[4]->set_pixel_x(pm->get<float>("test_input.vision.our_team.4.v_x"));
    our_robots[4]->set_pixel_y(pm->get<float>("test_input.vision.our_team.4.v_y"));

    our_robots[5]->set_robot_id(5);
    our_robots[5]->set_x(pm->get<float>("test_input.vision.our_team.5.x"));
    our_robots[5]->set_y(pm->get<float>("test_input.vision.our_team.5.y"));
    our_robots[5]->set_orientation(pm->get<float>("test_input.vision.our_team.5.orien"));
    our_robots[5]->set_pixel_x(pm->get<float>("test_input.vision.our_team.5.v_x"));
    our_robots[5]->set_pixel_y(pm->get<float>("test_input.vision.our_team.5.v_y"));


// -------- Opponent Robots ----------
    opponent_robots[0]->set_robot_id(0);
    opponent_robots[0]->set_x(pm->get<float>("test_input.vision.opponent_team.0.x"));
    opponent_robots[0]->set_y(pm->get<float>("test_input.vision.opponent_team.0.y"));
    opponent_robots[0]->set_orientation(pm->get<float>("test_input.vision.opponent_team.0.orien"));
    opponent_robots[0]->set_pixel_x(pm->get<float>("test_input.vision.opponent_team.0.v_x"));
    opponent_robots[0]->set_pixel_y(pm->get<float>("test_input.vision.opponent_team.0.v_y"));

    opponent_robots[1]->set_robot_id(1);
    opponent_robots[1]->set_x(pm->get<float>("test_input.vision.opponent_team.1.x"));
    opponent_robots[1]->set_y(pm->get<float>("test_input.vision.opponent_team.1.y"));
    opponent_robots[1]->set_orientation(pm->get<float>("test_input.vision.opponent_team.1.orien"));
    opponent_robots[1]->set_pixel_x(pm->get<float>("test_input.vision.opponent_team.1.v_x"));
    opponent_robots[1]->set_pixel_y(pm->get<float>("test_input.vision.opponent_team.1.v_y"));

    opponent_robots[2]->set_robot_id(2);
    opponent_robots[2]->set_x(pm->get<float>("test_input.vision.opponent_team.2.x"));
    opponent_robots[2]->set_y(pm->get<float>("test_input.vision.opponent_team.2.y"));
    opponent_robots[2]->set_orientation(pm->get<float>("test_input.vision.opponent_team.2.orien"));
    opponent_robots[2]->set_pixel_x(pm->get<float>("test_input.vision.opponent_team.2.v_x"));
    opponent_robots[2]->set_pixel_y(pm->get<float>("test_input.vision.opponent_team.2.v_y"));

    opponent_robots[3]->set_robot_id(3);
    opponent_robots[3]->set_x(pm->get<float>("test_input.vision.opponent_team.3.x"));
    opponent_robots[3]->set_y(pm->get<float>("test_input.vision.opponent_team.3.y"));
    opponent_robots[3]->set_orientation(pm->get<float>("test_input.vision.opponent_team.3.orien"));
    opponent_robots[3]->set_pixel_x(pm->get<float>("test_input.vision.opponent_team.3.v_x"));
    opponent_robots[3]->set_pixel_y(pm->get<float>("test_input.vision.opponent_team.3.v_y"));

    opponent_robots[4]->set_robot_id(4);
    opponent_robots[4]->set_x(pm->get<float>("test_input.vision.opponent_team.4.x"));
    opponent_robots[4]->set_y(pm->get<float>("test_input.vision.opponent_team.4.y"));
    opponent_robots[4]->set_orientation(pm->get<float>("test_input.vision.opponent_team.4.orien"));
    opponent_robots[4]->set_pixel_x(pm->get<float>("test_input.vision.opponent_team.4.v_x"));
    opponent_robots[4]->set_pixel_y(pm->get<float>("test_input.vision.opponent_team.4.v_y"));

    opponent_robots[5]->set_robot_id(5);
    opponent_robots[5]->set_x(pm->get<float>("test_input.vision.opponent_team.5.x"));
    opponent_robots[5]->set_y(pm->get<float>("test_input.vision.opponent_team.5.y"));
    opponent_robots[5]->set_orientation(pm->get<float>("test_input.vision.opponent_team.5.orien"));
    opponent_robots[5]->set_pixel_x(pm->get<float>("test_input.vision.opponent_team.5.v_x"));
    opponent_robots[5]->set_pixel_y(pm->get<float>("test_input.vision.opponent_team.5.v_y"));


    ball = wrapper_packet.mutable_detection()->add_balls();
    ball->set_x(pm->get<float>("test_input.vision.ball.x"));
    ball->set_y(pm->get<float>("test_input.vision.ball.y"));

    ball->set_pixel_x(pm->get<float>("test_input.vision.ball.v_x"));
    ball->set_pixel_y(pm->get<float>("test_input.vision.ball.v_y"));
}

void TestInput::updateVisionInput()
{
    static int frame_counter = 0;
    frame_counter ++;
    double current_time = currentTimeMSec();
    wrapper_packet.mutable_detection()->set_camera_id(5);
    wrapper_packet.mutable_detection()->set_t_capture(current_time);
    wrapper_packet.mutable_detection()->set_t_sent(current_time);
    wrapper_packet.mutable_detection()->set_frame_number(frame_counter);    

    VisionFilter::getInstance()->update(wrapper_packet);
}

void TestInput::updateWorldModel()
{
    static int counter = 0;
    counter += 10;

    for(int i=0; i<6; i++) {
        world->updateRobotState(SSLGame::getInstance()->ourColor(), i,
                               Vector3D(our_robots[i]->x(), our_robots[i]->y(), our_robots[i]->orientation()),
                               Vector3D(our_robots[i]->pixel_x(), our_robots[i]->pixel_y(), 0),
                               true);
    }
    for(int i=0; i<6; i++) {
        world->updateRobotState(SSLGame::getInstance()->opponentColor(), i,
                               Vector3D(opponent_robots[i]->x(), opponent_robots[i]->y(), opponent_robots[i]->orientation()),
                               Vector3D(opponent_robots[i]->pixel_x(), opponent_robots[i]->pixel_y(), 0),
                               true);
    }

    world->updateBallState(0,
                           Vector2D(ball->x(), ball->y() + counter % (int)FIELD_WIDTH),
                           Vector2D(ball->pixel_x(), ball->pixel_y()),
                           Vector2D(0.0 ,0.0));

}
