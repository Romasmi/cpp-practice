#include "pch.h"

#include "Car.h"

using namespace std;

enum Command
{
	INFO,
	ENGINE_ON,
	ENGINE_OFF,
	SET_GEAR,
	SET_SPEED,
	EXIT
};

using DialogCommand = pair<Command, string>;

const vector<DialogCommand> DialogCommands = {
	{ Command::INFO, "Info" },
	{ Command::ENGINE_ON, "EngineOn" },
	{ Command::ENGINE_OFF, "EngineOff" },
	{ Command::SET_GEAR, "SetGear" },
	{ Command::SET_SPEED, "SetSpeed" },
	{ Command::EXIT, "Exit" }
};

bool CommandExist(const string& strCommand, Command& command)
{
	for (const DialogCommand& item : DialogCommands)
	{
		if (item.second == strCommand)
		{
			command = item.first;
			return true;
		}
	}
	return false;
}

std::vector<std::string> Split(const std::string& str)
{
	std::istringstream strStream(str);
	std::vector<std::string> lineVector((std::istream_iterator<std::string>(strStream)), std::istream_iterator<std::string>());
	return lineVector;
}

void OnSetGear(Car& car, const vector<string>& inputCommand)
{
	if (inputCommand.size() < 2)
	{
		cout << "Gear is not set";
		return;
	}
	const int gear = stoi(inputCommand[1]);
	car.SetGear(gear);
}

void OnSetSpeed(Car& car, const vector<string>& inputCommand)
{
	if (inputCommand.size() != 2)
	{
		cout << "Speed is not set\n";
		return;
	}
	const unsigned int speed = stoul(inputCommand[1]);
	car.SetSpeed(speed);
}

void Dialog()
{
	Car car;

	string str;
	while (getline(cin, str))
	{
		const vector<string> inputCommand = Split(str);
		if (inputCommand.size() == 0)
		{
			continue;
		}

		Command command;
		if (CommandExist(inputCommand[0], command))
		{
			switch (command)
			{
			case Command::INFO:
				car.PrintState();
				break;
			case Command::ENGINE_ON:
				car.TurnOnEngine();
				break;
			case Command::ENGINE_OFF:
				car.TurnOffEngine();
				break;
			case Command::SET_GEAR:
				OnSetGear(car, inputCommand);
				break;
			case Command::SET_SPEED:
				OnSetSpeed(car, inputCommand);
				break;
			}
			if (command == Command::EXIT)
			{
				break;
			}
		}
		else
		{
			cout << "Unknown command\n";
		}
	}
}

int main()
{
	try
	{
		Dialog();
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}
	return 0;
}
