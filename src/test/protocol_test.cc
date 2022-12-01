#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include "../common/protocol.h"
#include "../common/lobby_command.h"
#include "../common/match_state.h"
#include "../common/car_state.h"
#include "../common/match_setup.h"
#include "../common/user_action.h"
#include "socket_test.h"

// // Demonstrate some basic assertions.
// TEST(HelloTest, BasicAssertions) {
//   // Expect two strings not to be equal.
//   EXPECT_STRNE("hello", "world");
//   // Expect equality.
//   EXPECT_EQ(7 * 6, 42);
// }

TEST(Protocolo, SendMessage) {
  SocketTest skt(2);
  Protocol protocol(skt);
  std::string data("String de prueba para test de protocolo.");
  protocol.send_message(data);
  bool was_closed = false;
  std::string recv(protocol.recv_message(&was_closed));
  EXPECT_STREQ(data.c_str(), recv.c_str());
}

TEST(Protocolo, SendLobbyCommand) {
  SocketTest skt(2);
  Protocol protocol(skt);
  LobbyCommand command(3, "payload del comando");
  protocol.send_lobby_command(command);
  bool was_closed = false;
  LobbyCommand recv(protocol.recv_lobby_command(&was_closed));
  uint8_t recv_code = command.get_code();
  std::string recv_payload = command.get_payload();
  EXPECT_EQ(recv_code, 3);
  EXPECT_STREQ(recv_payload.c_str(), "payload del comando");
}

TEST(Protocolo, SendMatchState) {
  SocketTest skt(2);
  Protocol protocol(skt);
  CarState cstate1(
    0, 
    1, 
    76,
    1,
    45,
    45,
    13
  );
  CarState cstate2(
    1, 
    0, 
    100,
    0,
    15,
    37,
    8
  );
  BallState bstate(
    125,
    200, 
    45, 
    3
  );
  std::vector<CarState> cstates;
  cstates.push_back(cstate1);
  cstates.push_back(cstate2);
  MatchState mstate(
    120,
    1,
    1,
    2,
    4,
    bstate,
    cstates
  );
  protocol.send_match_state(mstate);
  bool was_closed = false;
  MatchState recv(protocol.recv_match_state(&was_closed));

  // MatchStateChecks
  EXPECT_EQ(recv.get_time(), 120);
  EXPECT_EQ(recv.get_playing(), 1);
  EXPECT_EQ(recv.get_scorer_1(), 1);
  EXPECT_EQ(recv.get_scorer_2(), 2);
  EXPECT_EQ(recv.get_cars_quantity(), 4);
  
  // BallStateChecks
  BallState recv_ball = recv.get_ball();
  EXPECT_EQ(recv_ball.get_position_x(), 12500);
  EXPECT_EQ(recv_ball.get_position_y(), 20000);
  EXPECT_EQ(recv_ball.get_angle(), 45);
  EXPECT_EQ(recv_ball.get_shot_type(), 3);

  // CarStateChecks
  std::vector<CarState> recv_cars = recv.get_cars();
  CarState recv_car_1 = recv_cars[0]; 
  CarState recv_car_2 = recv_cars[1];
  EXPECT_EQ(recv_car_1.get_id(), 0);
  EXPECT_EQ(recv_car_1.get_nitro_percentage(), 76);
  EXPECT_EQ(recv_car_1.get_nitro_activated(), 1);
  EXPECT_EQ(recv_car_1.is_oriented_right(), 1);
  EXPECT_EQ(recv_car_1.get_angle(), 45);
  EXPECT_EQ(recv_car_1.get_position_x(), 4500);
  EXPECT_EQ(recv_car_1.get_position_y(), 1300); 

  EXPECT_EQ(recv_car_2.get_id(), 1);
  EXPECT_EQ(recv_car_2.get_nitro_percentage(), 100);
  EXPECT_EQ(recv_car_2.get_nitro_activated(), 0);
  EXPECT_EQ(recv_car_2.is_oriented_right(), 0);
  EXPECT_EQ(recv_car_2.get_angle(), 15);
  EXPECT_EQ(recv_car_2.get_position_x(), 3700);
  EXPECT_EQ(recv_car_2.get_position_y(), 800); 
}

TEST(Protocolo, SendMatchSetup) {
  SocketTest skt(2);
  Protocol protocol(skt);
  MatchSetup msetup(
    400,
    200,
    50,
    20,
    10,
    4
  );
  protocol.send_match_setup(msetup);
  bool was_closed = false;
  MatchSetup recv(protocol.recv_match_setup(&was_closed));

  EXPECT_EQ(recv.get_field_length(), 40000);
  EXPECT_EQ(recv.get_field_height(), 20000);
  EXPECT_EQ(recv.get_goal_height(), 5000);
  EXPECT_EQ(recv.get_ball_size(), 2000);
  EXPECT_EQ(recv.get_car_size(), 1000);
  EXPECT_EQ(recv.get_cars_quantity(), 4);
}

TEST(Protocolo, SendUserAction) {
  SocketTest skt(2);
  Protocol protocol(skt);
  uint8_t code_1 = 0x01;
  uint8_t code_2 = 0x05;
  uint8_t code_3 = 0x09;
  uint8_t id_1 = 0x00;
  uint8_t id_2 = 0x01;
  uint8_t id_3 = 0x02;
  UserAction action1(code_1, id_1);
  UserAction action2(code_2, id_2);
  UserAction action3(code_3, id_3);
  protocol.send_user_action(action1);
  protocol.send_user_action(action2);
  protocol.send_user_action(action3);
  bool was_closed = false;
  UserAction recv_action_1(protocol.recv_user_action(&was_closed));
  UserAction recv_action_2(protocol.recv_user_action(&was_closed));
  UserAction recv_action_3(protocol.recv_user_action(&was_closed));

  EXPECT_EQ(recv_action_1.getCode(), code_1);
  EXPECT_EQ(recv_action_2.getCode(), code_2);
  EXPECT_EQ(recv_action_3.getCode(), code_3);
}
