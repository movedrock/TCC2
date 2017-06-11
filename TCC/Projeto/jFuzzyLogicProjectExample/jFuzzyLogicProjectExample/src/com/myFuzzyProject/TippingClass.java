package com.myFuzzyProject;

import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;
import net.sourceforge.jFuzzyLogic.plot.JFuzzyChart;

public class TippingClass {
	public static void main(String[] args) throws Exception {
		String filename = "area_classif.fcl";
		FIS fis = FIS.load(filename, true);

		if (fis == null) {
			System.err.println("Can't load file: '" + filename + "'");
			System.exit(1);
		}

		// Get default function block
		FunctionBlock fb = fis.getFunctionBlock(null);
		
		double [] input1 = {
		      
				28.5489139433318,
				27.6099611950969,
				1.58030993042378,
				22.1357428655099,
				8.07358279195668,
				12.6850684502642,
				16.4361270364453,
				28.2821095283080,
				12.5323231294999,
				29.4915739940957,
				9.04364846136197,
				21.0329626770278,
				19.9901655475328,
				16.1737939512857,
				20.9431656054093,
				19.9958374020776,
				5.34397363201013,
				3.84043199160518,
				29.9724118428408,
				5.13363199069296,
				0.978024615915841,
				16.8359937812898,
				26.4559950135543,
				20.0752591360318,
				5.71299801539862,
				11.0674963819168,
				13.8217781178123,
				29.4491385291225,
				4.69214856679690,
				25.6656841753773,
		};
		
		
		double [] input2 = {
		
			6.44764536870088,
			3.76272210278832,
			1.90923695236303,
			4.28252992979386,
			4.82022061031856,
			1.20611613297162,
			5.89507484695059,
			2.26187679752676,
			3.84619124369411,
			5.82986382747674,
			2.51806122472313,
			2.90440664276979,
			6.17090884393223,
			2.65280909810029,
			8.24376266688835,
			9.82663399721950,
			7.30248792267598,
			3.43877004114983,
			5.84069333278452,
			1.07769015243743,
			9.06308150649733,
			8.79653724481905,
			8.17760559370642,
			2.60727999055465,
			5.94356250664331,
			0.225125927402318,
			4.25259320214135,
			3.12718886820616,
			1.61484744311750,
			1.78766186752368,

		};

		
		double [] output = new double [30];
		
		for (int i=0; i<30;i++){
			
			// Set inputs
			fb.setVariable("freq",input1[i]);
			fb.setVariable("satis",input2[i]);

			// Evaluate1
			fb.evaluate();


			// Show output variable's chart
			fb.getVariable("relacao").defuzzify();
			
			//JFuzzyChart.get().chart(fb);
			//fb.getVariable("relacao").chartDefuzzifier(true);

			output[i] = fb.getVariable("relacao").getValue();
			
			// Print ruleSet
			//System.out.println(fb);
			System.out.println(fb.getVariable("relacao").getValue());
			
			
		}
		

	}

}
