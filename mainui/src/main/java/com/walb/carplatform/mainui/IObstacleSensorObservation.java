package com.walb.carplatform.mainui;

public interface IObstacleSensorObservation {

	int getStartAngle();
	int getEndAngle();
	boolean getRangeChanged();
	double getObstacleDistance(int angle);

}