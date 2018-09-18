package com.walb.carplatform.mainui;

import java.util.Observable;
import java.util.Observer;

import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;

import com.walb.carplatform.mainui.ILineSensorModel.ILineSensorObservation;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.layout.GridData;

public class LineSensorView extends Composite implements Observer{

	private ILineSensorModel model;
	private Color  lineSeenColor;
	private Color  noLineSeenColor;
	private Button btnRR;
	private Button btnR;
	private Button btnL;
	private Button btnLL;
	private Composite composite;
	private Label lblNewLabel;

	/**
	 * Create the composite.
	 * @param parent
	 * @param style
	 */
	public LineSensorView(Composite parent, int style) {
		super(parent, style);
		setLayout(new GridLayout(1, false));
		
		lblNewLabel = new Label(this, SWT.NONE);
		lblNewLabel.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, true, false, 1, 1));
		lblNewLabel.setAlignment(SWT.CENTER);
		lblNewLabel.setText("Line sensor");
		
		composite = new Composite(this, SWT.NONE);
		composite.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1));
		composite.setLayout(new FillLayout(SWT.HORIZONTAL));
		
		btnLL = new Button(composite, SWT.TOGGLE);
		btnLL.setText("LL");
		
		btnL = new Button(composite, SWT.TOGGLE);
		btnL.setText("L");
		
				btnR = new Button(composite, SWT.TOGGLE);
				btnR.setText("R");
				
				btnRR = new Button(composite, SWT.TOGGLE);
				btnRR.setText("RR");
		
		lineSeenColor = new Color(this.getDisplay(), 200,200,200);
		noLineSeenColor = new Color(this.getDisplay(), 100,100,100);
	}
	
	public void setModel(ILineSensorModel model) {
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
		this.getDisplay().asyncExec(new UpdateTask(model.getObservation()));		
	}
	
	class UpdateTask implements Runnable {
		private ILineSensorObservation observation;
		public UpdateTask(ILineSensorModel.ILineSensorObservation obs) {
			this.observation = obs;
		}
		@Override
		public void run() {
			setButtonColor(btnLL, observation.LL);
			setButtonColor(btnL, observation.L);
			setButtonColor(btnR, observation.R);
			setButtonColor(btnRR, observation.RR);
		}
		private void setButtonColor(Button btn, boolean state) {
			if (state) {
				btn.setBackground(lineSeenColor);				
			}
			else {
				btn.setBackground(noLineSeenColor);
			}
		}
		
	}
}
