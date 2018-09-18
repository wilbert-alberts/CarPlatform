package com.walb.carplatform.mainui;

import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.layout.GridData;

public class CarView extends Composite {

	private ObstacleSensorView obstacleSensorView;
	private LineSensorView lineSensorView;

	/**
	 * Create the composite.
	 * @param parent
	 * @param style
	 */
	public CarView(Composite parent, int style) {
		super(parent, style);
		setLayout(new GridLayout(1, false));

		obstacleSensorView = new ObstacleSensorView(this, style);
		obstacleSensorView.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		lineSensorView = new LineSensorView(this, style);
		lineSensorView.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false, 1, 1));
	}

	@Override
	protected void checkSubclass() {
		// Disable the check that prevents subclassing of SWT components
	}

}
