#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
  TODO:
    * Calculate the RMSE here.
  */
	VectorXd rmse(4);
	rmse << 0,0,0,0;


    if( (estimations.size()==0) || (estimations.size() != ground_truth.size())){
        return rmse;
    }
	//accumulate squared residuals
	for(unsigned int i=0; i < estimations.size(); ++i){
		VectorXd residuals = estimations[i] - ground_truth[i];
		residuals = residuals.array() * residuals.array();
		rmse += residuals;
	}
    
    rmse = rmse/estimations.size();
    rmse = rmse.array().sqrt();

	return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
  TODO:
    * Calculate a Jacobian here.
  */
	MatrixXd Hj(3,4);
	//recover state parameters
	float px = x_state(0);
	float py = x_state(1);
	float vx = x_state(2);
	float vy = x_state(3);

	//TODO: YOUR CODE HERE 

	//check division by zero
	if(px==0 && py ==0){
	    cout << "division by zero" << endl;
	    return Hj;
	}
	//compute the Jacobian matrix
    float c1 = px * px + py * py;
    Hj << px/sqrt(c1), py/sqrt(c1), 0, 0,
          -py/c1, px/c1, 0, 0,
          (py*(vx*py-vy*px))/pow(c1,1.5),(px*(vy*px-vx*py))/pow(c1,1.5),px/sqrt(c1),py/sqrt(c1);
	return Hj;
}
