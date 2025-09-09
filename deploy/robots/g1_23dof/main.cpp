#include "FSM/CtrlFSM.h"
#include "FSM/State_Passive.h"
#include "FSM/State_FixStand.h"
#include "FSM/State_RLBase.h"

std::unique_ptr<LowCmd_t> FSMState::lowcmd = nullptr;
std::shared_ptr<LowState_t> FSMState::lowstate = nullptr;
std::shared_ptr<Keyboard> FSMState::keyboard = nullptr;

void init_fsm_state()
{
    auto lowcmd_sub = std::make_shared<unitree::robot::g1::subscription::LowCmd>();
    usleep(0.2 * 1e6);
    if(!lowcmd_sub->isTimeout())
    {
        spdlog::critical("The other process is using the lowcmd channel, please close it first.");
        unitree::robot::go2::shutdown();
        // exit(0);
    }
    FSMState::lowcmd = std::make_unique<LowCmd_t>();
    FSMState::lowstate = std::make_shared<LowState_t>();
    spdlog::info("Waiting for connection to robot...");
    FSMState::lowstate->wait_for_connection();
    spdlog::info("Connected to robot.");
}

int main(int argc, char** argv)
{
    // Load parameters
    auto vm = param::helper(argc, argv);

    std::cout << " --- Unitree Robotics --- \n";
    std::cout << "     G1-23dof Controller \n";

    // Unitree DDS Config
    unitree::robot::ChannelFactory::Instance()->Init(0, vm["network"].as<std::string>());

    init_fsm_state();

    FSMState::lowcmd->msg_.mode_machine() = 4; // 23dof
    if(!FSMState::lowcmd->check_mode_machine(FSMState::lowstate)) {
        spdlog::critical("Unmatched robot type.");
        exit(-1);
    }
    
    // Initialize FSM
    auto & joy = FSMState::lowstate->joystick;
    auto fsm = std::make_unique<CtrlFSM>(new State_Passive(FSMMode::Passive));
    fsm->states.back()->registered_checks.emplace_back(
        std::make_pair(
            [&]()->bool{ return joy.LT.pressed && joy.up.on_pressed; }, // L2 + Up
            (int)FSMMode::FixStand
        )
    );
    fsm->add(new State_FixStand(FSMMode::FixStand));
    fsm->states.back()->registered_checks.emplace_back(
        std::make_pair(
            [&]()->bool{ return joy.RB.pressed && joy.X.on_pressed; }, // R1 + X
            FSMMode::Velocity
        )
    );
    fsm->add(new State_RLBase(FSMMode::Velocity, "Velocity"));

    std::cout << "Press [L2 + Up] to enter FixStand mode.\n";
    std::cout << "And then press [R1 + X] to start controlling the robot.\n";

    while (true)
    {
        sleep(1);
    }
    
    return 0;
}

