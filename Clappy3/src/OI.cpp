#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"

#include "Commands/AutonomousCommand.h"
#include "Commands/DriveTeleop.h"
#include "Commands/MoveToGround.h"
#include "Commands/MoveToHook.h"
#include "Commands/AutoGrabGearFromGround.h"
#include "Commands/AutoGrabGearFromShoot.h"
#include "Commands/AutoPlaceGear.h"
#include "Commands/ToggleGearPCM.h"
#include "Commands/ToggleRobotDirection.h"

OI::OI() {

	m_driveConfig = ControlConfig::DISABLED;
	m_gearConfig = ControlConfig::DISABLED;

	switch (m_driveConfig)
	{
	case ControlConfig::JOYSTICK:
	{
	    driveStick.reset(new Joystick(0));
	    driveStickX = nullptr;

	    triggerRb.reset(new JoystickButton(driveStick.get(), 1)); //Trigger
	    triggerRb->WhenPressed(new ToggleRobotDirection());

	    break;
	}
	case ControlConfig::XBOXCONTOLLER:
	{
	    driveStickX.reset(new XboxController(0));
	    driveStick = nullptr;

	    triggerRb.reset(new JoystickButton(driveStickX.get(), 6)); //Rb
	    triggerRb->WhenPressed(new ToggleRobotDirection());

	    break;
	}
	case ControlConfig::DISABLED:
	{
		driveStick = nullptr;
		driveStickX = nullptr;
		triggerRb = nullptr;
		break;
	}
	}

	switch (m_gearConfig)
	{
	case ControlConfig::XBOXCONTOLLER:
	{
		gearStickX.reset(new XboxController(1));
		gearStick = nullptr;

	    triggerRb.reset(new JoystickButton(gearStickX.get(), 6)); //Rb
	    triggerRb->WhenPressed(new ToggleGearPCM(PCMStatus::CLOSED));

	    triggerLb.reset(new JoystickButton(gearStickX.get(), 7));
	    triggerLb->WhenPressed(new ToggleGearPCM(PCMStatus::OPENED));

	    button4a.reset(new JoystickButton(gearStickX.get(), 1));
	    button4a->WhenPressed(new AutoPlaceGear());

	    button5b.reset(new JoystickButton(gearStickX.get(), 2));
	    button5b->WhenPressed(new AutoGrabGearFromGround());

	    button6x.reset(new JoystickButton(gearStickX.get(), 3));
	    button6x->WhenPressed(new AutoGrabGearFromShoot());

	    button7y = nullptr;

	    break;
	}
	default:
	{
		gearStickX = nullptr;
		gearStick = nullptr;
	    triggerLb = nullptr;
	    button4a = nullptr;
	    button5b = nullptr;
	    button6x = nullptr;
	    button7y = nullptr;
	    break;
	}
	}

}

std::shared_ptr<Joystick> OI::getDriveStick()
{
   return driveStick;
}

std::shared_ptr<Joystick> OI::getGearStick()
{
	return gearStick;
}

std::shared_ptr<XboxController> OI::getDriveStickX()
{
	return driveStickX;
}

std::shared_ptr<XboxController> OI::getGearStickX()
{
	return gearStickX;
}

ControlConfig OI::getDriveConfig()
{
	return m_driveConfig;
}

ControlConfig OI::getGearConfig()
{
	return m_gearConfig;
}
