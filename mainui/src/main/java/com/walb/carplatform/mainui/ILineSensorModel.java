package com.walb.carplatform.mainui;

import java.util.Observer;

public interface ILineSensorModel {

	void addObserver(Observer lineSensorView);
	void deleteObserver(Observer lineSensorView);
	public ILineSensorObservation getObservation();

	public class ILineSensorObservation {
		public boolean LL;
		public boolean L;
		public boolean R;
		public boolean RR;
	}
	
}
