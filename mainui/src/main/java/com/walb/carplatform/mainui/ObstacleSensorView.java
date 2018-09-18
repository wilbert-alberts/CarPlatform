package com.walb.carplatform.mainui;

import java.util.Observable;
import java.util.Observer;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Composite;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.swt.ChartComposite;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.eclipse.swt.layout.FillLayout;

public class ObstacleSensorView extends Composite implements Observer {

	private XYSeriesCollection dataset;
	private XYSeries series;
	private IObstacleSensorModel model;

	/**
	 * Create the composite.
	 * 
	 * @param parent
	 * @param style
	 */
	public ObstacleSensorView(Composite parent, int style) {
		super(parent, style);

		dataset = new XYSeriesCollection();
		series = new XYSeries("obstacles");
		dataset.addSeries(series);

		JFreeChart chart = ChartFactory.createPolarChart("Obstacle sensor", // Chart title
				dataset, true, true, false);
		setLayout(new FillLayout(SWT.HORIZONTAL));

		ChartComposite cc = new ChartComposite(this, SWT.NONE, chart);
	}
	
	public void setModel(IObstacleSensorModel model) {
		if (this.model != null) {
			this.model.deleteObserver(this);
		}
		this.model = model;
		model.addObserver(this);
	}
		
	@Override
	protected void checkSubclass() {
		// Disable the check that prevents subclassing of SWT components
	}

	@Override
	public void update(Observable arg0, Object arg1) {
		IObstacleSensorModel.Observation obs = model.getObservation();
		this.getDisplay().asyncExec(new UpdateTask(obs)); 		
	}

	class UpdateTask implements Runnable {
		private IObstacleSensorModel.Observation observation;
		public UpdateTask(IObstacleSensorModel.Observation obs) {
			observation = obs;
		}
		@Override
		public void run() {
			if (observation.getRangeChanged()) {
				series.clear();
			}
			
			for (int i = observation.getStartAngle(); i<observation.getEndAngle(); i++) {
				series.addOrUpdate(i, observation.getObstacleDistance(i));
			}
		}
	}
}
