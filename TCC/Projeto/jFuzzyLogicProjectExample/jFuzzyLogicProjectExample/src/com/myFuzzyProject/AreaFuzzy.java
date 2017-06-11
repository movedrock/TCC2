package br.com.igor.tccrestws;

import java.util.List;

import br.com.igor.tccrestws.entity.Atividade;
import br.com.igor.tccrestws.entity.Perfil;
import br.com.igor.tccrestws.entity.UsuarioAtividade;
import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;
import net.sourceforge.jFuzzyLogic.plot.JFuzzyChart;

public class Fuzzy {
	
	public Fuzzy(){}
//	public void inicializaFuzzy(List<UsuarioAtividade> listUsuarioAtividade){
	public static Perfil executaFuzzy(UsuarioAtividade ua){
		
		String filename = "D:/JavaProjects/TccRestWS/src/br/com/igor/tccrestws/area_classif.fcl";
		FIS fis = FIS.load(filename, true);

		if (fis == null) {
			System.err.println("Can't load file: '" + filename + "'");
//			System.exit(1);
		}
		
		Perfil retorno = ua.getAtividade().getPerfil();

		// Get default function block
		FunctionBlock fb = fis.getFunctionBlock(null);
		
		//JFuzzyChart.get().chart(fb);

		Double freq = 0.0;
		Double satis = 0.0;

				freq = ua.getFrequencia();
				satis = ua.getSatisfacao();
				
				// Set inputs
				fb.setVariable("freq",freq);
				fb.setVariable("satis",satis);
		
				// Evaluate1
				fb.evaluate();
		
				// Show output variable's chart
				fb.getVariable("relacao").defuzzify();
				
				retorno = aplicaFuncao(retorno, fb.getVariable("relacao").getValue());

		System.out.println("Area Perfil: " + fb.getVariable("areaPerfil").getValue());
		return retorno;
	}
	
	public static Perfil aplicaFuncao(Perfil aux,Double relacao){
		
		
		aux.setArtistico(relacao*aux.getArtistico()/100);
		
		
		aux.setIntelecto(relacao*aux.getIntelecto()/100);
		
		aux.setSocial(relacao*aux.getSocial()/100);
		
		aux.setSaude(relacao*aux.getSaude()/100);

		return aux;
	}

}