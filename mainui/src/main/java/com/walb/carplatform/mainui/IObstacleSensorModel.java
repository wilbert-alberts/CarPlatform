package com.walb.carplatform.mainui;

import java.util.Observer;

public interface IObstacleSensorModel {
	public void addObserver(Observer o);
	public void deleteObserver(Observer o);
	public Observation getObservation();

	interface Observation {

		int getStartAngle();
		int getEndAngle();
		boolean getRangeChanged();
		double getObstacleDistance(int angle);

	}
}
