package com.walb.carplatform.mainui;

import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.SWT;

public class CarView extends Composite {

	private ObstacleSensorView obstacleSensorView;

	/**
	 * Create the composite.
	 * @param parent
	 * @param style
	 */
	public CarView(Composite parent, int style) {
		super(parent, style);
		setLayout(new FillLayout(SWT.HORIZONTAL));

		obstacleSensorView = new ObstacleSensorView(this, style);
	}

	@Override
	protected void checkSubclass() {
		// Disable the check that prevents subclassing of SWT components
	}

}
