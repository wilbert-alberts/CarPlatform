package com.walb.carplatform.mainui;

public class ObstacleSensorObservation implements IObstacleSensorModel.Observation {
	private int startAngle;
	private double obstacleDistance[];
	private boolean rangeChanged;
	
	public ObstacleSensorObservation(int sa, double distances[], boolean rc) {
		startAngle = sa;
		obstacleDistance = distances;
		rangeChanged = rc;
	}
	
	/* (non-Javadoc)
	 * @see com.walb.carplatform.mainui.IObstacleSensorObservation#getStartAngle()
	 */
	@Override
	public int getStartAngle() {
		return startAngle;
	}
	
	/* (non-Javadoc)
	 * @see com.walb.carplatform.mainui.IObstacleSensorObservation#getEndAngle()
	 */
	@Override
	public int getEndAngle() {
		return startAngle+obstacleDistance.length;
	}
	
	/* (non-Javadoc)
	 * @see com.walb.carplatform.mainui.IObstacleSensorObservation#getObstacleDistance(int)
	 */
	@Override
	public double getObstacleDistance(int angle) {
		if (angle < startAngle) {
			return -1;
		}
		
		if (angle - startAngle >= obstacleDistance.length) {
			return -1;
		}
		
		return obstacleDistance[angle-startAngle];
	}

	@Override
	public boolean getRangeChanged() {
		return rangeChanged;
	}
}
