#include "create/create.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
int main(int argc, char** argv){
	
	std::fstream newfile;

	create::RobotModel model = create::RobotModel::CREATE_2;
	std::string port="/dev/ttyAMA0";
	int baud = 115200;
	if(argc > 1 && std::string(argv[1]) == "create1") {
		model = create::RobotModel::CREATE_1;
		baud = 115200;
		std::cout<<"Running driver for create 1"<<std::endl;
	}
	else{
		std::cout<<"Running driver for create 2"<<std::endl;
	}
	// construct robot object
	create::Create robot(model);
	//connect to robot
	if(robot.connect(port, baud))
		std::cout<<"connected to robot"<<std::endl;
	else {
		std::cout<<"Failed to connect to robot on port"<<port.c_str() <<std::endl;
		return 1;
	}
	//switch to full mode
	robot.setMode(create::MODE_FULL);
	//delay till robot accept next command
	usleep(100000);
	newfile.open("matrix.txt",std::ios::in);
	if(newfile.is_open()){
		int left, right;
		while(newfile >> left >> right){
			std::cout<<"left "<<left<<"right "<<right<<std::endl;
			robot.driveWheels(left, right);
			usleep(100000);
			const create::Vel vel = robot.getVel();
			std::cout<<std::fixed<<std::setprecision(2)<<"\rOdometry(x,y,yaw):("
				<<vel.x<<", "<<vel.y<<", "<<vel.yaw<<") "<<std::endl;
			usleep(10000);	
	
		}
		newfile.close();
	}

	//robot.driveWheels(-0.2, 0.2);
	/*	
	while(true) {
		const create::Vel vel = robot.getVel();
		std::cout<<std::fixed<<std::setprecision(2)<<"\rOdometry(x,y,yaw):("
		<<vel.x<<", "<<vel.y<<", "<<vel.yaw<<") ";
		usleep(10000);	
	}
	*/
	return 0;
}
