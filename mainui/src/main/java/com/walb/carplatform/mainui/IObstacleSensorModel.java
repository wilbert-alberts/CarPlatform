package com.walb.carplatform.mainui;

import java.util.Observer;

public interface IObstacleSensorModel {
	public void addObserver(Observer o);
	public void deleteObserver(Observer o);
	public IObstacleSensorObservation getObservation();
}
